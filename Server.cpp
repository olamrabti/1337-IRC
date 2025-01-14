#include "Server.hpp"

#include <sstream> // TODO might be removed !

Server::Server(int port, std::string password) : _server_fd(-1), _port(port), _password(password), _client_count(1) {}

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
        throw std::runtime_error("Failed to set socket option SO_REUSEADDR");
    if (bind(_server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        throw std::runtime_error("Failed to bind the socket");
    if (listen(_server_fd, 10) < 0)
        throw std::runtime_error("Failed to listen on socket");

    std::cout << "Server is listening on port " << _port << std::endl;

    fds[0].fd = _server_fd;
    fds[0].events = POLLIN;
}

void Server::handleNewClient()
{
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    int client_fd = accept(_server_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd < 0)
        throw std::runtime_error("Failed to accept client");

    NonBlockingSocket client_socket(client_fd);
    fds[_client_count].fd = client_fd;
    fds[_client_count].events = POLLIN;

    // TODO might be removed !
    std::ostringstream client_id;
    client_id << client_fd;
    _clients[client_fd] = "client " + client_id.str();

    _client_count++;
    std::cout << "New client connected!" << std::endl;
}

void Server::handleClientRequest(int client_fd)
{
    char buffer[1024];
    int bytes_read = recv(client_fd, buffer, 1024, 0);

    if (bytes_read == 0)
    {
        std::cout << "Client disconnected." << std::endl;
        removeClient(client_fd);
        return;
    }
    else if (bytes_read < 0)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            std::cout << "another connection from same terminal" << std::endl;
        else
        {
            removeClient(client_fd);
            throw std::runtime_error("Error receiving data from client");
        }
    }
    else
    {
        buffer[bytes_read] = '\0';
        std::string message(buffer);
        std::cout << "Received: " << message;
        // Handle commands
        std::vector<std::string> command = split(trimString(message), ' ');
        if (command.empty())
            return;

        Client &currClient = _clients[client_fd];

        if (command[0] == "PASS")
        {
            PassCommand(client_fd, command);
            currClient.setAuthStatus(0x01);
        }
        else if (command[0] == "NICK")
        {
            NickCommand(client_fd, command);
            currClient.setAuthStatus(0x02);
        }
        else if (command[0] == "USER")
        {
            UserCommand(client_fd, command);
            currClient.setAuthStatus(0x04);
        }
        else if (currClient.isFullyAuthenticated())
        {
            if (command[0] == "JOIN")
                ChannelJoin(client_fd, command);
            else if (command[0] == "MODE") // TODO
                channelMode(client_fd, command);
            else if (command[0] == "KICK")
                channelKick(client_fd, command); // TODO to be tested when NICK is implemented
            else if (command[0] == "TOPIC")
                channelTopic(client_fd, command);
            else if (command[0] == "INVITE") // TODO
                channelInvite(client_fd, command);
        }
        else
        {
            std::cout << "Error: Client must be authenticated (PASS, NICK, USER) before any other command" << std::endl;
        }
    }
}
