#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <iostream>

class Client
{
	private :
		std::string _nickname;
		std::string _username;
		std::string _hostname;
		std::string _servername;
		std::string _realname;
		std::string _password;
		bool _registered;
		int _authStatus; // Bitwise flag for authentication status
	public :
		Client(void);
		Client(std::string nickname);
		~Client(void);
		Client &operator = (Client const &other);
		const std::string &getNickname(void) const;
		void setPassword(const std::string &password);
		const std::string &getPassword() const;
		bool isRegistered() const;
		void setRegistered(bool registered);
		void setNickname(const std::string &nickname);
		void setUsername(const std::string &username);
		void setHostname(const std::string &hostname);
		void setServername(const std::string &servername);
		void setRealname(const std::string &realname);
		void setAuthStatus(int status);
		int getAuthStatus() const;
		bool isFullyAuthenticated() const;
};

#endif