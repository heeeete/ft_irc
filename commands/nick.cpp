#include "../Server.hpp"

# define NICKNAME_VALID_CHAR "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_[]{}\\`|"

static bool	validNickName(std::string nickname)
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

void Server::nick(Client *client, Message *msg)
{
	std::string currNickname = client->getNickname();

	if (!client->hasValidPassword()) // PASS 틀린 경우, 없는 경우
		return (client->setShouldBeDeleted(true));

	if (msg->params.empty()) // 변경하려는 닉네임 비어있을 때
		return (client->sendMsg(ERR_NONICKNAMEGIVEN(currNickname)));

	std::string newNickname = msg->params[0];
	if (!validNickName(newNickname)) // 닉네임 유효하지 않을 때
		client->sendMsg(ERR_ERRONEUSNICKNAME(currNickname, newNickname));
	else if (currNickname == newNickname || nicknameDupCheck(newNickname)) // 닉네임 중복인 경우
		client->sendMsg(ERR_NICKNAMEINUSE(currNickname, newNickname));
	else
	{
		client->sendMsg(RPL_NICK(client->getNickname(), client->getUsername(), client->getHostname(), newNickname));
		std::vector<Channel *> channels = client->getJoinedChannels();
		if (!channels.empty()) {
			std::vector<Channel *>::iterator iter = channels.begin();
			for ( ; iter != channels.end(); ++iter)  // 해당 클라이언트가 속해있는 채널들
				client->sendMsgToChannel(RPL_NICK(client->getNickname(), client->getUsername(), client->getHostname(), newNickname), *iter);
		}
		client->setNickname(newNickname);
		client->setIsNicknameRegistered(true);
	}
}
