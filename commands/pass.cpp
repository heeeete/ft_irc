#include "../Irc.hpp"
#include "../commands.hpp"
#include "../DefineReplies.hpp"

void    pass(Client &client, Message *msg) {
	std::string pwd = msg->params[0];

	client.setConnectionPassword(true);
	if (client.getServer().getPassword() == pwd)
	{
		return ;
	}
	else
	{
		client.setCorrectPwd(false);
		client.sendMsg(client.getClientSocket(), ERR_PASSWDMISMATCH);
		close(client.getClientSocket()); //소켓 닫기 
		client.getServer().getClientsList().erase(client.getClientSocket()); //clientsList에서 해당 소켓 지우기
		client.getServer().getPollFDs()[client.getPollFDsIdx()].fd = -1; //pollFDs에서 fd 지우기
	}

}