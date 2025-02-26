#include "Server.hpp"
#include <iomanip>

std::string getFromattedCurrTime()
{
    std::time_t now = std::time(nullptr);

    std::tm local_time = *std::localtime(&now);

    std::ostringstream oss;
    oss << std::put_time(&local_time, "%Y-%m-%d %H:%M:%S");

    return oss.str();
}

void Server::sendWelcomeMessages(int client_fd, const Client &client)
{
    std::string datetime = getFromattedCurrTime();
    std::vector<std::string> welcome_msg;
    welcome_msg.push_back("★━━━━━━━━━━━━━━━━━━ Welcome to IRC ━━━━━━━━━━━━━━━━━★");
    welcome_msg.push_back("【Connection Details】");
    welcome_msg.push_back("✦ Nickname: " + client.getNickname());
    welcome_msg.push_back("✦ Username: " + client.getUsername());
    welcome_msg.push_back("✦ Hostname: " + client.getHostName());
    welcome_msg.push_back("【Server Information】");
    welcome_msg.push_back("⚡ Server: " + _hostname );
    welcome_msg.push_back("⚡ Connected: " + datetime);
    for (size_t i = 0; i < welcome_msg.size(); i++)
        sendReply(client_fd, (": 001 " + client.getNickname() + " : " + welcome_msg[i] + "\r\n"));
}

void Server::UserCommand(int client_fd, std::vector<std::string> command)
{
    if (command.size() < 5)
    {
        sendReply(client_fd, ERR_NEEDMOREPARAMS(_clients[client_fd].getNickname(), _clients[client_fd].getHostName(), "USER"));
        return;
    }

    Client &currClient = _clients[client_fd];

    if (currClient.getAuthStatus() != 0x01 && currClient.getAuthStatus() != 0x03)
    {
        if (currClient.getAuthStatus() == 0x07)
            sendReply(client_fd, ERR_ALREADYREGISTERED(_clients[client_fd].getNickname(), _clients[client_fd].getHostName()));
        return;
    }

    std::string username = command[1];
    std::string servername = command[3];
    std::string realname = command[4];

    if (realname[0] == ':')
    {
        realname = realname.substr(1);
        for (size_t i = 5; i < command.size(); ++i)
        {
            realname += " " + command[i];
        }
    }

    currClient.setUsername(username);
    currClient.setServername(servername);
    currClient.setRealname(realname);
    currClient.setRegistered(true);
    currClient.setClientFd(client_fd);
    currClient.setAuthStatus(0x04);

    if (currClient.getAuthStatus() == 0x07)
    {
        sendWelcomeMessages(client_fd, currClient);
        currClient.setNickFlag(1);
    }
}
