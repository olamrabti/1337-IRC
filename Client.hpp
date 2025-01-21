#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>

class Client
{
private:
	int _client_fd;
	std::string _nickname;
	std::string _username;
	std::string _hostname;
	std::string _servername;
	std::string _realname;
	// std::string _password;
	bool _registered;
	int _authStatus;
	int _nickFlag;

public:
	Client(void);
	Client(std::string nickname);
	Client(int fd);
	~Client(void);

	int getClientFd(void) const;
	void setClientFd(int fd);
	std::string getHostName(void) const;
	std::string getRealName(void) const;
	std::string getServerName(void) const;
	const std::string &getNickname(void) const;

	const std::string &getPassword() const;
	bool isRegistered() const;
	void setRegistered(bool registered);
	void setNickname(const std::string &nickname);
	void setUsername(const std::string &username);
	void setHostname(const std::string &hostname);
	const std::string &getUsername(void) const;

	void setServername(const std::string &servername);
	void setRealname(const std::string &realname);
	void setAuthStatus(int status);
	int getAuthStatus() const;
	bool isFullyAuthenticated() const;
	int getNickFlag() const;
	void setNickFlag(int flag);

	std::string getPrefix(void) const;
};

bool isValidChannelName(const std::string &name);

#endif