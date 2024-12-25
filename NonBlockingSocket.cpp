#include "NonBlockingSocket.hpp"

NonBlockingSocket::NonBlockingSocket(int socket_fd) : _fd(socket_fd)
{
    if (_fd == -1)
        throw std::runtime_error("Failed to create socket");
    setNonBlocking();
}

void NonBlockingSocket::setNonBlocking()
{
    if (fcntl(_fd, F_SETFL, O_NONBLOCK) == -1)
        throw std::runtime_error("Failed to set socket to non-blocking");
}

int NonBlockingSocket::getSocket() const
{
    return _fd;
}