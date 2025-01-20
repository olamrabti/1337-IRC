#include "Server.hpp"

void Server::NickCommand(int client_fd, std::vector<std::string> command)
{
    Client &currClient = _clients[client_fd];
    if (currClient.getAuthStatus() != 0x01 && currClient.getAuthStatus() != 0x05)
        return;
    //  TODO check if the user already has nickname

    if (command.size() < 2)
    {
        std::cout << "Error: NICK command requires a nickname" << std::endl;
        return;
    }

    std::string nickname = command[1];
    for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it->second.getNickname() == nickname)
        {
            std::cout << "Error: Nickname is already in use" << std::endl;
            return;
        }
    }
    currClient.setNickname(nickname);
    currClient.setAuthStatus(0x02);
    std::cout << "Nickname set to " << nickname << " for client " << client_fd << std::endl;
}
