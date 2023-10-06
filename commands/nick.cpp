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
	{
		client->setShouldBeDeleted(true);
		return ;
	}

	if (msg->params.empty()) // 변경하려는 닉네임 비어있을 때 - 등록된 계정에서 실험해보기 
	{
		client->sendMsg(ERR_NONICKNAMEGIVEN(currNickname));
		return ;
	}

	std::string newNickname = msg->params[0];
	if (!validNickName(newNickname)) // 닉네임 유효하지 않을 때
		client->sendMsg(ERR_ERRONEUSNICKNAME(currNickname, newNickname));
	else if (currNickname != newNickname && nicknameDupCheck(newNickname)) // 닉네임 중복인 경우
		client->sendMsg(ERR_NICKNAMEINUSE(currNickname, newNickname)); // 아마 NICK을 다시 보내주는데 등록된 계정에서는 실험해봐야 함 
	else
	{
		client->setNickname(newNickname);
		client->setIsNicknameRegistered(true);
	}
}