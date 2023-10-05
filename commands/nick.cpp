#include "../Irc.hpp"
#include "../commands.hpp"
#include "../DefineReplies.hpp"

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

static std::string changeNickname(Client &client, std::string oldName)
{
	std::string newName = oldName;
	int name_idx = 0;
	int char_idx = 0;
	do 
	{
		if (newName.length() < 9)
			newName += "_";
		else
		{
			newName[name_idx] = NICKNAME_VALID_CHAR[char_idx];
			char_idx++;
			if (char_idx == strlen(NICKNAME_VALID_CHAR))
			{
				char_idx = 0;
				name_idx++;
				if (name_idx == 9)
					return "";
			} 
		}
	} while (client.getServer().nickNameDupCheck(newName)); 
	return newName;
}

void    nick(Client &client, Message *msg) {
	std::string m;
	if (!client.getConnectionPassword()) //PASS 없이 온 경우 클라이언트 없애기 
	{
		client.setCorrectPwd(false);
		client.sendMsg(client.getClientSocket(), ERR_PASSWDMISMATCH);
		close(client.getClientSocket()); //소켓 닫기
		client.getServer().getClientsList().erase(client.getClientSocket()); //clientsList에서 해당 소켓 지우기
		client.getServer().getPollFDs()[client.getPollFDsIdx()].fd = -1; //pollFDs에서 fd 지우기
		return ;
	}
	if (!client.getCorrectPwd()) // 패스워드 다른 경우 바로 리턴
		return ;
	if (msg->params.empty())	//변경하려는 닉네임 비어있을때
		client.sendMsg(client.getClientSocket(), ERR_NONICKNAMEGIVEN(client.getNickName()));
	else if (!validNickName(msg->params[0]))	//닉네임 문자 확인
		client.sendMsg(client.getClientSocket(), ERR_ERRONEUSNICKNAME(client.getNickName(), msg->params[0]));
	else if (client.getNickName() != msg->params[0] && client.getServer().nickNameDupCheck(msg->params[0]))	//닉네임 중복검사
	{
		client.sendMsg(client.getClientSocket(), ERR_NICKNAMEINUSE(client.getNickName(), msg->params[0]));
		if (!client.getRegistrationDone()) //아직 등록 안됐는데 닉네임 중복인 경우 닉네임 임의로 바꿔주고 닉네임 등록 
		{
			std::string newNick = changeNickname(client, msg->params[0]);
			if (newNick == "")
			{
				std::string errMsg = ":PPL_IRC ERROR " + client.getNickName() + " :사용할 수 있는 닉네임이 없습니다";
				client.sendMsg(client.getClientSocket(), errMsg);
				client.setCorrectPwd(false);
				close(client.getClientSocket()); //소켓 닫기
				client.getServer().getClientsList().erase(client.getClientSocket()); //clientsList에서 해당 소켓 지우기
				client.getServer().getPollFDs()[client.getPollFDsIdx()].fd = -1; //pollFDs에서 fd 지우기
				return ;
			}
			client.setNickName(newNick);
		}
	}
	else {
		client.setNickName(msg->params[0]);
	}
}
