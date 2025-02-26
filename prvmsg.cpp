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
    if (channel_it == _channels.end())
    {
        sendReply(client.getClientFd(), ERR_NOSUCHCHANNEL(client.getHostName(), client.getNickname(), channel_name));
        return;
    }

    Channel &channel = channel_it->second;
    std::vector<int> &clients_in_channel = channel.getClients();

    if (std::find(clients_in_channel.begin(), clients_in_channel.end(), client.getClientFd()) == clients_in_channel.end())
    {
        sendReply(client.getClientFd(), ERR_CANNOTSENDTOCHAN(client.getHostName(), client.getNickname(), channel_name));
        return;
    }

    std::string formatted_msg = ":" + client.getNickname() + "!" + client.getUsername() + "@" + client.getHostName() + " PRIVMSG " + channel_name + " :" + message + "\r\n";
    for (std::vector<int>::iterator it = clients_in_channel.begin(); it != clients_in_channel.end(); ++it)
    {
        if (*it != client.getClientFd())
        {
            std::map<int, Client>::iterator target_client = _clients.find(*it);
            if (target_client != _clients.end())
            {
                sendReply(target_client->second.getClientFd(), formatted_msg);
            }
        }
    }
}

void Server::sendToClient(const std::string &target_nick, Client &client, const std::string &message)
{
    int target_fd = getClientByNickname(target_nick);
    if (target_fd != -1 && _clients[target_fd].isFullyAuthenticated())
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
        sendReply(client.getClientFd(), ERR_NEEDMOREPARAMS(client.getNickname(), client.getHostName(), "PRIVMSG"));
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
        if (target == "SECBOT")
        {
            std::vector<std::string> bots_msg;
            bots_msg.push_back("SECBOT");
            bots_msg.push_back(message);
            BotCommand(client.getClientFd(), bots_msg);
        }

        else if (target[0] == '#' || target[0] == '&')
        {
            std::map<std::string, Channel>::iterator channel_it = _channels.find(target);
            if (channel_it == _channels.end())
                sendReply(client.getClientFd(), ERR_NOSUCHCHANNEL(client.getHostName(), client.getNickname(), target));
            else if (!channel_it->second.isClientInChannel(client.getClientFd()))
                sendReply(client.getClientFd(), ERR_NOTONCHANNEL(client.getHostName(), target));
            else
                broadcastToChannel(client, target, message);
        }
        else
            sendToClient(target, client, message);
    }
}