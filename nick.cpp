#include "Server.hpp"

void Server::NickCommand(int client_fd, std::vector<std::string> command)
{
    if (command.size() < 2)
    {
        std::cout << "Error: NICK command requires a nickname" << std::endl;
        return;
    }

    std::string nickname = command[1];
    Client &currClient = _clients[client_fd];
    for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it->second.getNickname() == nickname)
        {
            std::cout << "Error: Nickname is already in use" << std::endl;
            return;
        }
    }
    currClient.setNickname(nickname);
    std::cout << "Nickname set to " << nickname << " for client " << client_fd << std::endl;
}