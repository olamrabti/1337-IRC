#include "Server.hpp"

void Server::UserCommand(int client_fd, std::string message)
{
    std::string trimmedMessage = trimString(message);
    std::vector<std::string> splits = split(trimmedMessage, ' ');

    if (splits.size() < 5)
    {
        std::cout << "Error: USER command requires username, hostname, servername, and realname" << std::endl;
        return;
    }
    std::string username = splits[1];
    std::string hostname = splits[2];
    std::string servername = splits[3];
    std::string realname = splits[4];

    Client &currClient = _clients[client_fd];
    if (currClient.isRegistered())
    {
        std::cout << "Error: Client is already registered" << std::endl;
        return;
    }
    currClient.setUsername(username);
    currClient.setHostname(hostname);
    currClient.setServername(servername);
    currClient.setRealname(realname);
    currClient.setRegistered(true);
    std::cout << "User registered: " << username << " (" << realname << ")" << std::endl;
}
