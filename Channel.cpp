#include "Channel.hpp"

Channel::Channel(void) {}

bool isValidChannelName(const std::string &name)
{
	if (name.empty() || (name[0] != '#' && name[0] != '&'))
		return false;
	if (name.find(',') != std::string::npos)
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
	_inviteOnly = false;
	_topicLock = false;
	_creationDate = getCurrTime();
}

Channel::~Channel(void) {}

std::vector<std::string> split(const std::string &str, char delimiter)
{
	std::vector<std::string> tokens;
	size_t start = 0;
	size_t end = str.find(delimiter);
	while (end != std::string::npos)
	{
		tokens.push_back(str.substr(start, end - start));
		start = end + 1;
		end = str.find(delimiter, start);
	}
	tokens.push_back(str.substr(start));
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

	if (!result.empty() && isspace(result[result.size() - 1]))
		result.erase(result.size() - 1);

	return result;
}


std::map<std::string, std::string> parseJoinCommand(std::vector<std::string> command)
{
	std::map<std::string, std::string> tokens;
	std::vector<std::string> keys;
	std::vector<std::string> channelsNames;

	if (command.size() >= 2)
	{
		channelsNames = split(command[1], ',');
		if (command.size() >= 3)
		{
			keys = split(command[2], ',');
		}

		for (size_t i = 0; i < channelsNames.size(); i++)
		{
			if (i < keys.size() && !keys[i].empty())
			{
				tokens[channelsNames[i]] = keys[i];
			}
			else
			{
				tokens[channelsNames[i]] = "";
			}
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

std::vector<int> &Channel::getClients(void)
{
	return _channelClients;
}

bool Channel::removeClientFromChannel(int client_fd)
{
    for (std::vector<int>::iterator it = _channelClients.begin(); it != _channelClients.end(); ++it)
    {
        if (*it == client_fd)
        {
            _channelClients.erase(it);
            return true;
        }
    }
    return false;
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

void Channel::addClient(int client_fd)
{
	_channelClients.push_back(client_fd);
}

bool Channel::verifyKey(const std::string &key) const
{
	return _key == key;
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

std::set<int> Channel::getOperators(void) const
{
	return _operators;
}

std::set<int> Channel::getInvited(void) const
{
	return _invited;
}

void Channel::addOperator(int client_fd)
{
	_operators.insert(client_fd);
}

void Channel::removeOperator(int client_fd)
{
	std::set<int>::iterator it;
	it = _operators.find(client_fd);
	if (it != _operators.end())
		_operators.erase(it);
}

void Channel::addInvited(int client_fd)
{
	_invited.insert(client_fd);
}

bool Channel::isInvited(int client_fd) const
{
	std::set<int>::iterator it;
	it = _invited.find(client_fd);
	if (it == _invited.end())
		return false;
	return true;
}

bool Channel::isOperator(int client_fd) const
{
	std::set<int>::iterator it;
	it = _operators.find(client_fd);
	if (it != _operators.end())
		return true;
	return false;
}

void Channel::broadcastMessage(std::string message, std::map<int, Client>& _clients)
{
	for (size_t i = 0; i < _channelClients.size(); i++)
	{
		int client_fd = _channelClients[i];

        std::map<int, Client>::iterator it = _clients.find(client_fd);
        if (it != _clients.end())
			sendReply(client_fd, message);
	}
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

std::string Channel::getAllUsersNames(std::map<int, Client>& _clients)
{
    std::string result;

    for (size_t i = 0; i < _channelClients.size(); i++)
    {
        int client_fd = _channelClients[i];

        std::map<int, Client>::iterator it = _clients.find(client_fd);
        if (it == _clients.end())
            continue;

        if (isOperator(client_fd))
            result += "@" + it->second.getNickname() + " ";
        else
            result += it->second.getNickname() + " ";
    }

    return result;
}

bool Channel::isClientInChannel(int client_fd)
{
    return std::find(_channelClients.begin(), _channelClients.end(), client_fd) != _channelClients.end();
}


std::string Channel::getChannelModes()
{
    std::string modes = "+";

    if (_inviteOnly)
        modes += "i";
    if (_topicLock)
        modes += "t";
    if (!_key.empty())
        modes += "k";
    if (_userLimit > 0)
        modes += "l";

    return modes;
}


size_t Channel::getUserCount(void) const
{
	return _channelClients.size();
}