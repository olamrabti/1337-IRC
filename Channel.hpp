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
    std::map<std::string, Client> _clients;
    std::set<std::string> _operators;
    std::set<std::string> _invited;
    size_t _userLimit;
    bool _inviteOnly;
    bool _topicLock;

public:
    Channel(void);
    Channel(const std::string &name, const std::string &key);
    ~Channel(void);

    const std::string &getName(void) const;
    const std::string &getTopic(void) const;
    const std::string &getKey(void) const;
    std::map<std::string, Client> &getClients(void);
    bool isOperator(const std::string &nickname) const;
    size_t getUserCount(void) const;
    size_t getUserLimit(void) const;
    bool getInviteOnly(void) const;
    bool getTopicLock(void) const;
    std::set<std::string> getOperators(void) const;
    std::set<std::string> getInvited(void) const;
    std::string getCreationDate(void) const;
    std::string getTopicDdate(void) const;
    std::string getTopicSetter(void) const;

    // // Setters
    void setTopic(const std::string &topic);
    void setKey(const std::string &key);
    void setUserLimit(size_t limit);
    void setInviteOnly(bool status);
    void setTopicLock(bool status);
    void setCreationDate(std::string date);
    void setTopicDate(std::string date);
    void setTopicSetter(std::string client);

    // // Client Management
    bool addClient(Client &client);
    bool removeClient(const std::string &nickname);
    void addOperator(const std::string &nickname);
    void removeOperator(const std::string &nickname);
    void addInvited(const std::string &nickname);
    // void removeInvited(const std::string &nickname);
    bool isClientInChannel(std::string nickname);

    // // Key Verification
    bool verifyKey(const std::string &key) const;
    bool isInvited(const std::string &nickname) const;
    void broadcastMessage(std::string message);
    std::string getAllUsersNames(void);
};

std::map<std::string, std::string> parseJoinCommand(std::vector<std::string> message);
std::vector<std::string> split(const std::string &str, char delimiter);
std::string trimString(const std::string &input);

std::string getCurrTime(void);

#endif