#include "Server.hpp"

void Server::removeClient(int client_fd)
{
    _clients.erase(client_fd);

    for (int i = 1; i < _client_count; i++)
    {
        if (fds[i].fd == client_fd)
        {
            fds[i] = fds[_client_count - 1];
            fds[_client_count - 1].fd = -1;
            _client_count--;
            return;
        }
    }
}

void Server::channelKick(int client_fd, std::string message)
{
    std::string newMessage = trimString(message);
    std::vector<std::string> splits = split(newMessage, ' ');
    std::string channelName = splits[1];
    std::string nickname = splits[2];
    std::string reason = splits[3]; // TODO reason is more then one word
    if (splits.size() < 3)
    {
        std::cout << "Error: KICK <channel> <nickname>" << std::endl;
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

        if (currChannel.removeClient(nickname))
        {
            std::cout << "Client " << nickname << " removed from channel " << channelName << std::endl;
        }

    }
    
}
