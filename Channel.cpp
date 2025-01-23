#include "Channel.hpp"

Channel::Channel(void) {}

bool isValidChannelName(const std::string &name)
{
	if (name.empty() || (name[0] != '#' && name[0] != '&'))
		return false;
	if (name.find(' ') != std::string::npos || name.find(',') != std::string::npos)
		return false;
	return name.length() <= 200;
}

std::string getCurrTime(void)
{
	std::stringstream convert;
	convert << time(NULL);
	return (convert.str());
}

Channel::Channel(const std::string &name, const std::string &key)
{
	_name = name;
	_topic = "";
	_key = key;
	_userLimit = 0;
	_inviteOnly = false; // TODO
	_topicLock = false;
	_creationDate = getCurrTime();
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
		// if (command.size() == 3) // TODO
		std::vector<std::string> keys = split(command[2], ',');
		for (size_t i = 0; i < channelsNames.size(); i++)
		{
			if (i < keys.size())
				tokens[channelsNames[i]] = keys[i];
			else
				tokens[channelsNames[i]] = "";
		}
	}
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
	std::map<std::string, Client>::iterator it = _clients.find(nickname);
	if (it != _clients.end())
	{
		_clients.erase(it);
		if (_operators.find(nickname) != _operators.end())
			_operators.erase(nickname);
		return true;
	}
	return false;
}

void Channel::setTopic(const std::string &topic) // TODO
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

		if (isInvited(client.getNickname()))
			_invited.erase(client.getNickname());
		return true;
	}
	return false;
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

std::set<std::string> Channel::getInvited(void) const
{
	return _invited;
}

void Channel::addOperator(const std::string &nickname)
{
	_operators.insert(nickname); // TODO : Check if this is correct
}

void Channel::removeOperator(const std::string &nickname)
{
	std::set<std::string>::iterator it;
	it = _operators.find(nickname);
	if (it != _operators.end())
		_operators.erase(it);
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
	if (it != _operators.end())
		return true;
	return false;
}

void Channel::broadcastMessage(std::string message)
{
	for (std::map<std::string, Client>::iterator it = _clients.begin(); it != _clients.end(); ++it)
		sendReply(it->second.getClientFd(), message);
}

std::string Channel::getCreationDate(void) const
{
	return _creationDate;
}

std::string Channel::getTopicDdate(void) const
{
	return _topicDate;
}

std::string Channel::getTopicSetter(void) const
{
	return _topicSetter;
}

void Channel::setCreationDate(std::string date)
{
	_creationDate = date;
}
void Channel::setTopicDate(std::string date)
{
	_topicDate = date;
}

void Channel::setTopicSetter(std::string client)
{
	_topicSetter = client;
}

std::string Channel::getAllUsersNames(void)
{
	std::string result = "";

	for (std::map<std::string, Client>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (isOperator(it->first))
			result += "@" + it->first + " ";
		else
			result += it->first + " ";
	}
	return result;
}

bool Channel::isClientInChannel(std::string nickname)
{
	std::map<std::string, Client>::iterator it_client;
	for (it_client = _clients.begin(); it_client != _clients.end(); ++it_client)
	{
		if (it_client->second.getNickname() == nickname)
			return true;
	}
	return false;
}
