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
#include "NonBlockingSocket.hpp"

class Server
{

private:
    int _server_fd;
    int _port;
    char *_password;
    int _client_count;
    struct pollfd fds[FD_SETSIZE];
    std::map<int, std::string> _clients;

public:
    Server(int port, char *password);

    void run();
    void startServer();
    void handleNewClient();
    void handleClientRequest(int client_fd);
};

#endif