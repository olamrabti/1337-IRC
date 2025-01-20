#include "Client.hpp"

Client::Client(void) : _authStatus(0) {}

Client::Client(std::string nickname) : _nickname(nickname), _authStatus(0) {}

Client::Client(int fd)
{
    _client_fd = fd;
    _authStatus = 0;
    _nickname = "";
    _username = "";
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

void Client::setHostname(const std::string &hostname)
{
    _hostname = hostname;
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

std::string Client::getHostName(void)
{
    return _hostname;
}

std::string Client::getRealName(void)
{
    return _realname;
}

std::string Client::getServerName(void)
{
    return _servername;
}

int Client::getClientFd(void) const
{
    return _client_fd;
}

void Client::setClientFd(int fd)
{
    this->_client_fd = fd;
}

std::string Client::getPrefix() const
{
    return _nickname + "!" + _username + "@" + _hostname;
}
