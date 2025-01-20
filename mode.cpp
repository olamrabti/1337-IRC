#include "Server.hpp"

bool isValidMode(char c)
{
    return (c == 'i' || c == 't' || c == 'k' || c == 'o' || c == 'l');
}

std::vector<std::string> parseModes(const std::string &modes, Client& currClient)
{
    std::vector<std::string> result;
    bool give = true;
    for (size_t i = 0; i < modes.size(); i++)
    {
        if (modes[i] == '+')
            give = true;
        else if (modes[i] == '-')
            give = false;
        else if (isValidMode(modes[i]))
            result.push_back((give ? "+" : "-") + std::string(1, modes[i]));
        else
        {
            sendReply(currClient.getClientFd(), ERR_UMODEUNKNOWNFLAG(currClient.getNickname(), channelName, modes[i]));
            return std::vector<std::string>();
        }
    }
    return result;
}

std::vector<std::string> parseParametres(std::vector<std::string> command)
{
    std::vector<std::string> result;
    if (command.size() > 3)
        for (size_t i = 3; i < command.size(); i++)
            result.push_back(command[i]);
    return result;
}

void oModeParam(Channel &currChannel, std::string parameter, std::string mode , Client& currClient , std::map<int, Client> _clients )
{
    if (parameter.empty())
    {
        sendReply(currClient.getClientFd(), ERR_NEEDMOREPARAMS(currClient.getNickname(), "MODE"));
        return;
    }
    if (mode == "+o")
    {
        std::map<std::string, Client>::iterator it_client;
        it_client = currChannel.getClients().find(parameter);
        if (it_client == currChannel.getClients().end())
        {
            sendReply(currClient.getClientFd(), ERR_NOTONCHANNEL(parameter, currChannel.getName()));
            return;
        }
        if (currChannel.isOperator(parameter))
        {
            sendReply(currClient.getClientFd(), ERR_INVALIDMODEPARAM(currClient.getNickname(), currChannel.getName(), mode));
            return;
        }
        currChannel.addOperator(parameter);
        sendReply(currClient.getClientFd(), ":" + currClient.getPrefix() + " MODE " + currChannel.getName() + " +o " + parameter + "\r\n");
        // sendReply(currClient.getClientFd(), RPL_CHANNELMODEIS(currClient.getNickname(), currChannel.getName(), mode));

    }
    else if (mode == "-o")
    {
        std::map<std::string, Client>::iterator it_client;
        it_client = currChannel.getClients().find(parameter);
        if (it_client == currChannel.getClients().end())
        {
            sendReply(currClient.getClientFd(), ERR_NOTONCHANNEL(parameter, currChannel.getName()));
            return;
        }
        if (!currChannel.isOperator(parameter))
        {
            sendReply(currClient.getClientFd(), ERR_CHANOPRIVSNEEDED(currClient.getNickname(), currChannel.getName()));
            return;
        }
        currChannel.removeOperator(parameter);
        sendReply(currClient.getClientFd(), ":" + currClient.getPrefix() + " MODE " + currChannel.getName() + " -o " + parameter + "\r\n");
    }
}

void iModeParam(Channel &currChannel, const std::string &mode, Client &currClient)
{
    if (mode == "+i")
    {
        currChannel.setInviteOnly(true);
        sendReply(currClient.getClientFd(), ":" + currClient.getPrefix() + " MODE " + currChannel.getName() + " +i" + "\r\n");
    }
    else if (mode == "-i")
    {
        currChannel.setInviteOnly(false);
        sendReply(currClient.getClientFd(), ":" + currClient.getPrefix() + " MODE " + currChannel.getName() + " -i" + "\r\n");
    }
}

void pluskModeParam(Channel &currChannel, const std::string &parameter, const std::string &mode, Client &currClient)
{
    if (mode == "+k")
    {
        if (parameter.empty())
        {
            sendReply(currClient.getClientFd(), ERR_NEEDMOREPARAMS(currClient.getNickname(), "MODE"));
            return;
        }
        currChannel.setKey(parameter);
        sendReply(currClient.getClientFd(), ":" + currClient.getPrefix() + " MODE " + currChannel.getName() + " +k " + parameter + "\r\n");
    }
}

void minuskModeParam(Channel &currChannel, const std::string &mode, Client &currClient)
{
    if (mode == "-k")
    {
        currChannel.setKey("");
        sendReply(currClient.getClientFd(), ":" + currClient.getPrefix() + " MODE " + currChannel.getName() + " -k" + "\r\n");
    }
}

void minuslModeParam(Channel &currChannel, const std::string &mode, Client &currClient)
{
    if (mode == "-l")
    {
        currChannel.setUserLimit(0);
        sendReply(currClient.getClientFd(), ":" + currClient.getPrefix() + " MODE " + currChannel.getName() + " -l" + "\r\n");
    }
}

void pluslModeParam(Channel &currChannel, const std::string &parameter, const std::string &mode, Client &currClient)
{
    if (mode == "+l")
    {
        if (parameter.empty())
        {
            sendReply(currClient.getClientFd(), ERR_NEEDMOREPARAMS(currClient.getNickname(), "MODE"));
            return;
        }

        try
        {
            int limit = std::stoi(parameter);
            currChannel.setUserLimit(limit);
            sendReply(currClient.getClientFd(), ":" + currClient.getPrefix() + " MODE " + currChannel.getName() + " +l " + parameter + "\r\n");
        }
        catch (const std::exception &e)
        {
            sendReply(currClient.getClientFd(), ERR_INVALIDMODEPARAM(currClient.getNickname(), currChannel.getName(), mode));
        }
    }
}

void tModeParam(Channel &currChannel, const std::string &mode, Client &currClient)
{
    if (mode == "+t")
    {
        currChannel.setTopicLock(true);
        sendReply(currClient.getClientFd(), ":" + currClient.getPrefix() + " MODE " + currChannel.getName() + " +t" + "\r\n");
    }
    else if (mode == "-t")
    {
        currChannel.setTopicLock(false);
        sendReply(currClient.getClientFd(), ":" + currClient.getPrefix() + " MODE " + currChannel.getName() + " -t" + "\r\n");
    }
    else
    {
        sendReply(currClient.getClientFd(), ERR_INVALIDMODEPARAM(currClient.getNickname(), currChannel.getName(), mode));
    }
}

void Server::channelMode(Client& currClient, std::vector<std::string> command)
{
    if (command.size() < 3)
    {
        sendReply(currClient.getClientFd(), ERR_NEEDMOREPARAMS(currClient.getNickname(), command[0]));
        return;
    }
    std::string channelName = command[1];
    std::vector<std::string> modes;
    if (command.size() >= 3)
        modes = parseModes(command[2], currClient);
    if (modes.empty())
    {
        sendReply(currClient.getClientFd(), ERR_UMODEUNKNOWNFLAG(currClient.getNickname(), channelName, ""));
        return;
    }
    std::vector<std::string> parameters = parseParametres(command);

    std::map<std::string, Channel>::iterator it;
    it = _channels.find(channelName);
    if (it == _channels.end())
    {
        sendReply(currClient.getClientFd(), ERR_NOSUCHCHANNEL(currClient.getNickname(), channelName));
        return;
    }
    else
    {
        Channel &currChannel = it->second;

        if (currChannel.isOperator(currClient.getNickname()) == false)
        {
            sendReply(currClient. getClientFd(), ERR_CHANOPRIVSNEEDED(currClient.getNickname(), channelName));
            return;
        }
        int paramCount = 0;
        for (size_t i = 0; i < modes.size(); i++)
        {
            if (modes[i] == "+o" || modes[i] == "-o")
            {
                if (parameters.size() > paramCount)
                {
                    oModeParam(currChannel, parameters[paramCount], modes[i], currClient, _clients);
                    paramCount++;
                }
                else 
                {
                    sendReply(currClient.getClientFd(), ERR_NEEDMOREPARAMS(currClient.getNickname(), command[0]));
                    return;
                }
            }
            else if (modes[i] == "+i" || modes[i] == "-i")
            {
                iModeParam(currChannel, modes[i], currClient);
            }
            else if (modes[i] == "+k" || modes[i] == "-k")
            {
                if (modes[i] == "+k")
                {
                    if (parameters.size() > paramCount)
                    {
                        pluskModeParam(currChannel, parameters[paramCount], modes[i], currClient);
                        paramCount++;
                    }
                    else 
                    {
                        sendReply(currClient.getClientFd(), ERR_NEEDMOREPARAMS(currClient.getNickname(), command[0]));
                        return;
                    }
                }
                else if (modes[i] == "-k")
                    minuskModeParam(currChannel, modes[i], currClient);
            }
            else if (modes[i] == "+l" || modes[i] == "-l")
            {
                if (modes[i] == "+l")
                {
                    if (parameters.size() > paramCount)
                    {
                        pluslModeParam(currChannel, parameters[paramCount], modes[i], currClient);
                        paramCount++;
                    }
                    else 
                    {
                        sendReply(currClient.getClientFd(), ERR_NEEDMOREPARAMS(currClient.getNickname(), command[0]));
                        return;
                    }
                }
                else if (modes[i] == "-l")
                    minuslModeParam(currChannel, modes[i], currClient);
            }
            else if (modes[i] == "+t" || modes[i] == "-t")
            {
                tModeParam(currChannel, modes[i], currClient);
            }
            else
            {
                sendReply(currClient.getClientFd(), ERR_UMODEUNKNOWNFLAG(currClient.getNickname(), channelName, ""));
                return;
            }
        }
    }
}
