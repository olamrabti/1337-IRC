#include "Server.hpp"

int ft_atoi(std::string parameter)
{
    size_t i = 0;
    int signe = 1;
    unsigned long long total = 0;

    while (parameter[i] >= 9 && parameter[i] <= 13)
        i++;
    if (parameter[i] == '+' || parameter[i] == '-')
    {
        if (parameter[i] == '-')
            signe = -1;
        i++;
    }
    while (parameter[i] >= '0' && parameter[i] <= '9')
    {
        if (total > (9223372036854775807ULL - (parameter[i] - '0')) / 10)
            return (signe == 1 ? -1 : 0);
        total = total * 10 + (parameter[i] - '0');
        i++;
    }
    return ((int)(signe * total));
}

bool isValidNumber(const std::string &number)
{
    int start = 0;

    if (number[0] == '+' || number[0] == '-')
        start = 1;

    for (size_t i = start; i < number.size(); i++)
    {
        if (number[i] < '0' || number[i] > '9')
            return false;
    }

    return true;
}

std::vector<std::string> parseModes(const std::string &modes)
{
    
    std::vector<std::string> result;
    bool give = true;
    for (size_t i = 0; i < modes.size(); i++)
    {
        if (modes[i] == '+')
            give = true;
        else if (modes[i] == '-')
            give = false;
        else
            result.push_back((give ? "+" : "-") + std::string(1, modes[i]));
    }
    return result;
}

std::vector<std::string> parseParametres(std::vector<std::string> command, std::vector<std::string> modes)
{
    std::vector<std::string> result;
    size_t paramIndex = 3;

    for (size_t i = 0; i < modes.size(); i++)
    {
        if (modes[i] == "+o" || modes[i] == "-o" || modes[i] == "+l" || modes[i] == "+k")
        {
            if (paramIndex < command.size())
                result.push_back(command[paramIndex++]);
            else
                result.push_back("");
        }
    }

    return result;
}

void Server::oModeParam(Channel &currChannel, std::string &parameter, std::string &mode, Client &currClient)
{
    if (parameter.empty())
        return;

    std::map<int, Client>::iterator it = _clients.find(getClientFdByName(parameter));
    if (it == _clients.end() || !it->second.isFullyAuthenticated())
    {
        sendReply(currClient.getClientFd(), ERR_NOSUCHNICK(currClient.getHostName(), currClient.getNickname(), parameter));
        return;
    }

    Client &targetClient = it->second;
    if (!currChannel.isClientInChannel(targetClient.getClientFd()))
    {
        sendReply(currClient.getClientFd(), ERR_USERNOTINCHANNEL(currClient.getHostName(), targetClient.getNickname(), currChannel.getName()));
        return;
    }

    if (mode == "+o")
    {
        if (!currChannel.isOperator(targetClient.getClientFd()))
        {
            currChannel.addOperator(targetClient.getClientFd());
            sendReply(targetClient.getClientFd(), RPL_YOUREOPER(targetClient.getNickname()));
        }
    }
    else if (mode == "-o" && currChannel.isOperator(targetClient.getClientFd()))
    {
        currChannel.removeOperator(targetClient.getClientFd());
    }

    broadcastModeChange(currClient, currChannel, mode, parameter);
}

void Server::iModeParam(Channel &currChannel, const std::string &mode, Client &currClient)
{
    currChannel.setInviteOnly(mode == "+i");
    broadcastModeChange(currClient, currChannel, mode, "");
}

void Server::pluskModeParam(Channel &currChannel, const std::string &parameter, Client &currClient)
{
    if (parameter.empty())
        return;

    currChannel.setKey(parameter);
    broadcastModeChange(currClient, currChannel, "+k", parameter);
}

void Server::minuskModeParam(Channel &currChannel, Client &currClient)
{
    currChannel.setKey("");
    broadcastModeChange(currClient, currChannel, "-k", "");
}

void Server::pluslModeParam(Channel &currChannel, const std::string &parameter, Client &currClient)
{
    if (parameter.empty())
        return;

    if (!isValidNumber(parameter))
    {
        sendReply(currClient.getClientFd(), ERR_INVALIDMODEPARAM(currClient.getNickname(), currChannel.getName(), "+l"));
        return;
    }

    currChannel.setUserLimit(ft_atoi(parameter));
    broadcastModeChange(currClient, currChannel, "+l", parameter);
}

void Server::minuslModeParam(Channel &currChannel, Client &currClient)
{
    currChannel.setUserLimit(0);
    broadcastModeChange(currClient, currChannel, "-l", "");
}


void Server::tModeParam(Channel &currChannel, const std::string &mode, Client &currClient)
{
    currChannel.setTopicLock(mode == "+t");
    broadcastModeChange(currClient, currChannel, mode, "");
}

void Server::broadcastModeChange(Client &currClient, Channel &currChannel, const std::string &mode, std::string parameter)
{
    std::string modeMessage = ":" + currClient.getPrefix() + " MODE " + currChannel.getName() + " " + mode;
    if (!parameter.empty())
        modeMessage += " " + parameter;
    modeMessage += "\r\n";

    currChannel.broadcastMessage(modeMessage, _clients);
}

void Server::sendChannelInfo(Client &currClient, Channel &currChannel)
{
    sendReply(currClient.getClientFd(), RPL_CHANNELMODEIS(_hostname, currClient.getNickname(), currChannel.getName(), currChannel.getChannelModes()));
    sendReply(currClient.getClientFd(), RPL_CREATIONTIME(_hostname, currClient.getNickname(), currChannel.getName(), currChannel.getCreationDate()));
}

int Server::getClientFdByName(const std::string &nickname)
{
    for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it->second.getNickname() == nickname)
            return it->first;
    }
    return -1;
}

bool allParamEmpty(std::vector<std::string> parameters, std::vector<std::string> modes)
{
    size_t paramCount = 0;
    for (size_t i = 0; i < modes.size(); i++)
    {
        if (modes[i] == "+o" || modes[i] == "-o" || modes[i] == "+l" || modes[i] == "+k")
            paramCount++;
    }
    if (paramCount != 0)
    {
        size_t total = 0;
        for (size_t i = 0; i < paramCount; i++)
        {
            if (parameters[i] == "")
                total++;
        }
        if (total == paramCount)
            return true;
    }

    return false;
}

void Server::channelMode(Client &currClient, std::vector<std::string> command)
{
    if (command.size() < 2)
    {
        sendReply(currClient.getClientFd(), ERR_NEEDMOREPARAMS(currClient.getNickname(), currClient.getHostName(), command[0]));
        return;
    }

    std::string channelName = command[1];
    std::map<std::string, Channel>::iterator it = _channels.find(channelName);
    if (it == _channels.end())
    {
        sendReply(currClient.getClientFd(), ERR_NOSUCHCHANNEL(currClient.getHostName(), currClient.getNickname(), channelName));
        return;
    }

    Channel &currChannel = it->second;

    if (command.size() == 2)
    {
        sendChannelInfo(currClient, currChannel);
        return;
    }

    if (!currChannel.isOperator(currClient.getClientFd()))
    {
        sendReply(currClient.getClientFd(), ERR_CHANOPRIVSNEEDED(currClient.getHostName(), currClient.getNickname(), channelName));
        return;
    }

    std::vector<std::string> modes;
    if (command.size() >= 3)
    {
        if (command[2][0] != '+' && command[2][0] != '-')
            return;
        modes = parseModes(command[2]);
    }
    
    std::vector<std::string> parameters = parseParametres(command, modes);
    if (allParamEmpty(parameters, modes))
    {
        sendChannelInfo(currClient, currChannel);
        return;
    }

    int paramCount = 0;
    for (size_t i = 0; i < modes.size(); i++)
    {
        if ((modes[i] == "+o" || modes[i] == "-o"))
        {
            oModeParam(currChannel, parameters[paramCount++], modes[i], currClient);
        }
        else if (modes[i] == "+i" || modes[i] == "-i")
        {
            iModeParam(currChannel, modes[i], currClient);
        }
        else if (modes[i] == "+k")
        {
            pluskModeParam(currChannel, parameters[paramCount++], currClient);
        }
        else if (modes[i] == "-k")
        {
            minuskModeParam(currChannel, currClient);
        }
        else if (modes[i] == "+l")
        {
            pluslModeParam(currChannel, parameters[paramCount++], currClient);
        }
        else if (modes[i] == "-l")
        {
            minuslModeParam(currChannel, currClient);
        }
        else if (modes[i] == "+t" || modes[i] == "-t")
        {
            tModeParam(currChannel, modes[i], currClient);
        }
        else
        {
            sendReply(currClient.getClientFd(), ERR_UNKNOWNMODE(currClient.getHostName(), currClient.getNickname(), modes[i]));
        }
    }
}
