#include "Server.hpp"

void Server::channelInvite(int client_fd, std::vector<std::string> command)
{
    if (command.size() != 3)
    {
        std::cout << "Error: INVITE <nickname> <channel>" << std::endl;
        return;
    }
    std::string nickname = command[1];
    std::string channelName = command[2];
    std::map<std::string, Channel>::iterator it;
    it = _channels.find(channelName);
    if (it == _channels.end())
        std::cout << "Error: channel " << channelName << " does not exist" << std::endl;
    else
    {
        Channel currChannel = it->second;
        if (currChannel.getInviteOnly() == false)
        {
            std::cout << "Error: channel " << channelName << " is not invite only" << std::endl;
            return;
        }
        Client currClient = _clients[client_fd];
        if (currChannel.isOperator(currClient.getNickname()) == false)
        {
            std::cout << "Error: " << currClient.getNickname() << " is not an operator in channel " << channelName << std::endl;
            return;
        }
        std::map<std::string, Client>::iterator it_client = currChannel.getClients().find(nickname);
        if (it_client != currChannel.getClients().end())
        {
            std::cout << "Error: " << nickname << " is not in channel " << channelName << std::endl;
            return;
        }

        for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); ++it)
        {
            if (it->second.getNickname() == nickname)
            {
                if (currChannel.isInvited(nickname))
                {
                    std::cout << "Error: " << nickname << " is already invited to channel " << channelName << std::endl;
                    return;
                }
                currChannel.addInvited(nickname);
            }
        }
        
    }
}