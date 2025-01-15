#include "Channel.hpp"
#include <sstream>

Channel::Channel(void) {}

bool Channel::isValidChannelName(const std::string &name) const
{
	if (name.empty() || (name[0] != '#' && name[0] != '&'))
		return false;
	if (name.find(' ') != std::string::npos || name.find(',') != std::string::npos)
		return false;
	return name.length() <= 200;
}

Channel::Channel(const std::string &name, const std::string &key)
{
	if (!isValidChannelName(name)) // Ensure the name conforms to IRC rules
		throw std::invalid_argument("Invalid channel name");

	_name = name;
	_topic = "";		 // Default topic is unset
	_key = key;			 // Set the provided key (empty for no key)
	_userLimit = 0;		 // No user limit by default
	_inviteOnly = false; // Channel is open to all
	_topicLock = false;	 // Topic can be modified by anyone
}

Channel::~Channel(void) {}

std::vector<std::string> split(const std::string &str, char delimiter)
{
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

std::string trimString(const std::string &input)
{
	std::string result;
	size_t i = 0;

	while (i < input.size() && isspace(input[i]))
		i++;

	bool inSpace = false;
	while (i < input.size())
	{
		if (isspace(input[i]))
		{
			if (!inSpace)
			{
				result += ' ';
				inSpace = true;
			}
		}
		else
		{
			result += input[i];
			inSpace = false;
		}
		i++;
	}

	if (!result.empty() && isspace(result.back()))
		result.pop_back();

	return result;
}

std::map<std::string, std::string> parseJoinCommand(std::vector<std::string> command)
{
	std::map<std::string, std::string> tokens;
	std::vector<std::string> keys;
	std::vector<std::string> channelsNames;
	if (command.size() == 2 || command.size() == 3)
	{
		std::vector<std::string> channelsNames = split(command[1], ',');
		if (command.size() == 3)
			std::vector<std::string> keys = split(command[2], ',');
		for (size_t i = 0; i < channelsNames.size(); i++)
		{
			if (i < keys.size())
				tokens[channelsNames[i]] = keys[i];
			else
				tokens[channelsNames[i]] = "";
		}
	}
	else
		std::cout << "Error: JOIN" << std::endl;
	return tokens;
}

const std::string &Channel::getName(void) const
{
	return _name;
}

const std::string &Channel::getTopic(void) const
{
	return _topic;
}

const std::string &Channel::getKey(void) const
{
	return _key;
}

std::map<std::string, Client> &Channel::getClients(void)
{
	return _clients;
}

bool Channel::removeClient(const std::string &nickname)
{
	std::map<std::string, Client>::iterator it;
	it = _clients.find(nickname);
	if (it == _clients.end())
	{
		std::cout << "Error: client " << nickname << " does not exist in channel " << _name << std::endl;
		return false;
	}
	else
	{
		_clients.erase(it);
		return true;
	}
}

void Channel::setTopic(const std::string &topic)
{
	_topic = topic;
}

void Channel::setKey(const std::string &key)
{
	_key = key;
}

void Channel::setUserLimit(size_t limit)
{
	_userLimit = limit;
}

void Channel::setInviteOnly(bool status)
{
	_inviteOnly = status;
}

void Channel::setTopicLock(bool status)
{
	_topicLock = status;
}

bool Channel::addClient(Client &client)
{
	std::map<std::string, Client>::iterator it;
	it = _clients.find(client.getNickname());
	if (it == _clients.end())
	{
		_clients[client.getNickname()] = client;
		return true;
	}
	else
	{
		std::cout << "Error: client " << client.getNickname() << " already exists in channel " << _name << std::endl;
		return false;
	}
}

bool Channel::verifyKey(const std::string &key) const
{
	return _key == key;
}

size_t Channel::getUserCount(void) const
{
	return _clients.size();
}

size_t Channel::getUserLimit(void) const
{
	return _userLimit;
}

bool Channel::getInviteOnly(void) const
{
	return _inviteOnly;
}

bool Channel::getTopicLock(void) const
{
	return _topicLock;
}

std::set<std::string> Channel::getOperators(void) const
{
	return _operators;
}

void Channel::addOperator(const std::string &nickname)
{
	_operators.insert(nickname); // TODO : Check if this is correct
}

void Channel::removeOperator(const std::string &nickname)
{
	std::set<std::string>::iterator it;
	it = _operators.find(nickname);
	if (it == _operators.end())
	{
		std::cout << "Error: " << nickname << " is not an operator in channel " << _name << std::endl;
	}
	else
	{
		_operators.erase(it);
	}
}

void Channel::addInvited(const std::string &nickname)
{
	_invited.insert(nickname);
}

bool Channel::isInvited(const std::string &nickname) const
{
	std::set<std::string>::iterator it;
	it = _invited.find(nickname);
	if (it == _invited.end())
		return false;
	return true;
}

bool Channel::isOperator(const std::string &nickname) const
{
	std::set<std::string>::iterator it;
	it = _operators.find(nickname);
	if (it == _operators.end())
		return false;
	return true;
}
