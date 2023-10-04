#include "../Irc.hpp"
#include "../commands.hpp"
#include "../DefineReplies.hpp"

# define NICKNAME_VALID_CHAR "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_[]{}\\`|"

bool	validNickName(std::string nickname)
{
	if (nickname.length() > 9)
		return false;
	for (size_t i = 0; i < nickname.length(); i++)
	{
		if (!std::strchr(NICKNAME_VALID_CHAR, nickname[i]))
			return false;
	}
	return true;
}

void    nick(Client &client, Message *msg) {
	std::string m;

	if (msg->params.empty()) client.sendMsg(client.getClientSocket(), ERR_NONICKNAMEGIVEN(client.getNickName()));
	else if (!validNickName(msg->params[0])) client.sendMsg(client.getClientSocket(), ERR_ERRONEUSNICKNAME(client.getNickName(), msg->params[0]));
	else {
		client.setNickName(msg->params[0]);
	}
}
