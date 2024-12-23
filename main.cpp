
#include "irc_server.hpp"

int main(int ac, char **av)
{
    if (ac == 3)
    {
        try
        {
            launch_server(av);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << std::endl;
            return 0;
        }
    }
    return 1;
}