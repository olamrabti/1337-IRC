#include "Server.hpp"


void Server::broadcastNickChange(Client &client, const std::string &oldNick, const std::string &newNick)
{
    std::string message = ":" + oldNick + "!" + client.getUsername() + "@" + client.getHostName() + " NICK :" + newNick + "\r\n";

    // Broadcast to all clients
    for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it->second.getClientFd() != client.getClientFd())
        {
            sendReply(it->second.getClientFd(), message);
        }
    }
}

void Server::NickCommand(int client_fd, std::vector<std::string> command)
{
    if (command.size() < 2)
    {
        sendReply(client_fd, ERR_NONICKNAMEGIVEN(_clients[client_fd].getNickname(), _clients[client_fd].getHostName()));
        return;
    }
    Client &currClient = _clients[client_fd];
    if (currClient.getAuthStatus() < 0x01)
        return;

    std::string nickname = command[1];
    int i = 0;
    bool validName = false;
    while (nickname[i])
    {
        if (isalnum(nickname[i]))
            validName = true;
        i++;
    }

    if (!validName)
    {
        sendReply(client_fd, ERR_NONICKNAMEGIVEN(_clients[client_fd].getNickname(), _clients[client_fd].getHostName()));
        return;
    }

    for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it->second.getNickname() == nickname)
        {
            sendReply(client_fd, ERR_NICKNAMEINUSE(currClient.getNickname(), nickname));
            return;
        }
    }
    // // std::cout << "Nickname set to " << nickname << " for client " << client_fd << std::endl;
    std::string oldNick = currClient.getNickname();
    currClient.setNickname(nickname);

    if (currClient.getAuthStatus() == 0x07 && currClient.getNickFlag() == 0 && oldNick.empty())
    {
        sendWelcomeMessages(client_fd, currClient);
        currClient.setNickFlag(1);
    }

    currClient.setAuthStatus(0x02);
    if (currClient.isFullyAuthenticated())
    {
        broadcastNickChange(currClient, oldNick, nickname);
    }
}
