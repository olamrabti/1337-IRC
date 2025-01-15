#include "Server.hpp"

void Server::channelMode(int client_fd, std::vector<std::string> command) // TODO to perform a MODE command you need to be an operator
{
    if (command.size() < 3)
    {
        std::cout << "Error" << std::endl;
        return ;
    }
    std::string channelName = command[1];
    std::string mode = command[2];
    std::string parameter = command[3];
    std::map<std::string, Channel>::iterator it;
    it = _channels.find(channelName);
    if (it == _channels.end())
    {
        std::cout << "Error: channel " << channelName << " does not exist" << std::endl;
        return;
    }
    else
    {
        Client currClient = _clients[client_fd];
        Channel currChannel = it->second;
        if (currChannel.isOperator(currClient.getNickname()) == false)
        {
            std::cout << "Error: " << currClient.getNickname() << " is not an operator in channel " << channelName << std::endl;
            return;
        }
        if (mode == "+o")
        {
            // user need to be in the channel and need to be an operator
            std::map<std::string, Client>::iterator it_client = currChannel.getClients().find(parameter);
            if (it_client == currChannel.getClients().end())
            {
                std::cout << "Error: " << parameter << " is not in channel " << channelName << std::endl;
                return;
            }
            if (currChannel.isOperator(parameter))
            {
                std::cout << "Error: " << parameter << " is already an operator in channel " << channelName << std::endl;
                return;
            }
            currChannel.addOperator(parameter);
        }
        else if (mode == "-o")
        {
            // user need to be in the channel and need to be an operator
            std::map<std::string, Client>::iterator it_client = currChannel.getClients().find(parameter);
            if (it_client == currChannel.getClients().end())
            {
                std::cout << "Error: " << parameter << " is not in channel " << channelName << std::endl;
                return;
            }
            currChannel.removeOperator(parameter);
        }
        else if (mode == "+i")
        {
            if (command.size() != 3)
            {
                std::cout << "Error: invalid mode command try MODE <channel> {+i|-i}" << std::endl;
            }
            currChannel.setInviteOnly(true);
        }
        else if (mode == "-i")
        {
            if (command.size() != 3)
            {
                std::cout << "Error: invalid mode command try MODE <channel> {+i|-i}" << std::endl;
            }
            currChannel.setInviteOnly(false);
        }
        else if (mode == "+k")
        {
            if (command.size() != 4)
            {
                std::cout << "Error: invalid mode command try MODE <channel> {+k|-k} <key>" << std::endl;
            }
            currChannel.setKey(parameter);
        }
        else if (mode == "-k")
        {
            if (command.size() != 3)
            {
                std::cout << "Error: invalid mode command try MODE <channel> {+k|-k} <key>" << std::endl;
            }
            currChannel.setKey("");
        }
        else if (mode == "+l")
        {
            if (command.size() != 4)
            {
                std::cout << "Error: invalid mode command try MODE <channel> {+l|-l} <limit>" << std::endl;
            }
            // TODO parce the parameter
            currChannel.setUserLimit(std::stoi(parameter));
        }
        else if (mode == "-l")
        {
            if (command.size() != 3)
            {
                std::cout << "Error: invalid mode command try MODE <channel> {+l|-l} <limit>" << std::endl;
            }
            currChannel.setUserLimit(0);
        }
        else if (mode == "+t")
        {
            if (command.size() != 3)
            {
                std::cout << "Error: MODE <channel> {+t|-t}" << std::endl;
            }
            currChannel.setTopicLock(true);
        }
        else if (mode == "-t")
        {
            if (command.size() != 3)
            {
                std::cout << "Error: MODE <channel> {+t|-t}" << std::endl;
            }
            currChannel.setTopicLock(false);
        }
        else
        {
            std::cout << "Error: invalid mode" << std::endl;
            return;
        }

    }
}
