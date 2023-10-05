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

	if (!client.getConnectionPassword())
	{
		client.setCorrectPwd(false);
		client.sendMsg(client.getClientSocket(), ERR_PASSWDMISMATCH);
		close(client.getClientSocket()); //소켓 닫기
		client.getServer().getClientsList().erase(client.getClientSocket()); //clientsList에서 해당 소켓 지우기
		client.getServer().getPollFDs()[client.getPollFDsIdx()].fd = -1; //pollFDs에서 fd 지우기
		return ;
	}
	if (!client.getCorrectPwd())
		return ;
	if (msg->params.empty())	//변경하려는 닉네임 비어있을때
		client.sendMsg(client.getClientSocket(), ERR_NONICKNAMEGIVEN(client.getNickName()));
	else if (!validNickName(msg->params[0]))	//닉네임 문자 확인
		client.sendMsg(client.getClientSocket(), ERR_ERRONEUSNICKNAME(client.getNickName(), msg->params[0]));
	else if (client.getServer().nickNameDupCheck(msg->params[0]))	//닉네임 중복검사
		client.sendMsg(client.getClientSocket(), ERR_NICKNAMEINUSE(client.getNickName(), msg->params[0]));
	else {
		client.setNickName(msg->params[0]);
	}
}
