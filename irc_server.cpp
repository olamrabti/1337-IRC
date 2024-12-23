#include "irc_server.hpp"

void handle_clients(int server_fd)
{
    (void)server_fd;
    std::cout << "Handling client..." << std::endl;
};

void launch_server(char **av)
{
    int server_fd;
    struct sockaddr_in server_addr;

    // TODO Password will be parsed and checked for later

    int port = atoi(av[1]); // TODO need to be parsed later

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
        throw std::runtime_error("Failed to open socket.");

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        close(server_fd);
        throw std::runtime_error("Failed to bind the socket.");
    }

    if (listen(server_fd, 5) < 0)
    {
        close(server_fd);
        throw std::runtime_error("Failed to listen on socket.");
    }

    std::cout << "Server is listening on port : " << port << std::endl;

    // TODO clients handling
    while (true)
    {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
        if (client_fd < 0)
        {
            std::cerr << "ERROR on accept" << std::endl;
            continue;
        }

        std::cout << "Client connected!" << std::endl;

        // Handle the client connection
        try
        {
            handle_clients(client_fd);
            close(client_fd);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error while handling client: " << e.what() << std::endl;
            close(client_fd);
        }

        close(server_fd);
    }
}