#include "Server.hpp"

void Server::NickCommand(int client_fd, std::string message)
{
    std::string trimmedMessage = trimString(message);
    std::vector<std::string> splits = split(trimmedMessage, ' ');
    if (splits.size() < 2)
    {
        std::cout << "Error: NICK command requires a nickname" << std::endl;
        return;
    }

    std::string nickname = splits[1];
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