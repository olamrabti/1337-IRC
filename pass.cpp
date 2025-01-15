#include "Server.hpp"

void Server::PassCommand(int client_fd, std::string message)
{
    std::string trimmedMessage = trimString(message);
    std::vector<std::string> splits = split(trimmedMessage, ' ');
    if (splits.size() < 2)
    {
        std::cout << "Error: PASS command requires a password" << std::endl;
        return;
    }

    std::string password = splits[1];
    Client &currClient = _clients[client_fd];
    if (currClient.isRegistered())
    {
        std::cout << "Error: Client is already registered" << std::endl;
        return;
    }
    currClient.setPassword(password);
    std::cout << "Password set for client " << currClient.getNickname() << std::endl;
}