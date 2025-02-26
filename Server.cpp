#include "Server.hpp"

Server::Server(int port, std::string password) : _server_fd(-1), _port(port), _password(password), _client_count(1)
{
    char hostBuffer[256];
    if (gethostname(hostBuffer, sizeof(hostBuffer)) == 0)
        _hostname = hostBuffer;
    else
        _hostname = "localhost";
}

Server::~Server()
{
    cleanup();
}

void Server::removeClient(int client_fd)
{
    std::map<int, Client>::iterator client_it = _clients.find(client_fd);
    if (client_it == _clients.end())
        return;

    for (std::map<std::string, Channel>::iterator it_chan = _channels.begin(); it_chan != _channels.end();)
    {
        if (it_chan->second.isClientInChannel(client_fd))
        {
            it_chan->second.removeClientFromChannel(client_fd);
            std::string message = RPL_KICK(client_it->second.getNickname(), client_it->second.getHostName(), client_it->second.getHostName(), client_it->second.getNickname(), it_chan->second.getName(), "");
            it_chan->second.broadcastMessage(message, _clients);
        }

        if (it_chan->second.getClients().empty())
            it_chan = _channels.erase(it_chan);
        else
            ++it_chan;
    }

    close(client_fd);
    _clients.erase(client_it);

    for (int i = 1; i < _client_count; i++)
    {
        if (fds[i].fd == client_fd)
        {
            fds[i] = fds[_client_count - 1];
            fds[_client_count - 1].fd = -1;
            _client_count--;
            break;
        }
    }
}

void Server::cleanup()
{
    for (int i = 1; i < _client_count; i++)
        removeClient(fds[i].fd);

    if (_server_fd != -1)
        close(_server_fd);

    _clients.clear();
    _channels.clear();
}

void Server::run()
{
    startServer();

    while (true)
    {
        int poll_count = poll(fds, _client_count, -1);
        if (poll_count < 0)
        {
            continue;
        }
        if (fds[0].revents & POLLIN)
        {
            handleNewClient();
            continue;
        }
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

    fds[0].fd = _server_fd;
    fds[0].events = POLLIN;
    launchBOT(server_addr);
}

void Server::handleNewClient()
{
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    int client_fd = accept(_server_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd < 0)
    {
        return;
    }
    NonBlockingSocket client_socket(client_fd);

    char *client_ip = inet_ntoa(client_addr.sin_addr);

    Client newClient(client_fd);
    _clients[client_fd] = newClient;
    newClient.setAdresseIp(client_ip);

    fds[_client_count].fd = client_fd;
    fds[_client_count].events = POLLIN;
    _client_count++;
}

void Server::launchBOT(struct sockaddr_in &server_addr)
{
    int bot_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (bot_fd < 0)
    {
        return;
    }

    if (connect(bot_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        close(bot_fd);
        return;
    }

    NonBlockingSocket bot_socket(bot_fd);
    Client botClient(bot_fd);
    botClient.setNickname("SECBOT");
    botClient.setUsername("SECBOT");
    botClient.setServername("SECBOT");
    botClient.setAdresseIp(_hostname);
    botClient.setRealname("SECBOT");
    botClient.setRegistered(true);
    botClient.setAuthStatus(0x07);

    _clients[bot_fd] = botClient;

    fds[_client_count].fd = bot_fd;
    fds[_client_count].events = POLLIN;
    _client_count++;

}

void Server::handleClientRequest(int client_fd)
{
    char buffer[BUFFER_SIZE];
    int bytes_read = recv(client_fd, buffer, BUFFER_SIZE, 0);

    if (bytes_read <= 0)
    {
        std::cout << "Client disconnected." << std::endl;
        this->removeClient(client_fd);
        return;
    }
    else
    {
        if (bytes_read >= BUFFER_SIZE)
            buffer[BUFFER_SIZE - 1] = '\0';
        else
            buffer[bytes_read] = '\0';

        Client &currClient = _clients[client_fd];
        currClient._buffer.append(buffer, bytes_read);
        currClient._buffer.erase(std::remove(currClient._buffer.begin(), currClient._buffer.end(), '\x04'), currClient._buffer.end());

        size_t pos;

        while (((pos = currClient._buffer.find("\r\n")) != std::string::npos) || ((pos = currClient._buffer.find("\n")) != std::string::npos))
        {
            if (currClient._buffer.empty())
                break;
            std::string command_str = currClient._buffer.substr(0, pos + 2);
            currClient._buffer.erase(0, pos + 2);

            std::vector<std::string> command = split(trimString(command_str), ' ');
            if (command.size() < 1)
                continue;

            std::cout << GREEN << "Received: " << RESET << command_str;

            if (command[0] == "PASS")
                PassCommand(client_fd, command);
            else if (command[0] == "NICK")
                NickCommand(client_fd, command);
            else if (command[0] == "USER")
                UserCommand(client_fd, command);
            else if (currClient.isFullyAuthenticated())
            {
                if (command[0] == "JOIN")
                    ChannelJoin(currClient, command);
                else if (command[0] == "MODE")
                    channelMode(currClient, command);
                else if (command[0] == "KICK")
                    channelKick(currClient, command);
                else if (command[0] == "TOPIC")
                    channelTopic(currClient, command);
                else if (command[0] == "INVITE")
                    channelInvite(currClient, command);
                else if (command[0] == "PRIVMSG")
                    PrivMsgCommand(currClient, command, command_str);
                else if (command[0] == "SECBOT")
                    BotCommand(client_fd, command);
            }
        }
    }
}

void sendReply(int client_fd, std::string response)
{
    if (send(client_fd, response.c_str(), response.length(), 0) == -1)
        return;
}
