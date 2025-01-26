#include "Server.hpp"

void Server::channelInvite(Client &currClient, std::vector<std::string> command)
{
    if (command.size() != 3)
    {
        sendReply(currClient.getClientFd(), ERR_NEEDMOREPARAMS(currClient.getNickname(), currClient.getHostName(), "INVITE"));
        return;
    }

    std::string nickname = command[1];
    std::string channelName = command[2];

    std::map<std::string, Channel>::iterator it = _channels.find(channelName);
    if (it == _channels.end())
    {
        sendReply(currClient.getClientFd(), ERR_NOSUCHCHANNEL(currClient.getHostName(), currClient.getNickname(), channelName));
        return;
    }

    Channel &currChannel = it->second;

    if (!currChannel.isOperator(currClient.getNickname()))
    {
        sendReply(currClient.getClientFd(), ERR_CHANOPRIVSNEEDED(currClient.getHostName(), currClient.getNickname(),  channelName));
        return;
    }

    Client *targetClient = NULL;
    for (std::map<int, Client>::iterator it_client = _clients.begin(); it_client != _clients.end(); ++it_client)
    {
        if (it_client->second.getNickname() == nickname)
        {
            targetClient = &it_client->second;
            break;
        }
    }
    if (!targetClient)
    {
        sendReply(currClient.getClientFd(), ERR_NOSUCHNICK(currClient.getHostName(), currClient.getNickname(), nickname));
        return;
    }

    if (currChannel.isClientInChannel(nickname))
    {
        sendReply(currClient.getClientFd(), ERR_USERONCHANNEL(currClient.getHostName(), currClient.getNickname(), nickname, channelName));
        return;
    }

    if (currChannel.isInvited(nickname)) // TODO
    {
        sendReply(currClient.getClientFd(), "Error: " + nickname + " is already invited to channel " + channelName);
        return;
    }

    currChannel.addInvited(nickname);

    sendReply(currClient.getClientFd(), RPL_INVITING(currClient.getHostName(), currClient.getNickname(), nickname, channelName));
    currChannel.broadcastMessage(RPL_INVITE(currClient.getNickname(), currClient.getUsername(), targetClient->getHostName(), channelName, nickname));

}
