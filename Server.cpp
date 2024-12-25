#include "Server.hpp"

#include <sstream> // TODO might be removed !

Server::Server(int port, char *password) : _server_fd(-1), _port(port), _password(password), _client_count(1) {}

void Server::run()
{
    startServer();
    while (true)
    {
        int poll_count = poll(fds, _client_count, -1);
        if (poll_count < 0)
            throw std::runtime_error("Poll failed");

        // std::cerr << "Debugg\n";
        if (fds[0].revents & POLLIN)
            handleNewClient();

        for (int i = 1; i < _client_count; i++)
        {
            if (fds[i].revents & POLLIN)
                handleClientRequest(fds[i].fd);
        }
    }
}

void Server::startServer()
{
    struct sockaddr_in server_addr;
    _server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_server_fd < 0)
        throw std::runtime_error("Failed to open socket");

    NonBlockingSocket server_socket(_server_fd);
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(_port);

    int opt = 1;
    if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        throw std::runtime_error("Failed to set socket option SO_REUSEADDR");
    }
    if (bind(_server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        throw std::runtime_error("Failed to bind the socket");

    if (listen(_server_fd, 10) < 0)
        throw std::runtime_error("Failed to listen on socket");

    std::cout << "Server is listening on port " << _port << std::endl;

    // Set up poll() to monitor server_fd (for accepting new clients)
    fds[0].fd = _server_fd;
    fds[0].events = POLLIN;
}

void Server::handleNewClient()
{
    // std::cout << "New client to add" << std::endl;
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    int client_fd = accept(_server_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd < 0)
        throw std::runtime_error("Failed to accept client");

    NonBlockingSocket client_socket(client_fd);
    fds[_client_count].fd = client_fd;
    fds[_client_count].events = POLLIN;

    std::ostringstream client_id;
    client_id << _client_count;
    _clients[_client_count] = "client " + client_id.str();
    _client_count++;
    std::cout << "New client connected!" << std::endl;
}

void Server::handleClientRequest(int client_fd)
{
    char buffer[1024];
    int bytes_read = recv(client_fd, buffer, 1024, 0);
    if (bytes_read <= 0)
    {
        if (bytes_read == 0)
            std::cout << "Client disconnected." << std::endl;
        else
            throw std::runtime_error("Error receiving data from client");
        close(client_fd);
        return;
    }

    buffer[bytes_read] = '\0'; // Null-terminate the received data
    std::string message(buffer);

    std::cout << " Received : " << message << std::endl;

    // Handle commands
    if (message.substr(0, 4) == "NICK")
        std::cout << "Nick mok" << std::endl;
    else if (message.substr(0, 4) == "USER")
        std::cout << "User Flan flani" << std::endl;
    else if (message.substr(0, 4) == "JOIN")
        std::cout << "Wakha" << std::endl;
    // other commands ...
}