#include "Server.hpp"

int Server::getClientByNickname(const std::string &nickname) const
{
    for (std::map<int, Client>::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it->second.getNickname() == nickname)
            return it->first;
    }
    return -1;
}

void Server::broadcastToChannel(Client &client, const std::string &channel_name, const std::string &message)
{
    std::map<std::string, Channel>::iterator channel_it = _channels.find(channel_name);
    if (channel_it != _channels.end())
    {
        std::map<std::string, Client> &clients_in_channel = channel_it->second.getClients();
        if (clients_in_channel.find(client.getNickname()) == clients_in_channel.end())
        {
            sendReply(client.getClientFd(), ERR_CANNOTSENDTOCHAN(client.getHostName(), client.getNickname(), channel_name));
            return;
        }

        for (std::map<std::string, Client>::iterator client_it = clients_in_channel.begin(); client_it != clients_in_channel.end(); ++client_it)
        {
            if (client_it->first != client.getNickname())
            {
                std::string formatted_msg = PRIVMSG_FORMAT(client.getNickname(), client.getUsername(), client.getHostName(), channel_name, message);
                sendReply(client_it->second.getClientFd(), formatted_msg);
            }
        }
    }
    else
    {
        sendReply(client.getClientFd(), ERR_NOSUCHCHANNEL(client.getHostName(), client.getNickname(), client.getNickname()));
    }
}

void Server::sendToClient(const std::string &target_nick, Client &client, std::string &message)
{
    int target_fd = getClientByNickname(target_nick);
    if (target_fd != -1)
    {
        std::string formatted_msg = PRIVMSG_FORMAT(client.getNickname(), client.getUsername(), client.getHostName(), target_nick, message);
        sendReply(target_fd, formatted_msg);
    }
    else
    {
        sendReply(client.getClientFd(), ERR_NOSUCHNICK(client.getHostName(), client.getNickname(), target_nick));
    }
}

void Server::PrivMsgCommand(Client &client, std::vector<std::string> command, std::string &buffer)
{
    if (command.size() < 3)
    {
        sendReply(client.getClientFd(), ERR_NEEDMOREPARAMS(_hostname, client.getNickname(), "PRIVMSG"));
        return;
    }
    std::string target = command[1];
    std::string message = command[2];
    if (message[0] == ':')
        message = buffer.substr(buffer.find(':') + 1);
    message.erase(std::remove(message.begin(), message.end(), '\n'), message.end());
    message.erase(std::remove(message.begin(), message.end(), '\r'), message.end());

    std::string sender_nick = client.getNickname();
    std::vector<std::string> target_list = split(target, ',');

    for (size_t i = 0; i < target_list.size(); ++i)
    {
        std::string target = target_list[i];
        if (target[0] == '#' || target[0] == '&')
        {
            std::map<std::string, Channel>::iterator channel_it = _channels.find(target);
            if (channel_it == _channels.end())
                sendReply(client.getClientFd(), ERR_NOSUCHCHANNEL(client.getHostName(), client.getNickname(), target));
            else if (!channel_it->second.isClientInChannel(sender_nick))
                sendReply(client.getClientFd(), ERR_CANNOTSENDTOCHAN(client.getHostName(), client.getNickname(), target));
            else
                broadcastToChannel(client, target, message);
        }
        else
            sendToClient(target, client, message);
    }
}