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
#include "NonBlockingSocket.hpp"

#include "Client.hpp"
#include "Channel.hpp"

class Channel;
class Client;
class Server
{

private:
    int _server_fd;
    int _port;
     std::string _password;
    int _client_count;
    struct pollfd fds[FD_SETSIZE];
    std::map<int, Client> _clients; // Client TODO 
    std::map<std::string, Channel> _channels;

public:
    Server(int port, std::string password);

    void run();
    void startServer();
    void handleNewClient();
    void handleClientRequest(int client_fd);
    void removeClient(int client_fd);
    
    // pp:
    void ChannelJoin(int client_fd, std::vector<std::string> command);
    void joinCommand(std::string channelName, std::string key, int client_fd);
    void channelTopic(int client_fd, std::vector<std::string> command);
    void channelMode(int client_fd, std::vector<std::string> command);
    void channelKick(int client_fd, std::vector<std::string> command);
    void channelInvite(int client_fd, std::vector<std::string> command);

    // salmane 
    void PassCommand(int client_fd, std::vector<std::string> command);
    void NickCommand(int client_fd, std::vector<std::string> command);
    void UserCommand(int client_fd, std::vector<std::string> command);

};

#endif