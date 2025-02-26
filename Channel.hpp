#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>

#include "Client.hpp"
#include "Server.hpp"

class Client;

class Channel
{
private:
    std::string _name;
    std::string _topic;
    std::string _key;
    std::string _creationDate;
    std::string _topicDate;
    std::string _topicSetter;
    std::vector<int> _channelClients;
    std::set<int> _operators;
    std::set<int> _invited;
    size_t _userLimit;
    bool _inviteOnly;
    bool _topicLock;

public:
    Channel(void);
    Channel(const std::string &name, const std::string &key);
    ~Channel(void);

    // getter
    const std::string &getName(void) const;
    const std::string &getTopic(void) const;
    const std::string &getKey(void) const;
    std::vector<int> &getClients(void);
    bool isOperator(int client_fd) const;
    size_t getUserCount(void) const;
    size_t getUserLimit(void) const;
    bool getInviteOnly(void) const;
    bool getTopicLock(void) const;
    std::set<int> getOperators(void) const;
    std::set<int> getInvited(void) const;
    std::string getCreationDate(void) const;
    std::string getTopicDdate(void) const;
    std::string getTopicSetter(void) const;

    // Setters
    void setTopic(const std::string &topic);
    void setKey(const std::string &key);
    void setUserLimit(size_t limit);
    void setInviteOnly(bool status);
    void setTopicLock(bool status);
    void setCreationDate(std::string date);
    void setTopicDate(std::string date);
    void setTopicSetter(std::string client);

    // Client Management
    void addClient(int client_fd);
    bool removeClientFromChannel(int client_fd);
    void addOperator(int);
    void removeOperator(int client_fd);
    void addInvited(int client_fd);
    bool isClientInChannel(int Client_fd);

    // Key Verification
    bool verifyKey(const std::string &key) const;
    bool isInvited(int client_fd) const;
    void broadcastMessage(std::string message, std::map<int, Client>& _clients);
    std::string getAllUsersNames(std::map<int, Client>& _clients);
    std::string getChannelModes();

};

std::map<std::string, std::string> parseJoinCommand(std::vector<std::string> message);
std::vector<std::string> split(const std::string &str, char delimiter);
std::string trimString(const std::string &input);
std::string getCurrTime(void);

#endif