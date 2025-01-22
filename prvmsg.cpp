#include "Server.hpp"
#include <sstream>

int Server::getClientByNickname(const std::string &nickname) const
{
    for (std::map<int, Client>::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it->second.getNickname() == nickname)
            return it->first;
    }
    return -1;
}

void Server::broadcastToChannel(const std::string &channel_name, const std::string &sender, const std::string &message)
{
    std::map<std::string, Channel>::iterator channel_it = _channels.find(channel_name);
    if (channel_it != _channels.end())
    {
        std::map<std::string, Client> &clients_in_channel = channel_it->second.getClients();
        if(clients_in_channel.find(sender) == clients_in_channel.end())
        {
            sendReply(_clients[getClientByNickname(sender)].getClientFd(), ERR_CANNOTSENDTOCHAN(sender, channel_name));
            return;
        }
        for (std::map<std::string, Client>::iterator client_it = clients_in_channel.begin(); client_it != clients_in_channel.end(); ++client_it)
        {
            if (client_it->first != sender)
            {
                std::string formatted_msg = ":" + sender + " PRIVMSG " + channel_name + " :" + message;
                sendReply(client_it->second.getClientFd(), formatted_msg);
            }
        }
    }
    else
    {
        sendReply(_clients[getClientByNickname(sender)].getClientFd(), ERR_NOSUCHCHANNEL(sender, channel_name));
    }
}

void Server::sendToClient(const std::string &target_nick, const std::string &sender_nick, const std::string &message)
{
    int target_fd = getClientByNickname(target_nick);
    if (target_fd != -1)
    {
        std::string formatted_msg = ":" + sender_nick + " PRIVMSG " + target_nick + " :" + message;
        sendReply(target_fd, formatted_msg);
    }
    else
    {
        sendReply(_clients[getClientByNickname(sender_nick)].getClientFd(), ERR_NOSUCHNICK(sender_nick, target_nick));
    }
}

void Server::handleDCCCommand(int client_fd, const std::string &target, const std::string &message)
{
    std::istringstream iss(message);
    std::string dcc, type, filename, address, port_str, size_str;
    iss >> dcc >> type >> filename >> address >> port_str >> size_str;

    if (dcc != "DCC" || type != "SEND")
    {
        sendReply(client_fd, ERR_UNKNOWNCOMMAND(_clients[client_fd].getNickname(), "PRIVMSG"));
        return;
    }

    // Send DCC SEND command to the target client
    std::string sender_nick = _clients[client_fd].getNickname();
    std::string formatted_msg = ":" + sender_nick + " PRIVMSG " + target + " :" + message;
    sendToClient(target, sender_nick, formatted_msg);
}

void Server::PrivMsgCommand(int client_fd, std::vector<std::string> command, std::string &buffer)
{
    if (command.size() < 2)
    {
        sendReply(client_fd, ERR_NORECIPIENT(_clients[client_fd].getNickname()));
        return;
    }

    if (command.size() < 3)
    {
        sendReply(client_fd, ERR_NOTEXTTOSEND(_clients[client_fd].getNickname()));
        return;
    }

    std::string target = command[1];
    std::string message = buffer.substr(buffer.find(':') + 1);

    std::string sender_nick = _clients[client_fd].getNickname();
    std::vector<std::string> target_list = split(target, ',');

    for (size_t i = 0; i < target_list.size(); ++i)
    {
        std::string target = target_list[i];
        if (target[0] == '#')
        {
            broadcastToChannel(target, sender_nick, message);
        }
        else if (target[0] == '$' || target[0] == '#')
        {
            sendReply(client_fd, ERR_UNKNOWNCOMMAND(_clients[client_fd].getNickname(), "PRIVMSG"));
        }
        else
        {
            if (message.find("DCC SEND") != std::string::npos)
            {
                handleDCCCommand(client_fd, target, message);
            }
            else
                sendToClient(target, sender_nick, message);
        }
    }
}