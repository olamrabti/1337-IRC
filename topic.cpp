#include "Server.hpp"

void Server::channelTopic(int client_fd, std::string message)
{
    std::string newMessage = trimString(message);
    std::vector<std::string> splits = split(newMessage, ' ');
    std::string channelName = splits[1];
    std::string newTopic = splits[2];
    if (splits.size() < 2 || splits.size() > 3)
    {
        std::cout << "Error: TOPIC <channel> [<topic>]\n";
        return;
    }
    std::map<std::string, Channel>::iterator it;
    it = _channels.find(channelName);
    if (it == _channels.end())
    {
        std::cout << "Error: channel " << channelName << " does not exist" << std::endl;
        return;
    }
    else
    {
        Channel currChannel = it->second;
        Client currClient = _clients[client_fd];
        if (currChannel.isOperator(currClient.getNickname()) == false)
        {
            std::cout << "Error: " << currClient.getNickname() << " is not an operator in channel " << channelName << std::endl;
            return;
        }
        if (splits.size() == 2)
        {
            std::cout << "Topic for channel " << channelName << " is " << currChannel.getTopic() << std::endl;
        }
        else
        {
            currChannel.setTopic(newTopic);
            std::cout << "Topic for channel " << channelName << " is set to " << newTopic << std::endl;
        }
    }

}

