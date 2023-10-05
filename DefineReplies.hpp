#ifndef DEFINEREPLIES_HPP
# define DEFINEREPLIES_HPP

/* WELCOME */
# define RPL_WELCOME(nick, user, host)                  ":PPL_IRC 001 " + nick + " :Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host + "\r\n"
# define RPL_YOURHOST(nick, servername, ver)                  ":PPL_IRC 002 " + nick + " :Your host is " + servername + ", running version " + ver + "\r\n"
# define RPL_CREATED(nick, _startTime)                        ":PPL_IRC 003 " + nick + " :This server was created " + _startTime + "\r\n"
# define RPL_MYINFO(nick, servername, version, channelModes, userModes) ":PPL_IRC 004 " + nick + " :" + servername + " " + version + " " + channelModes + " " + userModes + "\r\n"

/*MOTD*/
# define RPL_MOTDSTART(nick)							":PPL_IRC 375 " + nick + " :Message of the day\r\n"
# define RPL_MOTD(nick)									":PPL_IRC 372 " + nick + " :" + \
														"       ______                                           ______\r\n" + \
														"      /::::::\\      *****************************      /::::::\\\r\n" + \
														"      |      |      *    W  E  L  C  O  M  E    *      |      |\r\n" + \
														"     @  O  O  @     *                           *     @  O  O  @\r\n" + \
														"      |  +   |      *            T O            *      |  +   |\r\n" + \
														"       \\ -- /       *                           *       \\ -- /\r\n" + \
														"        |  |        *   빡  빡  이   I  R  C    *        |  |    \r\n" + \
														"                    *****************************\r\n"
# define RPL_ENDOFMOTD(nick)							":PPL_IRC 376 " + nick + " :End of MOTD command\r\n"

/* PING PONG */
# define RPL_PONG(token)								":PPL_IRC PONG " + token + "\r\n"

/* ERROR */
# define ERR_NOORIGIN                                   ":PPL_IRC 409 * :No origin specified\r\n" //ping 에러
# define ERR_NONICKNAMEGIVEN(nick)						":PPL_IRC 431 " + nick + " " + ":No nickname given\r\n" //공백 닉네임
# define ERR_ERRONEUSNICKNAME(nick, rejectedNickname)	":PPL_IRC 432 " + nick + " " + rejectedNickname + " :Erroneus nickname\r\n" //특수문자 닉네임
# define ERR_NICKNAMEINUSE(nick, rejectedNickname)		":PPL_IRC 433 " + nick + " " + rejectedNickname + " :Nickname is already in use\r\n" //중복된 닉네임
# define ERR_NOTREGISTERED								":PPL_IRC 451 * :You have not registered\r\n"
# define ERR_NEEDMOREPARAMS(nick, command)			    ":PPL_IRC 461 " + nick + " " + command + " :Not enough parameters\r\n"
# define ERR_ALREADYREGISTRED(nick)                     ":PPL_IRC 462 " + nick + " :Unauthorized command (already registered)\r\n"
# define ERR_PASSWDMISMATCH								":PPL_IRC 464 * :Password incorrect\r\n"

#endif
