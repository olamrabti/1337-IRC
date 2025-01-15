#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <iostream>
#include <vector>

#include "Client.hpp"
#include "Server.hpp"

class Channel
{
private:
    std::string _name;
    std::string _topic;
    std::string _key;
    std::map<std::string, Client> _clients; // TODO : Change to vector and use Clien as * ponter
    std::set<std::string> _operators;
    std::set<std::string> _invited;
    size_t _userLimit; // User limit for +l mode
    bool _inviteOnly;  // Invite-only mode (+i)
    bool _topicLock;   // Topic lock mode (+t)

public:
    Channel(void);
    Channel(const std::string &name, const std::string &key);
    ~Channel(void);

    const std::string &getName(void) const;
    const std::string &getTopic(void) const;
    const std::string &getKey(void) const;
    std::map<std::string, Client>& getClients(void);
    bool isOperator(const std::string &nickname) const;
    size_t getUserCount(void) const;
    size_t getUserLimit(void) const;
    bool getInviteOnly(void) const;
    bool getTopicLock(void) const;
    std::set<std::string> getOperators(void) const;

    // // Setters
    void setTopic(const std::string &topic);
    void setKey(const std::string &key);
    void setUserLimit(size_t limit);
    void setInviteOnly(bool status);
    void setTopicLock(bool status);

    // // Client Management
    bool addClient(Client &client);
    bool removeClient(const std::string &nickname);
    void addOperator(const std::string &nickname);
    void removeOperator(const std::string &nickname);
    void addInvited(const std::string &nickname);
    // void removeInvited(const std::string &nickname);

    // // Key Verification
    bool verifyKey(const std::string &key) const;
    bool isValidChannelName(const std::string &name) const;

    bool isInvited(const std::string &nickname) const;

};

std::map<std::string, std::string> parseJoinCommand(std::string message);
std::vector<std::string> split(const std::string &str, char delimiter);
std::string trimString(const std::string &input);

#endif