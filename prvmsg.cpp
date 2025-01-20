// :Angel PRIVMSG Wiz :Hello are you receiving this message ?
//                                 ; Message from Angel to Wiz.

// PRIVMSG Angel :yes I'm receiving it !receiving it !'u>(768u+1n) .br ;
//                                 Message to Angel.

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

void Server::broadcastToChannel(const std::string &channel_name, const std::string &sender, const std::string &message)
{
    std::map<std::string, Channel>::iterator channel_it = _channels.find(channel_name);
    if (channel_it != _channels.end())
    {
        std::map<std::string, Client> &clients_in_channel = channel_it->second.getClients();
        for (std::map<std::string, Client>::iterator client_it = clients_in_channel.begin(); client_it != clients_in_channel.end(); ++client_it)
        {
            if (client_it->first != sender)
            {
                std::string formatted_msg = ":" + sender + " PRIVMSG " + channel_name + " :" + message;
                send(client_it->second.getClientFd(), formatted_msg.c_str(), formatted_msg.size(), 0);
            }
        }
    }
    else
    {
        std::cerr << "No such Channel: " << channel_name << std::endl;
        // Send error reply: No such channel
    }
}

void Server::sendToClient(const std::string &target_nick, const std::string &sender_nick, const std::string &message)
{
    int target_fd = getClientByNickname(target_nick);
    if (target_fd != -1)
    {
        std::string formatted_msg = ":" + sender_nick + " PRIVMSG " + target_nick + " :" + message;
        send(target_fd, formatted_msg.c_str(), formatted_msg.size(), 0);
    }
    else
    {
        std::cerr << "No such User: " << target_nick << std::endl;
        // Send error reply: No such nick/channel
    }
}

void Server::PrivMsgCommand(int client_fd, std::vector<std::string> command, std::string &buffer)
{
    std::cerr << "prv message " << std::endl;
    if (command.size() < 3)
    {
        std::cerr << "ach wa93 ? " << std::endl;
        // TODO numerical response of this shit should be sent
        return;
    }

    std::string target = command[1];
    std::string message = buffer.substr(buffer.find(':') + 1);

    // std::string message;
    // for (size_t i = 2; i < command.size(); ++i)
    // {
    //     if (i == 2 && !command[i].empty() && command[i][0] == ':')
    //         message += command[i].substr(1);
    //     else
    //         message += command[i];
    //     if (i != command.size() - 1)
    //         message += " ";
    // }

    std::string sender_nick = _clients[client_fd].getNickname();
    std::vector<std::string> target_list = split(target, ',');

    for (size_t i = 0; i < target_list.size(); ++i)
    {
        std::string target = target_list[i];
        if (target[0] == '#')
            broadcastToChannel(target, sender_nick, message);
        else
            sendToClient(target, sender_nick, message);
    }
}