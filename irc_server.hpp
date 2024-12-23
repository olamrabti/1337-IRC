#ifndef IRC_SERVER_HPP
#define IRC_SERVER_HPP

#include <iostream>
#include <sys/socket.h>
#include <exception>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 6665

void launch_server(char **av);
void handle_clients(int server_fd);

#endif