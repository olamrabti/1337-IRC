#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <iostream>

class Client
{
	private :
		std::string _nickname;
		std::string _username;
	public :
		Client(void);
		Client(std::string nickname);
		~Client(void);
		Client &operator = (Client const &other);
		const std::string &getNickname(void) const;
};

#endif