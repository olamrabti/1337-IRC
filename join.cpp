#include "Server.hpp"

void Server::joinCommand(std::string channelName, std::string key, int client_fd)
{
    Client currClient = _clients[client_fd];
	std::map<std::string, Channel>::iterator it;
    it = _channels.find(channelName);
    if (it == _channels.end())
    {
        Channel newChannel(channelName, key);
        newChannel.addClient(currClient);
        newChannel.addOperator(currClient.getNickname());
        _channels[channelName] = newChannel;
        std::cout << "Channel " << channelName << " created" << std::endl;
    }
    else
    {
        std::cout << "Channel " << channelName << " already exists" << std::endl;
        Channel currChannel = it->second;
        if (currChannel.getKey() == key)
            std::cout << "Key is correct" << std::endl;
        else
        {
            std::cout << "Key is incorrect" << std::endl;
            return;
        }
        // if (currChannel.isInviteOnly()) // TODO
        if (currChannel.getUserLimit() != 0 && currChannel.getUserCount() >= currChannel.getUserLimit())
        {
            std::cout << "Error: channel " << channelName << " is full" << std::endl;
            return;
        }
        std::map<std::string, Client>::iterator it_client = currChannel.getClients().find(currClient.getNickname());
        if (it_client == currChannel.getClients().end())
        {
            currChannel.addClient(currClient);
            std::cout << "Client " << currClient.getNickname() << " added to channel " << channelName << std::endl;
        }
        else
        {
            std::cout << "Client " << currClient.getNickname() << " already exists in channel " << channelName << std::endl;
        }
    }
}


void Server::ChannelJoin(int client_fd, std::vector<std::string> command)
{
	std::map<std::string, std::string> tokens = parseJoinCommand(command);
    if (tokens.size() == 0)
    {
        std::cout << "Error: invalid JOIN command" << std::endl;
        return;
    }
	std::map<std::string, std::string>::iterator it;
	for (it = tokens.begin(); it != tokens.end(); it++)
		joinCommand(it->first, it->second, client_fd);
}
