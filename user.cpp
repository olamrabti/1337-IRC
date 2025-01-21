#include "Server.hpp"

void sendWelcomeMessages(int client_fd, const Client& client) {
    const char* CYAN = "\033[1;96m";
    const char* WHITE = "\033[1;97m";
    const char* YELLOW = "\033[1;93m";
    const char* RESET = "\033[0m";
    const char* MAGENTA = "\033[1;95m";
    const char* GREEN = "\033[1;32m";

    std::string welcome_msg = 
     std::string(CYAN) + "★━━━━━━━━━━━━━━━━━━ Welcome to IRC ━━━━━━━━━━━━━━━━━★" + RESET + "\n\n" +
        WHITE + "【Connection Details】" + RESET + "\n" +
        GREEN + "✦" + RESET + " Nickname: " + YELLOW + client.getNickname() + RESET + "\n" +
        GREEN + "✦" + RESET + " Username: " + YELLOW + client.getUsername() + RESET + "\n" +
        GREEN + "✦" + RESET + " Hostname: " + YELLOW + client.getHostName() + RESET + "\n\n" +     
        WHITE + "【Server Information】" + RESET + "\n" +
        GREEN + "⚡" + RESET + " Server: " + MAGENTA + "localhost" + RESET + "\n" +
        GREEN + "⚡" + RESET + " Connected: " + MAGENTA + "now" + RESET + "\n\n" +
        std::string(CYAN) + "┌─────────────────────────────────────┐" + RESET + "\n" +
        CYAN + "│" + YELLOW + "  Welcome to our IRC Network!        " + CYAN + "│" + RESET + "\n" +
        CYAN + "└─────────────────────────────────────┘" + RESET + "\n";

    sendReply(client_fd, welcome_msg);

    sendReply(client_fd, RPL_WELCOME(
        user_forma(client.getNickname(), client.getUsername(), client.getHostName()),
        client.getNickname()
    ));
    sendReply(client_fd, RPL_YOURHOST(client.getNickname(), "localhost"));
    sendReply(client_fd, RPL_CREATED(client.getNickname(), "now"));
}

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

    if (realname[0] == ':')
    {
        realname = realname.substr(1);
        for (size_t i = 5; i < command.size(); ++i)
        {
            realname += " " + command[i];
        }
    }

    currClient.setUsername(username);
    currClient.setHostname(hostname);
    currClient.setServername(servername);
    currClient.setRealname(realname);
    currClient.setRegistered(true);
    currClient.setClientFd(client_fd);
    currClient.setAuthStatus(0x04);
    
    std::cout << "User set to " << username << " for client " << client_fd << " and realname " << realname << std::endl;
    if (currClient.getAuthStatus() == 0x07)
    {
        sendWelcomeMessages(client_fd, currClient);
        currClient.setNickFlag(1);
    }
}
