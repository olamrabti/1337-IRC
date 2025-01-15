
#include "Server.hpp"

std::pair<int, std::string> parse_args(char **av)
{
    std::pair<int, std::string> params;
    params.first = -1;
    params.second = "";

    std::string port_str = av[1];
    for (size_t i = 0; i < port_str.length(); i++)
    {
        if (!isdigit(port_str[i]))
            throw std::invalid_argument("Port must be a numeric value.");
    }

    char *end_ptr;
    double port = std::strtod(av[1], &end_ptr);

    if (*end_ptr != '\0')
        throw std::invalid_argument("Port must be a numeric value.");

    if (port != static_cast<int>(port))
        throw std::invalid_argument("Port must be an integer.");

    if (port < 1 || port > 65535)
        throw std::invalid_argument("Port must be in the range 1–65535.");

    params.first = static_cast<int>(port);

    std::string password = av[2];
    if (password.empty())
        throw std::invalid_argument("Password cannot be empty.");

    params.first = port;
    params.second = password;
    return params;
}

int main(int ac, char **av)
{
    if (ac != 3)
    {
        std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
        return 1;
    }

    try
    {
        // Parse and validate arguments
        std::pair<int, std::string> params = parse_args(av);
        Server IRC(params.first, params.second);
        IRC.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}