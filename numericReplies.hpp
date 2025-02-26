#ifndef NUMERICREPLIES
#define NUMERICREPLIES

// Operator-related replies
#define RPL_YOUREOPER(client) (":localhost 381 " + client + " :You are now an IRC operator\r\n")

// Mode-related errors
#define ERR_UMODEUNKNOWNFLAG(client, channel, flag) (":localhost 501 " + client + " :Unknown MODE " + flag + "\r\n")
#define ERR_INVALIDMODEPARAM(client, channel, mode) (":localhost 696 " + client + " " + channel + " " + mode + " :Invalid MODE parameter\r\n")
#define ERR_UNKNOWNMODE(hostname, nick, c) ":" + hostname + " 472 " + nick + " " + c + " :is unknown mode char to me\r\n"

// Channel-related errors
#define ERR_INVITEONLYCHAN(client, channel) (":localhost 473 " + client + " " + channel + " :Cannot join channel (+i) - invite only\r\n")
#define ERR_NOSUCHCHANNEL(hostname, nick, channel) ":" + hostname + " 403 " + nick + " " + channel + " :No such channel\r\n"
#define ERR_CHANOPRIVSNEEDED(hostname, nick, chann) ":" + hostname + " 482 " + nick + " " + chann + " :You're not channel operator\r\n"
#define ERR_USERNOTINCHANNEL(hostname, nick, chann) ":" + hostname + " 441 " + nick + " " + chann + " :They aren't on that channel\r\n"
#define ERR_KEYSET(hostname, nick, chann) ":" + hostname + " 467 " + nick + " " + chann + " :Channel key already set\r\n"
#define ERR_USERONCHANNEL(hostname, nick, nick2, chann) ":" + hostname + " 443 " + nick + " " + nick2 + " " + chann + " :is already on channel\r\n"
#define ERR_NOTONCHANNEL(hostname, chann) ":" + hostname + " 442 " + chann + " " + ":You're not on that channel\r\n"
#define ERR_CANNOTSENDTOCHAN(hostname, nick, channel) ":" + hostname + " 404 " + nick + " " + channel + " :Cannot send to channel\r\n"
#define ERR_CHANNELISFULL(hostname, nick, channelName) ":" + hostname + " 471 " + nick + " " + channelName + " :Cannot join channel, Channel is full (+l)\r\n"
#define ERR_BADCHANNELKEY(nick, hostname, channelName) ":" + hostname + " 475 " + nick + " " + channelName + " :Cannot join channel (+K) - bad key\r\n"
#define ERR_INVITEONLY(hostname, nick, channelName) ":" + hostname + " 473 " + nick + " " + channelName + " :Cannot join channel, you must be invited (+i)\r\n"

// Topic-related replies
#define RPL_TOPICWHOTIME(client, channel, setter, datetime) (": 333 " + client + " " + channel + " " + setter + " " + datetime + " \r\n")
#define RPL_TOPIC(hostname, nick, chann, topic) ":" + hostname + " 332 " + nick + " " + chann + " :" + topic + "\r\n"
#define RPL_NOTOPIC(hostname, nick, chann) ":" + hostname + " 331 " + nick + " " + chann + " :No topic is set.\r\n"

// Nickname-related errors
#define ERR_NOSUCHNICK(hostname, nick, nick2) ":" + hostname + " 401 " + nick + " " + nick2 + " :No such nick\r\n"
#define ERR_NONICKNAMEGIVEN(nick, hostname) ":" + hostname + " 431 " + nick + " :No nickname given !\r\n"
#define ERR_NICKNAMEINUSE(nickname) ": 555 * " + nickname + " :Nickname already taken, please try again\r\n"
#define ERR_ERRONEUSNICKNAME(nick, nickname, hostname) ":" + hostname + " 432 " + nick + " " + nickname + " :Erroneous nickname\r\n"

// Registration and authentication errors
#define ERR_PASSWDMISMATCH(nick, hostname) ":" + hostname + " 464 " + nick + " :Password incorrect !\r\n"
#define ERR_ALREADYREGISTERED(nick, hostname) ":" + hostname + " 462 " + nick + " :You may not reregister !\r\n"

// Channel mode replies
#define RPL_CHANNELMODEIS(servername, nick, channel, modes) ":" + servername + " 324 " + nick + " " + channel + " " + modes + "\r\n"

// Invite-related replies
#define RPL_INVITING(hostname, nick, invited, chann) ":" + hostname + " 341 " + nick + " " + invited + " " + chann + " :Inviting " + invited + " to " + chann + "\r\n"
#define RPL_INVITE(nick, username, clienthostname, channel, nick2) ":" + nick + "!~" + username + "@" + clienthostname + " INVITE " + nick2 + " " + channel + "\r\n"

// Join and part-related replies
#define RPL_JOIN(nick, username, channelname, ipaddress) ":" + nick + "!~" + username + "@" + ipaddress + " JOIN " + channelname + "\r\n"
#define RPL_NAMREPLY(hostname, clients, channelname, nick) ":" + hostname + " 353 " + nick + " = " + channelname + " :" + clients + "\r\n"
#define RPL_ENDOFNAMES(hostname, nick, channelname) ":" + hostname + " 366 " + nick + " " + channelname + " :END of /NAMES list\r\n"

// Message-related replies
#define PRIVMSG_FORMAT(senderNick, senderUsername, senderHostname, receiver, message) ":" + senderNick + "!~" + senderUsername + "@" + senderHostname + " PRIVMSG " + receiver + " :" + message + "\r\n"

// Kick-related replies
#define RPL_KICK(nick, username, hostname, kicked, channel, reason) ":" + nick + "!" + "~" + username + "@" + hostname + " KICK " + channel + " " + kicked + " :" + reason + "\r\n"

// Channel creation time reply
#define RPL_CREATIONTIME(hostname, nickname, channelname, creationtime) ":" + hostname + " 329 " + nickname + " " + channelname + " " + creationtime + "\r\n"

// Parameter-related errors
#define ERR_NEEDMOREPARAMS(nick, hostname, cmd) ":" + hostname + " 461 " + nick + " " + cmd + " :Not enough parameters\r\n"

#endif