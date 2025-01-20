#include "Server.hpp"

void Server::channelTopic(Client& currClient, std::vector<std::string> command)
{
    if (command.size() < 2)
    {
        sendReply(currClient.getClientFd(), ERR_NEEDMOREPARAMS(currClient.getNickname(), command[0]));
        return;
    }

    std::string channelName = command[1];
    std::string newTopic = (command.size() > 2) ? command[2] : "";


    std::map<std::string, Channel>::iterator it = _channels.find(channelName);
    if (it == _channels.end())
    {
        sendReply(currClient.getClientFd(), ERR_NOSUCHCHANNEL(currClient.getNickname(), channelName));
        return;
    }

    Channel& currChannel = it->second;

    if (command.size() == 2)
    {
        if (currChannel.getTopic().empty())
        {
            sendReply(currClient.getClientFd(), RPL_NOTOPIC(currClient.getNickname(), channelName));
        }
        else
        {
            sendReply(currClient.getClientFd(), RPL_TOPIC(currClient.getNickname(), channelName, currChannel.getTopic()));
            sendReply(currClient.getClientFd(), RPL_TOPICWHOTIME(currClient.getNickname(), channelName, currChannel.getTopicSetter(), currChannel.getTopicDdate()));
        }
        return;
    }

    if (currChannel.getTopicLock() && !currChannel.isOperator(currClient.getNickname()))
    {
        sendReply(currClient.getClientFd(), ERR_CHANOPRIVSNEEDED(currClient.getNickname(), channelName));
        return;
    }

    currChannel.setTopic(newTopic);
    currChannel.setTopicDate(getCurrTime());
    currChannel.setTopicSetter(currClient.getNickname());

    std::string message = RPL_TOPIC(currClient.getNickname(), channelName, newTopic);
    currChannel.broadcastMessage(message);

}
