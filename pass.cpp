#include "Server.hpp"

void Server::PassCommand(int client_fd, std::vector<std::string> command)
{
    if (command.size() < 2)
    {
        sendReply(client_fd, ERR_NEEDMOREPARAMS(_clients[client_fd].getNickname(), "PASS"));
        return;
    }

    std::string password = command[1];
    Client &currClient = _clients[client_fd];
    if (_password == password && currClient.getAuthStatus() == 0x07)
    {
        sendReply(client_fd, ERR_ALREADYREGISTERED(currClient.getNickname()));
        return;
    }

    if (_password == password)
    {
        std::cout << "Password set for client " << currClient.getNickname() << std::endl;
        currClient.setAuthStatus(0x01);
    }
    else {
        sendReply(client_fd, ERR_PASSWDMISMATCH(_clients[client_fd].getNickname()));
    }
}