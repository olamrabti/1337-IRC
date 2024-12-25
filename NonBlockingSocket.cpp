#include "NonBlockingSocket.hpp"

NonBlockingSocket::NonBlockingSocket(int socket_fd) : _fd(socket_fd)
{
    if (_fd == -1)
        throw std::runtime_error("Failed to create socket");
    setNonBlocking();
}

void NonBlockingSocket::setNonBlocking()
{
    int flags = fcntl(_fd, F_GETFL, 0);
    if (flags == -1)
        throw std::runtime_error("Failed to get socket flags");
    if (fcntl(_fd, F_SETFL, flags | O_NONBLOCK) == -1)
        throw std::runtime_error("Failed to set socket to non-blocking");
}

int NonBlockingSocket::getSocket() const
{
    return _fd;
}