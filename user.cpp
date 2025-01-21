#include "Server.hpp"

void Server::UserCommand(int client_fd, std::vector<std::string> command)
{
    Client &currClient = _clients[client_fd];
    if (currClient.getAuthStatus() != 0x01 && currClient.getAuthStatus() != 0x03)
    {
        if (currClient.getAuthStatus() == 0x07)
            sendReply(client_fd, ERR_ALREADYREGISTERED(_clients[client_fd].getNickname()));
        return;
    }

    if (command.size() < 5)
    {
        sendReply(client_fd, ERR_NEEDMOREPARAMS(_clients[client_fd].getNickname(), "USER"));
        return;
    }
    std::string username = command[1];
    std::string hostname = command[2];
    std::string servername = command[3];
    std::string realname = command[4];

    currClient.setUsername(username);
    currClient.setHostname(hostname);
    currClient.setServername(servername);
    currClient.setRealname(realname);
    currClient.setRegistered(true);
    currClient.setClientFd(client_fd);
    currClient.setAuthStatus(0x04);
    
    std::cout << "User set to " << username << " for client " << client_fd << std::endl;
    if (currClient.getAuthStatus() == 0x07)
    {
        sendReply(client_fd, RPL_WELCOME(user_forma(_clients[client_fd].getNickname(), _clients[client_fd].getUsername(), _clients[client_fd].getHostname()), _clients[client_fd].getNickname()));
        currClient.setNickFlag(1);
    }
}
