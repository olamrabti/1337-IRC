#include "Server.hpp"

std::string getReason(std::vector<std::string> command)
{
    std::string result = "";
    for (size_t i = 3; i < command.size(); i++)
    {
        if (i > 3)
            result += " ";
        result += command[i];
    }
    if (!result.empty() && result[0] == ':')
        result = result.substr(1);
    return result;
}

std::map<std::string, std::vector<std::string > > parseKickCommand(std::vector<std::string> command)
{
    std::map<std::string, std::vector<std::string > > tokens;

    if (command.size() >= 3)
    {
        std::vector<std::string> channelNames = split(command[1], ',');
        std::vector<std::string> users = split(command[2], ',');

        if (channelNames.size() == users.size())
        {
            for (size_t i = 0; i < channelNames.size(); ++i)
            {
                tokens[channelNames[i]].push_back(users[i]);
            }
        }
        else if (channelNames.size() == 1 && users.size() >= 1)
        {
            for (size_t i = 0; i < users.size(); ++i)
            {
                tokens[channelNames[0]].push_back(users[i]);
            }
        }
        else if (users.size() == 1 && channelNames.size() >= 1)
        {
            for (size_t i = 0; i < channelNames.size(); ++i)
            {
                tokens[channelNames[i]].push_back(users[0]);
            }
        }
    }
    return tokens;
}

void Server::kickCommand(Client& currClient, std::string channelName, std::string nickname, std::string reason)
{
    std::map<std::string, Channel>::iterator it;
    it = _channels.find(channelName);
    if (it == _channels.end())
    {
        sendReply(currClient.getClientFd(), ERR_NOSUCHCHANNEL(currClient.getNickname(), channelName));
        return;
    }
    Channel &currChannel = it->second;

    if (!currChannel.isOperator(currClient.getNickname()))
    {
        sendReply(currClient.getClientFd(), ERR_CHANOPRIVSNEEDED(currClient.getNickname(), channelName));
        return;
    }

    if (!currChannel.isClientInChannel(nickname))
    {
        sendReply(currClient.getClientFd(), ERR_USERNOTINCHANNEL(currClient.getNickname(), nickname, channelName));
        return;
    }

    if (currChannel.removeClient(nickname))
    {
        std::string message = RPL_KICK(currClient.getNickname(), currClient.getHostName(), channelName, nickname, reason);
        currChannel.broadcastMessage(message);
        if (currChannel.getClients().empty())
        {
            _channels.erase(it);
            return;
        }
        if (currChannel.getOperators().empty())
        {
            std::map<std::string, Client>::iterator it_target = currChannel.getClients().begin();
            if (it_target != currChannel.getClients().end())
            {
                Client &targetClient = it_target->second;
                currChannel.addOperator(targetClient.getNickname());
                sendReply(targetClient.getClientFd(), RPL_YOUREOPER(targetClient.getNickname()));
            }
        }
    }

}

void Server::channelKick(Client &currClient, std::vector<std::string> command)
{
    if (command.size() < 3)
    {
        sendReply(currClient.getClientFd(), ERR_NEEDMOREPARAMS(currClient.getNickname(), command[0]));
        return;
    }

    std::string reason = getReason(command);

    std::map<std::string, std::vector<std::string > > tokens = parseKickCommand(command);
    if (tokens.size() == 0)
    {
        sendReply(currClient.getClientFd(), ERR_NEEDMOREPARAMS(currClient.getNickname(), command[0]));
        return;
    }

    for (std::map<std::string, std::vector<std::string > >::iterator it = tokens.begin(); it != tokens.end(); it++)
    {
        std::string channelName = it->first;
        // std::cout << "channelName: " << channelName << std::endl;
        std::vector<std::string> users = it->second;
        for (size_t i = 0; i < users.size(); i++)
        {
            std::string nickname = users[i];
            // std::cout << "nickname: " << users[i] << std::endl;
            kickCommand(currClient, channelName, nickname, reason);
        }
    }

}
