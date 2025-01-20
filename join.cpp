#include "Server.hpp"
#include "numericReplies.hpp"

void Server::joinCommand(std::string channelName, std::string key, Client& currClient)
{
    int client_fd = currClient.getClientFd();
    std::map<std::string, Channel>::iterator it;
    it = _channels.find(channelName);
    if (it == _channels.end())
    {
        if (!isValidChannelName(channelName))
        {
            sendReply(client_fd, ERR_NOSUCHCHANNEL(currClient.getNickname(), channelName));
            return;
        }
        Channel newChannel(channelName, key);
        newChannel.addClient(currClient);
        newChannel.addOperator(currClient.getNickname());

        _channels[channelName] = newChannel;
        sendReply(client_fd, RPL_NOTIFYJOIN(currClient.getNickname(), currClient.getHostName(), channelName));
        if (newChannel.getTopic() == "")
            sendReply(client_fd, RPL_NOTOPIC(currClient.getNickname(), channelName));
        else
        {
            sendReply(client_fd, RPL_TOPIC(currClient.getNickname(), channelName, newChannel.getTopic()));
            sendReply(client_fd, RPL_TOPICWHOTIME(currClient.getNickname(), channelName, newChannel.getTopicSetter(), newChannel.getTopicDdate()));
        }
        sendReply(client_fd, RPL_NAMREPLY(currClient.getNickname(), channelName, newChannel.getAllUsersNames()));
        sendReply(client_fd, RPL_ENDOFNAMES(currClient.getNickname(), channelName));
    }
    else
    {
        Channel &currChannel = it->second;
        if (currChannel.getInviteOnly() && !currChannel.isInvited(currClient.getNickname()))
        {
            sendReply(client_fd, ERR_INVITEONLYCHAN(currClient.getNickname(), channelName));
            return;
        }

        if (currChannel.getUserLimit() != 0 && currChannel.getUserCount() >= currChannel.getUserLimit())
        {
            sendReply(client_fd, ERR_CHANNELISFULL(currClient.getNickname(), channelName));
            return;
        }

        if (currChannel.getKey() != key)
        {
            sendReply(client_fd, ERR_INVALIDKEY(currClient.getNickname(), channelName));
            return;
        }

        if (currChannel.getClients().find(currClient.getNickname()) != currChannel.getClients().end())
        {
            sendReply(client_fd, ERR_USERONCHANNEL(currClient.getNickname(), currClient.getNickname(), channelName));
            return;
        }

        currChannel.addClient(currClient);
        std::string message = RPL_NOTIFYJOIN(currClient.getNickname(), currClient.getHostName(), channelName);
        sendReply(client_fd, message);
        currChannel.broadcastMessage(message);
        if (currChannel.getTopic() == "")
            sendReply(client_fd, RPL_NOTOPIC(currClient.getNickname(), channelName));
        else
        {
            sendReply(client_fd, RPL_TOPIC(currClient.getNickname(), channelName, currChannel.getTopic()));
            sendReply(client_fd, RPL_TOPICWHOTIME(currClient.getNickname(), channelName, currChannel.getTopicSetter(), currChannel.getTopicDdate()));
        }
        sendReply(client_fd, RPL_NAMREPLY(currClient.getNickname(), channelName, currChannel.getAllUsersNames()));
        sendReply(client_fd, RPL_ENDOFNAMES(currClient.getNickname(), channelName));
    }
}

void Server::ChannelJoin(Client& currClient, std::vector<std::string> command)
{
    if (command.size() < 2)
    {
        sendReply(currClient.getClientFd(), ERR_NEEDMOREPARAMS(currClient.getNickname(), command[0]));
        return;
    }
    std::map<std::string, std::string> tokens = parseJoinCommand(command);
    if (tokens.size() == 0)
    {
        sendReply(currClient.getClientFd(), ERR_NEEDMOREPARAMS(currClient.getNickname(), command[0]));
        return;
    }

    std::map<std::string, std::string>::iterator it;
    for (it = tokens.begin(); it != tokens.end(); it++)
    {
        joinCommand(it->first, it->second, currClient);
    }
}
