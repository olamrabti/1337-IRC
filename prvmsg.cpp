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

void Server::PrivMsgCommand(int client_fd, std::vector<std::string> command)
{
    std::cerr << "prv message " << std::endl;
    if (command.size() < 3)
    {
        std::cerr << "ach wa93 ? " << std::endl;
        // TODO numerical response of this shit should be sent
        return;
    }

    std::string target = command[1];

    std::string message;
    for (size_t i = 2; i < command.size(); ++i)
    {
        if (i == 2 && !command[i].empty() && command[i][0] == ':')
            message += command[i].substr(1);
        else
            message += command[i];
        if (i != command.size() - 1)
            message += " ";
    }

    if (target[0] == '#')
    {
        std::map<std::string, Channel>::iterator channel_it = _channels.find(target);
        if (channel_it != _channels.end())
        {
            std::map<std::string, Client> &clients_in_channel = channel_it->second.getClients();
            std::string sender_nick = _clients[client_fd].getNickname();

            for (std::map<std::string, Client>::iterator client_it = clients_in_channel.begin(); client_it != clients_in_channel.end(); ++client_it)
            {
                if (client_it->first != sender_nick)
                {
                    std::string formatted_msg = ":" + sender_nick + " PRIVMSG " + target + " :" + message + "\r\n";
                    send(client_it->second.getClientFd(), formatted_msg.c_str(), formatted_msg.size(), 0);
                }
            }
        }
        else
        {
            std::cerr << "No such Channel : " << channel_it->second.getName() << std::endl;
            // TODO Send error reply: No such channel
        }
    }
    else
    {
        int target_fd = getClientByNickname(target);
        if (target_fd != -1)
        {
            std::string formatted_msg = ":" + _clients[client_fd].getNickname() + " PRIVMSG " + target + " :" + message + "\r\n";
            send(target_fd, formatted_msg.c_str(), formatted_msg.size(), 0);
        }
        else
        {
            // TODO numerical response of this shit should be sent
            std::cerr << "NO such USER : " << target << std::endl;
        }
    }
}