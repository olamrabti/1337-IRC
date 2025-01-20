#include "Server.hpp"

void Server::UserCommand(int client_fd, std::vector<std::string> command)
{
    Client &currClient = _clients[client_fd];
    // if (currClient.getAuthStatus() != 0x01 && currClient.getAuthStatus() != 0x03)
    //     return;

    if (command.size() < 5)
    {
        std::cout << "Error: USER command requires username, hostname, servername, and realname" << std::endl;
        return;
    }
    //  if username not empty TODO
    std::string username = command[1];
    std::string hostname = command[2];
    std::string servername = command[3];
    std::string realname = command[4];

    // if (currClient.isRegistered())
    // {
    //     std::cout << "Error: Client is already registered" << std::endl;
    //     return;
    // }
    currClient.setUsername(username);
    currClient.setHostname(hostname);
    currClient.setServername(servername);
    currClient.setRealname(realname);
    currClient.setRegistered(true);
    currClient.setClientFd(client_fd);
    currClient.setAuthStatus(0x04);
}
