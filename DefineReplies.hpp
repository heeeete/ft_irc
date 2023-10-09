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

//INVITE
# define RPL_INVITING(nick, toInviteUser, channelName)				":PPL_IRC 341 " + nick + " " + toInviteUser + " " + ":" + channelName + "\r\n"
//:irc.local 341 zxc qwe :#123

// JOIN
# define RPL_NAMREPLY(nick, channelName, names) 		":PPL_IRC 353 " + nick + " = " + channelName + " :" + names + "\r\n"
# define RPL_ENDOFNAMES(nick, channelName) 				":PPL_IRC 366 " + nick + " " + channelName + " :End of /NAMES list.\r\n"
# define USER_JOIN(nick, username, hostname,channelName)			":" + nick + "!" + username + "@" + hostname + " JOIN " + channelName + "\r\n"

/* KICK */
# define RPL_KICK(nick, userName, hostName, channel, kicked, reason) 	":" + nick + "!" + userName + "@" + hostName + " " + "KICK " + channel + " " + kicked + " :" + reason + "\r\n"

/* PART */
# define RPL_PART(nick, userName, hostName, channel, reason)		":" + nick + "!" + userName + "@" + hostName + " " + "PART " + channel + " :" + reason + "\r\n"

/* QUIT */
# define RPL_QUIT(nick, userName, hostName, reason)                	":" + nick + "!" + userName + "@" + hostName + " " + "QUIT :" + reason + "\r\n"

/* PRIVMSG */
# define RPL_PRIVMSG(nick, userName, hostName, receiver, msg) ":" + nick + "!" + userName + "@" + hostName + " " + "PRIVMSG  " + receiver + " :" + msg + "\r\n"

/* PING PONG */
# define RPL_PONG(token)								":PPL_IRC PONG " + token + " :PPL_IRC\r\n"
//:irc.local PONG irc.local :irc.local

/* ERROR */
# define ERR_NOSUCHNICK(nick, targetNick)							":PPL_IRC 401 " + nick + " " + targetNick + " :No such nick\r\n" //닉네임 못찾음
# define ERR_NOSUCHCHANNEL(nick, channelName)			":PPL_IRC 403 " + nick + " " + channelName + " :No such channel\r\n" //유효하지 않은 채널 이름
# define ERR_CANNOTSENDTOCHAN(nick, channelName)		":PPL_IRC 404 " + nick + " " + channelName + " :Cannot send to channel\r\n" //유저가 속하지 않은 채널에 메세지 보낼 때
# define ERR_TOOMANYCHANNELS(nick, channelName)			":PPL_IRC 405 " + nick + " " + channelName + " :You have joined too many channels\r\n" //유저가 4개 이상의 채널에 접속
# define ERR_NOORIGIN                                   ":PPL_IRC 409 * :No origin specified\r\n" //ping 에러

# define ERR_NONICKNAMEGIVEN(nick)						":PPL_IRC 431 " + nick + " " + ":No nickname given\r\n" //공백 닉네임
# define ERR_ERRONEUSNICKNAME(nick, rejectedNickname)	":PPL_IRC 432 " + nick + " " + rejectedNickname + " :Erroneus nickname\r\n" //특수문자 닉네임
# define ERR_NICKNAMEINUSE(nick, rejectedNickname)		":PPL_IRC 433 " + nick + " " + rejectedNickname + " :Nickname is already in use\r\n" //중복된 닉네임
# define ERR_USERNOTINCHANNEL(nick, channel) 			":PPL_IRC 441 " + nick + " " + channel + " :They aren't on that channel"	// 강퇴하려는 멤버가 채널에 없을 때
# define ERR_NOTONCHANNEL(nick, channelName)			":PPL_IRC 442 " + nick + " " + channelName + " :You're not on that channel\r\n"	//클라이언트가 멤버가 아닌 채널 이펙트 명령을 수행하려고 할 때
# define ERR_USERONCHANNEL(nick, toInviteNick, channelName)			":PPL_IRC 443 " + nick + " " + toInviteNick + " " + channelName + " :is already on channel\r\n"	//클라이언트가 이미 해당 채널에 있음
# define ERR_NOTREGISTERED								":PPL_IRC 451 * :You have not registered\r\n"
# define ERR_NEEDMOREPARAMS(nick, command)			    ":PPL_IRC 461 " + nick + " " + command + " :Not enough parameters\r\n"
# define ERR_ALREADYREGISTRED(nick)                     ":PPL_IRC 462 " + nick + " :Unauthorized command (already registered)\r\n"
# define ERR_PASSWDMISMATCH								":PPL_IRC 464 * :Password incorrect\r\n"
# define ERR_CHANNELISFULL(nick, channelName)			":PPL_IRC 471 " + nick + " " + channelName + " :Cannot join channel (+l)\r\n"
# define ERR_INVITEONLYCHAN(nick, channelName)			":PPL_IRC 473 " + nick + " " + channelName + " :Cannot join channel (+i)\r\n"
# define ERR_BANNEDFROMCHAN(nick, channelName)			":PPL_IRC 473 " + nick + " " + channelName + " :Cannot join channel (+b)\r\n"
# define ERR_BADCHANNELKEY(nick, channelName)			":PPL_IRC 473 " + nick + " " + channelName + " :Cannot join channel (+k)\r\n"
# define ERR_CHANOPRIVSNEEDED(nick, channelName)		":PPL_IRC 482 " + nick + " " + channelName + " :You're not channel operator\r\n"
//:irc.local 482 qwe #123 :You must be a channel operator

#endif
