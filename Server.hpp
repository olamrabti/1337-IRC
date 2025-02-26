#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <sys/socket.h>
#include <exception>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <map>
#include <set>
#include <poll.h>
#include <vector>
#include <utility>
#include <sstream>
#include <cerrno>
#include <algorithm>
#include "NonBlockingSocket.hpp"

#include "Client.hpp"
#include "Channel.hpp"
#include "numericReplies.hpp"
#define BUFFER_SIZE 512
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

class Channel;
class Client;

class Server
{

private:
    int _server_fd;
    int _port;
    std::string _password;
    std::string _hostname;
    int _client_count;
    struct pollfd fds[FD_SETSIZE];
    std::map<int, Client> _clients;
    std::map<std::string, Channel> _channels;

public:
    Server(int port, std::string password);
    ~Server();
    void run();
    void startServer();
    void launchBOT(struct sockaddr_in &server_addr);
    void handleNewClient();
    void handleClientRequest(int client_fd);
    void removeClient(int client_fd);
    void cleanup();
    int getClientByNickname(const std::string &nickname) const;
    void broadcastToChannel(Client &client, const std::string &channel_name, const std::string &message);
    void sendToClient(const std::string &target_nick, Client &client, const std::string &message);

    void sendWelcomeMessages(int client_fd, const Client &client);

    // pp:
    void ChannelJoin(Client &currClient, std::vector<std::string> command);
    void joinCommand(std::string channelName, std::string key, Client &currClient);
    void channelTopic(Client &currClient, std::vector<std::string> command);
    void channelMode(Client &currClient, std::vector<std::string> command);
    void channelKick(Client &currClient, std::vector<std::string> command);
    void channelInvite(Client &currClient, std::vector<std::string> command);
    void kickCommand(Client &currClient, std::string &channelName, std::string &nickname, std::string &reason);
    void oModeParam(Channel &currChannel, std::string &parameter, std::string &mode, Client &currClient);
    void iModeParam(Channel &currChannel, const std::string &mode, Client &currClient);
    void pluskModeParam(Channel &currChannel, const std::string &parameter, Client &currClient);
    void minuskModeParam(Channel &currChannel, Client &currClient);
    void minuslModeParam(Channel &currChannel, Client &currClient);
    void pluslModeParam(Channel &currChannel, const std::string &parameter, Client &currClient);
    void tModeParam(Channel &currChannel, const std::string &mode, Client &currClient);
    void sendChannelInfo(Client &currClient, Channel &currChannel);
    int getClientFdByName(const std::string &nickname);
    void broadcastModeChange(Client &currClient, Channel &currChannel, const std::string &mode, std::string parameter);

    // salmane
    void PassCommand(int client_fd, std::vector<std::string> command);
    void NickCommand(int client_fd, std::vector<std::string> command);
    void UserCommand(int client_fd, std::vector<std::string> command);
    void PrivMsgCommand(Client &client, std::vector<std::string> command, std::string &buffer);
    void BotCommand(int client_fd, std::vector<std::string> command);
    void broadcastNickChange(Client &client, const std::string &oldNick, const std::string &newNick);
};

void sendReply(int client_fd, std::string response);

#endif