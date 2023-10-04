#ifndef DEFINEREPLIES_HPP
# define DEFINEREPLIES_HPP

/* WELCOME */
# define RPL_WELCOME(nick, user, host)                  ":PPL_IRC 001 " + nick + " :Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host + "\r\n"
# define RPL_YOURHOST(nick, servername, ver)                  ":PPL_IRC 002 " + nick + " :Your host is " + servername + ", running version " + ver + "\r\n"
# define RPL_CREATED(nick, _startTime)                        ":PPL_IRC 003 " + nick + " :This server was created " + _startTime + "\r\n"
# define RPL_MYINFO(nick, servername, version, channelModes, userModes) ":PPL_IRC 004 " + nick + " :" + servername + " " + version + " " + channelModes + " " + userModes + "\r\n"


/* ERROR */
# define ERR_NEEDMOREPARAMS(nick, command)			    ":PPL_IRC 461 " + nick + " " + command + " :Not enough parameters\r\n"
# define ERR_ALREADYREGISTRED(nick)                     ":PPL_IRC 462 " + nick + " :Unauthorized command (already registered)\r\n"

#endif