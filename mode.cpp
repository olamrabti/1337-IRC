#include "Server.hpp"

bool isValidMode(char c)
{
    return (c == 'i' || c == 't' || c == 'k' || c == 'o' || c == 'l');
}

std::vector<std::string> parseModes(const std::string &modes)
{
    std::vector<std::string> result;
    // std::cout << "|modes:| " << modes << std::endl;
    bool give = true;
    for (size_t i = 0; i < modes.size(); i++)
    {
        if (modes[i] == '+')
            give = true;
        else if (modes[i] == '-')
            give = false;
        else if (isValidMode(modes[i]))
            result.push_back((give ? "+" : "-") + std::string(1, modes[i]));
        else
        {
            std::cout << "Error : invalide MODE type \n";
            return std::vector<std::string>();
        }
    }
    return result;
}

std::vector<std::string> parseParametres(std::vector<std::string> command)
{
    std::vector<std::string> result;
    if (command.size() > 3)
        for (size_t i = 3; i < command.size(); i++)
            result.push_back(command[i]);
    return result;
}

void oModeParam(Channel &currChannel, std::string parameter, std::string mode)
{
    // user need to be in the channel and need to be an operator
    if (parameter.empty())
    {
        std::cout << "ERROR missing parametre\n";
        return;
    }
    if (mode == "+o")
    {
        std::map<std::string, Client>::iterator it_client;
        it_client = currChannel.getClients().find(parameter);
        if (it_client == currChannel.getClients().end())
        {
            std::cout << "Error: " << parameter << " is not in channel " << currChannel.getName() << std::endl;
            return;
        }
        if (currChannel.isOperator(parameter))
        {
            std::cout << "Error: " << parameter << " is already an operator in channel " << std::endl;
            return; // TODO
        }
        currChannel.addOperator(parameter);
    }
    else if (mode == "-o")
    {
        std::map<std::string, Client>::iterator it_client;
        it_client = currChannel.getClients().find(parameter);
        if (it_client == currChannel.getClients().end())
        {
            std::cout << "Error: " << parameter << " is not in channel " << currChannel.getName() << std::endl;
            return;
        }
        if (!currChannel.isOperator(parameter))
        {
            std::cout << "Error: " << parameter << " is not an operator in channel " << std::endl;
            return; // TODO
        }
        currChannel.removeOperator(parameter);
    }
}

void iModeParam(Channel &currChannel, std::string mode)
{
    if (mode == "+i")
        currChannel.setInviteOnly(true);
    else if (mode == "-i")
        currChannel.setInviteOnly(false);
}

void pluskModeParam(Channel &currChannel, std::string parameter, std::string mode)
{
    if (mode == "+k")
        currChannel.setKey(parameter);
}

void minuskModeParam(Channel &currChannel, std::string mode)
{
    if (mode == "-k")
        currChannel.setKey("");
}

void minuslModeParam(Channel &currChannel, std::string mode)
{
    if (mode == "-l")
        currChannel.setUserLimit(0);
}

void pluslModeParam(Channel &currChannel, std::string parameter, std::string mode)
{
    std::cout << "currChannel: " << currChannel.getName() << " param: " << parameter << " mode: " << mode << std::endl;
    if (mode == "+l")
    {
        if (parameter.empty())
        {
            std::cout << "ERROR missing limit param\n";
            return;
        }
        // TODO parse param
        currChannel.setUserLimit(std::stoi(parameter));
    }
}

void tModeParam(Channel &currChannel, std::string mode)
{
    if (mode == "+t")
        currChannel.setTopicLock(true);
    else if (mode == "-t")
        currChannel.setTopicLock(false);
}

void Server::channelMode(int client_fd, std::vector<std::string> command)
{
    if (command.size() < 3)
    {
        std::cout << "Error" << std::endl;
        return;
    }
    std::string channelName = command[1];
    std::vector<std::string> modes;
    if (command.size() >= 3)
        modes = parseModes(command[2]);
    if (modes.empty())
    {
        std::cout << "Error: empty modes\n";
        return;
    }
    std::vector<std::string> parameters = parseParametres(command);
    for (auto mode : modes)
        std::cout << "|mode|: " << mode << std::endl;

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
        Channel &currChannel = it->second;

        if (currChannel.isOperator(currClient.getNickname()) == false)
        {
            std::cout << "Error: " << currClient.getNickname() << " is not an operator in channel " << channelName << std::endl;
            return;
        }
        int paramCount = 0;
        for (size_t i = 0; i < modes.size(); i++)
        {
            if (modes[i] == "+o" || modes[i] == "-o")
            {
                if (parameters.size() > paramCount) // TODO
                {
                    oModeParam(currChannel, parameters[paramCount], modes[i]);
                    paramCount++;
                }
                else 
                {
                    std::cout << "error not enough param\n";
                    return;
                }
            }
            else if (modes[i] == "+i" || modes[i] == "-i")
            {
                iModeParam(currChannel, modes[i]);
            }
            else if (modes[i] == "+k" || modes[i] == "-k")
            {
                if (modes[i] == "+k")
                {
                    if (parameters.size() > paramCount) // TODO
                    {
                        pluskModeParam(currChannel, parameters[paramCount], modes[i]);
                        paramCount++;
                    }
                    else 
                    {
                        std::cout << "error not enough param\n";
                        return;
                    }
                }
                else if (modes[i] == "-k")
                    minuskModeParam(currChannel, modes[i]);
            }
            else if (modes[i] == "+l" || modes[i] == "-l")
            {
                if (modes[i] == "+l")
                {
                    std::cout << "paramCount: " << paramCount << std::endl;
                    std::cout << "param size(): " << parameters.size() << std::endl;
                    if (parameters.size() > paramCount) // TODO
                    {
                        pluslModeParam(currChannel, parameters[paramCount], modes[i]);
                        paramCount++;
                    }
                    else 
                    {
                        std::cout << "error not enough param\n";
                        return;
                    }
                }
                else if (modes[i] == "-l")
                    minuslModeParam(currChannel, modes[i]);
            }
            else if (modes[i] == "+t" || modes[i] == "-t")
            {
                tModeParam(currChannel, modes[i]);
            }
            else
            {
                std::cout << "Error: invalid mode" << std::endl;
                return;
            }
        }
    }
}
