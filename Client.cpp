#include "Client.hpp"
#include <unistd.h>

Client::Client(void) : _authStatus(0) {}

Client::Client(std::string nickname) : _nickname(nickname), _authStatus(0) {}

Client::Client(int fd)
{
    _client_fd = fd;
    _authStatus = 0;
    _nickname = "";
    _username = "";
    char hostBuffer[256];
    if (gethostname(hostBuffer, sizeof(hostBuffer)) == 0)
        _hostname = hostBuffer;
    else
        _hostname = "localhost";
}

Client::~Client(void) {}

const std::string &Client::getNickname(void) const
{
    return _nickname;
}

bool Client::isRegistered() const
{
    return _registered;
}

void Client::setRegistered(bool registered)
{
    _registered = registered;
}

void Client::setNickname(const std::string &nickname)
{
    _nickname = nickname;
}

void Client::setUsername(const std::string &username)
{
    _username = username;
}

void Client::setServername(const std::string &servername)
{
    _servername = servername;
}

void Client::setRealname(const std::string &realname)
{
    _realname = realname;
}

void Client::setAuthStatus(int status)
{
    _authStatus |= status;
}

int Client::getAuthStatus() const
{
    return _authStatus;
}

bool Client::isFullyAuthenticated() const
{
    return (_authStatus & 0x07) == 0x07;
}

std::string Client::getRealName(void) const
{
    return _realname;
}

std::string Client::getServerName(void) const
{
    return _servername;
}
const std::string &Client::getUsername(void) const
{
    return _username;
}

int Client::getClientFd(void) const
{
    return _client_fd;
}

void Client::setClientFd(int fd)
{
    this->_client_fd = fd;
}

std::string Client::getHostName(void) const
{
    return _hostname;
}

std::string Client::getPrefix() const
{
    return _nickname + "!" + _username + "@" + _hostname;
}
int Client::getNickFlag() const
{
    return _nickFlag;
}

void Client::setNickFlag(int flag)
{
    _nickFlag = flag;
}

void Client::setAdresseIp(const std::string &ip)
{
    _ip = ip;
}

const std::string &Client::getAdresseIp() const
{
    return _ip;
}
