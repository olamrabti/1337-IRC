#include "Client.hpp"

Client::Client(void) {}

Client::Client(std::string nickname) : _nickname(nickname) {}

Client::~Client(void) {}

Client &Client::operator = (Client const &other)
{
	return (*this);
}

const std::string &Client::getNickname(void) const
{
	return _nickname;
}