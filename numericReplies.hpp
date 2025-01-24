#ifndef NUMERICREPLIES
#define NUMERICREPLIES

#define user_forma(nickname, username, hostname) (":" + nickname + "!" + username + "@" + hostname)
// #define ERR(command) (": 421 !" + command + "\r\n") //
// #define ERR_NONICKNAMEGIVEN (":localhost 431 ! :There is no nickname.\r\n")
// #define ERR_ERRONEUSNICKNAME(nickname) (": 432 ! " + nickname + " :Erroneous nickname\r\n")
// #define RPL_NICK(oclient, uclient, client) (":" + oclient + "!" + uclient + "@localhost NICK " + client + "\r\n")
// #define ERR_NICKNAMEINUSE(client, nickname) (": 433 !" + client + " " + nickname + " :Nickname is already in use.\r\n")
// #define RPL(msg, nickname) (": 001 " + nickname + " : " + msg + "\r\n")


// #define RPL_YOURHOST(client, localhost) (": 002 " + client + " :Your host is " + localhost + "\r\n")
// #define RPL_CREATED(client, datetime) (": 003 " + client + " :This server was created " + datetime + "\r\n")
// #define RPL_ISUPPORT(client, tokens) (":localhost 005 " + client + " " + tokens " :are supported by this server\r\n")
// #define ERR_ALREADYREGISTERED(client) (":localhost 462 " + client + " :You may not reregister.\r\n")
// #define RPL_INVITING(client, nickname, channel) (":localhost 341 " + client + " " + nickname + " " + channel + "\r\n")
// #define RPL_AWAY(client, nickname, away_message) (":localhost 301 " + client + " " + nickname + " :" + away_message + "\r\n")
// #define ERR_PASSWDMISMATCH(client) (":localhost 464 " + client + " :Password incorrect.\r\n")
// #define ERR_PASSINVALID(client) (":localhost 464 " + client + " :Not a Valid Password.\r\n")

// #define ERR_NORECIPIENT(client) (":localhost 411 " + client + " :No recipient given (PRIVMSG)\r\n")
// #define ERR_NOTEXTTOSEND(client) (":localhost 412 " + client + " :No text to send\r\n")
// #define ERR_CANNOTSENDTOCHAN(client, channel) (":localhost 404 " + client + " " + channel + " :Cannot send to channel\r\n")
// #define RPL_PRIVMSG(nick, username, target, message) (":" + nick + "!" + username + "@localhost PRIVMSG " + target + " :" + message + "\r\n")
// #define RPL_NICKCHANGED(Oldnick, client_host, Newnick) (":" + Oldnick + "!" + client_host + " NICK " + Newnick + "\r\n")
// #define ERR_UNKNOWNCOMMAND(client, command) (":localhost 421 " + client + " " + command + " :Unknown command\r\n")
// #define ERR_NOOPERHOST(client) (":localhost 491 " + client + " :No O-lines for your host\r\n")
// #define RPL_YOUREOPER(client) (":localhost 381 " + client + " :You are now an IRC operator\r\n")
// #define RPL_INVITESEND(client, nick, channel) (":localhost 341 " + client + " " + nick + " " + channel + "\r\n")
// #define RPL_INVITENOTIFY(client, nick, channel) (":" + client + "!InviterUser@InviterHost" + " INVITE " + nick + " :" + channel + "\r\n")
// #define ERR_USERNOTINCHANNEL(client, nick, channel) (":localhost 443 " + client + " " + nick + " " + channel + " :user not on channel.\r\n")
// #define ERR_NEEDMOREPARAMS(client, command) (":localhost 461 " + client + " " + command + " :Not enough parameters.\r\n")
// #define ERR_NOTONCHANNEL(client, channel) (":localhost 442 " + client + " " + channel + " :You're not on that channel.\r\n")
// #define RPL_CHANNELMODEIS(client, channel, mode) (":localhost 324 " + client + " " + channel + " " + mode + "\r\n")
// #define RPL_CREATIONTIME(client, channel, datetime) (":localhost 329 " + client + " " + channel + " " + datetime + "\r\n")
// #define MODE_CHANGED(client, client_host, channel, mode, last_param) (":" + client + "!" + client_host + " MODE " + channel + " " + mode + " " + last_param + "\r\n")
// #define ERR_CHANOPRIVSNEEDED(client, channel) (":localhost 482 " + client + " " + channel + " :You're not channel operator.\r\n")
// #define ERR_UMODEUNKNOWNFLAG(client, channel, flag) (":localhost 501 " + client + " :Unknown MODE " + flag + "\r\n")
// #define ERR_INVALIDMODEPARAM(client, channel, mode) (":localhost 696 " + client + " " + channel + " " + mode + " :Invalid MODE parameter\r\n")
// #define ERR_INVALIDKEY(client, channel) (":localhost 525 " + client + " " + channel + " :Cannot join channel (+k) - bad key\r\n")
// #define ERR_CHANNELISFULL(client, channel) (":localhost 471 " + client + " " + channel + " :Cannot join channel (+l) - channel is full\r\n")
#define ERR_INVITEONLYCHAN(client, channel, hostname) (":" + hostname + " 473 " + client + " " + channel + " :Cannot join channel (+i) - invite only\r\n")
// #define ERR_NOSUCHNICK(client, target) (":localhost 401 " + client + " " + target + " :No such nick/channel\r\n")
// #define ERR_NOSUCHCHANNEL(client, channel) (":localhost 403 " + client + " " + channel + " :No such channel\r\n")
// #define ERR_USERONCHANNEL(client, nick, channel) (":localhost 443 " + client + " " + nick + " " + channel + " is already on channel\r\n")
// #define RPL_KICK(client, client_host, channel, kicked, reason) (":" + client + "!" + "Kicker@" + client_host + " KICK " + channel + " " + kicked + " :" + reason + "\r\n");
// #define RPL_NOTIFYQUIT(client, client_host, message) (":" + client + "!" + client_host + " QUIT :" + message + "\r\n")
// #define RPL_NOTIFYPART(client, client_host, channel) (":" + client + "!" + client_host + " PART " + channel + "\r\n")
#define RPL_NOTIFYJOIN(client, client_host, channel) (":" + client + "!" + client + "@" + client_host + " JOIN " + channel + "\r\n")
#define ERR_INVALIDMODEPARAM(client, channel, mode, hostname) (":" + hostname + " 696 " + client + " " + channel + " " + mode + " :Invalid MODE parameter\r\n")
#define RPL_YOUREOPER(client, hostname) (":" + hostname + " 381 " + client + " :You are now an IRC operator\r\n")
#define ERR_UMODEUNKNOWNFLAG(client, channel, flag, hostname) (":" + hostname + " 501 " + client + " :Unknown MODE " + flag + "\r\n")
// #define RPL_JOIN(client, client_host, channel) (":" + client + "!~" + client + "@" + client_host + " JOIN :" + channel + "\r\n")
// #define RPL_NAMREPLY(client, channel, all_users) (": 353 " + client + " = " + channel + " :" + all_users + "\r\n")
// #define RPL_ENDOFNAMES(client, channel) (": 366 " + client + " " + channel + " :End of /NAMES list\r\n")
// #define RPL_CHANNMSG(client, host, channel, message) (":" + client + "!" + host + " PRIVMSG " + channel + "  :" + message + "\r\n")
// #define RPL_TOPIC(client, channel, topic) (": 332 " + client + " " + channel + " :" + topic + " \r\n")
#define RPL_TOPICWHOTIME(client, channel, setter, datetime) (": 333 " + client + " " + channel + " " + setter + " " + datetime + " \r\n")
// #define RPL_NOTOPIC(client, channel) (": 331 " + client + " " + channel + " :No topic is set.\r\n")
// #define RPL_TOPICCHANGE(client, client_host, channel, topic) (":" + client + "!" + client_host + " TOPIC " + channel_name + " :" + topic + " \r\n")
// # define ERR_NOTEXTTOSEND(client) ("412 " + client + " :No text to send\r\n")



#define ERR_UNKNOWNCOMMAND(hostname, nick, arg) ":" + hostname + " 421 " + nick + " " + arg + " :Unknown command\r\n"
#define ERR_NEEDMOREPARAMS(nick, hostname, cmd) ":" + hostname + " 461 " + nick + " " + cmd + " :Not enough parameters\r\n"
#define ERR_NOSUCHCHANNEL(hostname, nick, channel) ":" + hostname + " 403 " + nick + " " + channel + " :No such channel\r\n"
#define RPL_CHANNELMODEIS(servername, nick, channel, modes) ":" + servername + " 324 " + nick + " " + channel + " " + modes + "\r\n"
#define ERR_CHANOPRIVSNEEDED(hostname, nick, chann) ":" + hostname + " 482 " + nick + " " + chann + " :You're not channel operator\r\n"
#define ERR_USERNOTINCHANNEL(hostname, nick, chann) ":" + hostname + " 441 " + nick + " " + chann + " :They aren't on that channel\r\n"
#define ERR_NOSUCHNICK(hostname, nick, nick2) ":" + hostname + " 401 " + nick + " " + nick2 + " :No such nick\r\n"
#define ERR_KEYSET(hostname, nick, chann) ":" + hostname + " 467 " + nick + " " + chann + " :Channel key already set\r\n"
#define ERR_UNKNOWNMODE(hostname, nick, c) ":" + hostname + " 472 " + nick + " " + c + " :is unknown mode char to me\r\n"
#define ERR_NOTREGISTERED(hostname, nick) ":" + hostname + " 451 " + nick + " :You have not registered\r\n"
#define ERR_USERONCHANNEL(hostname, nick, nick2, chann) ":" + hostname + " 443 " + nick + " " + nick2 + " " + chann + " :is already on channel\r\n"
#define RPL_INVITING(hostname, nick, invited, chann) ":" + hostname + " 341 " + nick + " " + invited + " " + chann + " :Inviting " + invited + " to " + chann + "\r\n"
#define ERR_NOTONCHANNEL(hostname, chann) ":" + hostname + " 442 " + chann + " " + ":You're not on that channel\r\n"
#define RPL_TOPIC(hostname, nick, chann, topic) ":" + hostname + " 332 " + nick + " " + chann + " :" + topic + "\r\n"
#define RPL_NEWTOPICSETTED(nick, username, hostname, channel, topic) ":" + nick + "!~" + username + "@" + hostname + " TOPIC " + channel + " :" + topic + "\r\n";
#define ERR_CANNOTSENDTOCHAN(hostname, nick, channel) ":" + hostname + " 404 " + nick + " " + channel + " :Cannot send to channel\r\n"
#define ERR_NORECIPIENT(hostname, nick, command) ":" + hostname + " 411 " + nick + " :No recipient given (" + command + ")\r\n"
#define RPL_NOTOPIC(hostname, nick, chann) ":" + hostname + " 331 " + nick + " " + chann + " :No topic is set.\r\n"
#define ERR_PASSWDMISMATCH(nick, hostname) ":" + hostname + " 464 " + nick + " :Password incorrect !\r\n"
#define ERR_ERRONEUSNICKNAME(nick, hostname) ":" + hostname + " 432 * " + nick + " :Erroneus nickname !\r\n"
#define ERR_NONICKNAMEGIVEN(nick, hostname) ":" + hostname + " 431 " + nick + " :No nickname given !\r\n"
#define ERR_NICKNAMEINUSE(nick, hostname) ":" + hostname + " 433 " + nick + " :Nickname is already in use !\r\n"
#define RPL_NICKCHANGE(oldNick, nick, hostname) ":" + oldNick + " NICK " + nick + "\r\n"
#define ERR_ALREADYREGISTERED(nick, hostname) ":" + hostname + " 462 " + nick + " :You may not reregister !\r\n"
#define ERR_BADCHANNELNAME(nick, hostname, channelname) ":" + hostname + " 476 " + nick + " " + channelname + " :Invalid channel name." + "\r\n"
#define ERR_CHANNELISFULL(hostname, nick, channelName) ":" + hostname + " 471 " + nick + " " + channelName + " :Cannot join channel, Channel is full (+l)\r\n"
#define ERR_BADCHANNELKEY(nick, hostname, channelName) ":" + hostname + " 475 " + nick + " " + channelName + " :Cannot join channel (+K) - bad key\r\n"
#define ERR_INVITEONLY(hostname, nick, channelName) ":" + hostname + " 473 " + nick + " " + channelName + " :Cannot join channel, you must be invited (+i)\r\n"
#define RPL_JOIN(nick, username, channelname, ipaddress) ":" + nick + "!~" + username + "@" + ipaddress + " JOIN :" + channelname + "\r\n"
#define RPL_JOIN_OP(nick, username, channelname, ipaddress) ":@" + nick + "!~" + username + "@" + ipaddress + " JOIN :" + channelname + "\r\n"
#define RPL_TOPICDISPLAY(hostname, nick, channel, topic) ":" + hostname + " 332 " + nick + " " + channel + " :" + topic + "\r\n"
#define RPL_NAMREPLY(hostname, nick, channelname, clients) ":" + hostname + " 353 " + nick + " = " + channelname + " :" + clients + "\r\n"
#define RPL_ENDOFNAMES(hostname, nick, channelname) ":" + hostname + " 366 " + nick + " " + channelname + " :END of /NAMES list\r\n"
#define RPL_MODEISLIMIT(channel, hostname, mode, newlimit) ":" + hostname + " MODE " + channel + " " + mode + " " + newlimit + "\r\n"
#define RPL_CHANNELMODES(hostname, channelName, nick, channelmode) ":" + hostname + " 324 " + nick + " " + channelName + " " + channelmode + "\r\n"
#define RPL_INVITE(nick, username, clienthostname, channel, nick2) ":" + nick + "!~" + username + "@" + clienthostname + " INVITE " + nick2 + " " + channel + "\r\n"
#define PRIVMSG_FORMAT(senderNick, senderUsername, senderHostname, receiver, message) ":" + senderNick + "!~" + senderUsername + "@" + senderHostname + " PRIVMSG " + receiver + " :" + message + "\r\n"
#define RPL_QUIT(nick, host, message) ":" + nick + "!" + "~" + nick + "@" + host + " QUIT : " + message + "\r\n"
#define ERR_NOTEXTTOSEND(nick, hostname) ":" + hostname + " 412 " + nick + " :No text to send\r\n"
#define RPL_KICK(nick, username, hostname, kicked, channel, reason) ":" + nick + "!~" + username + "@" + hostname + " KICK " + channel + " " + kicked + " :" + reason + "\r\n"
#define NICKNAME_RPLY(nickname, username, hostname, newNickName) ":" + nickname + "!~" +  + "@" + hostname + " NICK :" + newNickName  + "\r\n"
#define RPL_UMODEIS(hostname, sender, target, modes) ":" + hostname +  " 221 " + sender + " " + target + " " + modes + "\r\n"
#define ERR_USERSDONTMATCH(sender) sender + " :Cant change mode for other users"
#define RPL_CREATIONTIME(hostname, nickname, channelname, creationtime) ":" + hostname + " 329 " + nickname + " " + channelname + " " + creationtime + "\r\n"
#define RPL_MODE(nick, username, host, target, mode) ":" + nick + "!~" + username + "@" + host + " MODE " + target + " " + mode + "\r\n"
#define RPL_NOTIFYPART(nick, host, channel, reason) (":" + nick + "!" + host + " PART " + channel +  " :" + reason + "\r\n")
#define ERR_INVALIDKEY(hostname, nick, chann) ":" + hostname + " 696 " + nick + " " + chann + " k * :Invalid key mode parameter. Syntax: <key>.\r\n"



#define RPL_WELCOME(user_forma, nickname) (": 001 " + nickname + " :Welcome " + nickname + " to the Internet Relay Chat " + user_forma + "\r\n")
#define RPL_YOURHOST(client, localhost) (": 002 " + client + " :Your host is " + localhost + "\r\n")
#define RPL_CREATED(client, datetime) (": 003 " + client + " :This server was created " + datetime + "\r\n")
#define RPL_MYINFO(client, servername, version, user_modes, chan_modes, chan_param_modes) (":localhost 004 " + client + " " + servername + " " + version + " " + user_modes + " " + chan_modes + " " + chan_param_modes + "\r\n")

#endif
