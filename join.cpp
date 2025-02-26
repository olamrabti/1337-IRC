#include "Server.hpp"

void Server::joinCommand(std::string channelName, std::string key, Client &currClient)
{
    int client_fd = currClient.getClientFd();
    std::map<std::string, Channel>::iterator it;
    it = _channels.find(channelName);
    if (it == _channels.end())
    {
        if (!isValidChannelName(channelName))
            return;
        Channel newChannel(channelName, key);
        newChannel.addClient(currClient.getClientFd());
        newChannel.addOperator(currClient.getClientFd());

        _channels[channelName] = newChannel;
        std::string message = RPL_JOIN(currClient.getNickname(), currClient.getUsername(), channelName, currClient.getAdresseIp());
        sendReply(currClient.getClientFd(), message);
        if (newChannel.getTopic() == "")
            sendReply(client_fd, RPL_NOTOPIC(currClient.getHostName(), currClient.getNickname(), channelName));
        else
        {
            sendReply(client_fd, RPL_TOPIC(currClient.getHostName(), currClient.getNickname(), channelName, newChannel.getTopic()));
            sendReply(client_fd, RPL_TOPICWHOTIME(currClient.getNickname(), channelName, newChannel.getTopicSetter(), newChannel.getTopicDdate()));
        }
        sendReply(client_fd, RPL_NAMREPLY(currClient.getHostName(), newChannel.getAllUsersNames(_clients) , channelName, currClient.getNickname()));
        sendReply(client_fd, RPL_ENDOFNAMES(currClient.getHostName(), currClient.getNickname(), channelName));
    }
    else
    {
        Channel &currChannel = it->second;
        if (currChannel.getInviteOnly() && !currChannel.isInvited(currClient.getClientFd()))
        {
            sendReply(client_fd, ERR_INVITEONLYCHAN(currClient.getNickname(), channelName));
            return;
        }

        if (currChannel.getUserLimit() != 0 && currChannel.getUserCount() >= currChannel.getUserLimit())
        {
            sendReply(client_fd, ERR_CHANNELISFULL(currClient.getHostName(), currClient.getNickname(), channelName));
            return;
        }

        if (currChannel.getKey() != key)
        {
            sendReply(client_fd, ERR_BADCHANNELKEY(currClient.getNickname(), currClient.getHostName(), channelName));
            return;
        }

        if (std::find(currChannel.getClients().begin(), currChannel.getClients().end(), currClient.getClientFd()) != currChannel.getClients().end())
        {
            sendReply(client_fd, ERR_USERONCHANNEL(currClient.getHostName(), currClient.getNickname(), currClient.getNickname(), channelName));
            return;
        }

        currChannel.addClient(currClient.getClientFd());
        std::string message = RPL_JOIN(currClient.getNickname(), currClient.getUsername(), channelName, currClient.getAdresseIp());
        currChannel.broadcastMessage(message, _clients);
        if (currChannel.getTopic() == "")
            sendReply(client_fd, RPL_NOTOPIC(currClient.getHostName(), currClient.getNickname(), channelName));
        else
        {
            sendReply(client_fd, RPL_TOPIC(currClient.getHostName(), currClient.getNickname(), channelName, currChannel.getTopic()));
            sendReply(client_fd, RPL_TOPICWHOTIME(currClient.getNickname(), channelName, currChannel.getTopicSetter(), currChannel.getTopicDdate()));
        }
        sendReply(client_fd, RPL_NAMREPLY(currClient.getHostName(), currChannel.getAllUsersNames(_clients), channelName, currClient.getNickname()));
        sendReply(client_fd, RPL_ENDOFNAMES(currClient.getHostName(), currClient.getNickname(), channelName));
    }
}

void Server::ChannelJoin(Client &currClient, std::vector<std::string> command)
{
    if (command.size() < 2)
    {
        sendReply(currClient.getClientFd(), ERR_NEEDMOREPARAMS(currClient.getNickname(), currClient.getHostName(), command[0]));
        return;
    }
    std::map<std::string, std::string> tokens = parseJoinCommand(command);
    if (tokens.size() == 0)
    {
        sendReply(currClient.getClientFd(), ERR_NEEDMOREPARAMS(currClient.getNickname(), currClient.getHostName(), command[0]));
        return;
    }

    std::map<std::string, std::string>::iterator it;
    for (it = tokens.begin(); it != tokens.end(); it++)
    {
        joinCommand(it->first, it->second, currClient);
    }
}
