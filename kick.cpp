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
    return result;
}

void Server::channelKick(Client& currClient, std::vector<std::string> command)
{
    if (command.size() < 3)
    {
        sendReply(currClient.getClientFd(), ERR_NEEDMOREPARAMS(currClient.getNickname(), command[0]));
        return;
    }
    std::string channelName = command[1];
    std::string nickname = command[2];
    std::string reason = getReason(command);

    std::map<std::string, Channel>::iterator it;
    it = _channels.find(channelName);
    if (it == _channels.end())
    {
        sendReply(currClient.getClientFd(), ERR_NOSUCHCHANNEL(currClient.getNickname(), channelName));
        return;
    }
    Channel& currChannel = it->second;

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
        std::string message = RPL_KICK(currClient.getNickname(), currClient.getHostName(), channelName, nickname , reason);
        currChannel.broadcastMessage(message);
        if (currChannel.getClients().empty())
        {
            _channels.erase(it);
            sendReply(currClient.getClientFd(), "Channel " + channelName + " deleted as it has no more users.");
        }
    }
}
