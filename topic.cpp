#include "Server.hpp"

std::string getTopic(std::vector<std::string> command)
{
    std::string result = "";
    for (size_t i = 2; i < command.size(); i++)
    {
        if (i > 2)
            result += " ";
        result += command[i];
    }
    if (!result.empty() && result[0] == ':')
        result = result.substr(1);
    return result;
}

void Server::channelTopic(Client &currClient, std::vector<std::string> command)
{
    if (command.size() < 2)
    {
        sendReply(currClient.getClientFd(), ERR_NEEDMOREPARAMS(currClient.getNickname(), command[0]));
        return;
    }

    std::string channelName = command[1];
    std::string newTopic = getTopic(command);

    std::map<std::string, Channel>::iterator it = _channels.find(channelName);
    if (it == _channels.end())
    {
        sendReply(currClient.getClientFd(), ERR_NOSUCHCHANNEL(currClient.getNickname(), channelName));
        return;
    }

    Channel &currChannel = it->second;

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
    currChannel.broadcastMessage(RPL_TOPIC(currClient.getNickname(), channelName, newTopic));
}
