#include "Server.hpp"
#include "numericReplies.hpp"

void Server::joinCommand(std::string channelName, std::string key, int client_fd)
{
    Client currClient = _clients[client_fd];
	std::map<std::string, Channel>::iterator it;
    it = _channels.find(channelName);
    if (it == _channels.end())
    {
        if (!isValidChannelName(channelName))
        {
		    // sendReply(client_fd, ERR_BADCHANMASK, channelName + " :Invalid channel name");
            return ;
        }
        Channel newChannel(channelName, key);
        newChannel.addClient(currClient);
        newChannel.addOperator(currClient.getNickname());
        _channels[channelName] = newChannel;
        // sendReply(client_fd, RPL_TOPIC, channelName + " :" + newChannel.getTopic());
        // std::cout << "Channel " << channelName << " created" << std::endl;
    }
    else
    {
        // std::cout << "Channel " << channelName << " already exists" << std::endl;
        Channel currChannel = it->second;
        if (currChannel.getInviteOnly() && !currChannel.isInvited(currClient.getNickname())) {
            // sendReply(client_fd, ERR_INVITEONLYCHAN, channelName + " :Cannot join channel (+i)");
            return;
        }

        if (currChannel.getUserLimit() != 0 && currChannel.getUserCount() >= currChannel.getUserLimit())
        {
            // sendReply(client_fd, ERR_CHANNELISFULL, channelName + " :Cannot join channel (+l)");
            return;
        }

        if (currChannel.getKey() != key) {
            // sendReply(client_fd, ERR_BADCHANNELKEY, channelName + " :Cannot join channel (+k)");
            return;
        }

        if (currChannel.getClients().find(currClient.getNickname()) != currChannel.getClients().end()) {
            // sendReply(client_fd, "NOTICE", ":You are already in the channel");
            return;
        }

        currChannel.addClient(currClient);
        sendReply(client_fd, "");
    }
}


void Server::ChannelJoin(int client_fd, std::vector<std::string> command)
{
    std::cout << "mre7ba \n";
    if (command.size() < 2)
    {
        sendReply(client_fd , ERR_NEEDMOREPARAMS(_clients[client_fd].getNickname(), command[0]));
        return;
    }
	std::map<std::string, std::string> tokens = parseJoinCommand(command);
    if (tokens.size() == 0)
    {
        std::cout << "Error: invalid JOIN command" << std::endl;
        return;
    }
	std::map<std::string, std::string>::iterator it;
	for (it = tokens.begin(); it != tokens.end(); it++)
		joinCommand(it->first, it->second, client_fd);
}
