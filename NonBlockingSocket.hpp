#ifndef NON_BLOCKING_S_HPP
#define NON_BLOCKING_S_HPP

#include <exception>
#include <iostream>
#include <fcntl.h>

class NonBlockingSocket
{

private:
    int _fd;

public:
    NonBlockingSocket(int socket_fd);
    void setNonBlocking();
    int getSocket() const;
};

#endif