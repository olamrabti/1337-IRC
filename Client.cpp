#include "Client.hpp"

Client::Client(void) : _authStatus(0) {}

Client::Client(std::string nickname) : _nickname(nickname), _authStatus(0) {}

Client::~Client(void) {}

Client &Client::operator = (Client const &other)
{
	return (*this);
}

const std::string &Client::getNickname(void) const
{
	return _nickname;
}

void Client::setPassword(const std::string &password)
{
    _password = password;
}

const std::string &Client::getPassword() const
{
    return _password;
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