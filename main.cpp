
#include "Server.hpp"

int main(int ac, char **av)
{

    if (ac == 3)
    {
        // TODO parse args here (olamrabt):
        int port = std::atoi(av[1]);
        try
        {
            Server IRC(port, av[2]);
            IRC.run();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << std::endl;
            return 0;
        }
    }
    return 1;
}