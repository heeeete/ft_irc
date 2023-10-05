#include "../Irc.hpp"
#include "../commands.hpp"
#include "../DefineReplies.hpp"

void    pass(Client &client, Message *msg) {
	if (msg->params.empty())
		client.sendMsg(client.getClientSocket(), ERR_NEEDMOREPARAMS(std::string("*"), msg->command));

	std::string pwd = msg->params[0];

	if (client.getRegistrationDone())
        client.sendMsg(client.getClientSocket(), ERR_ALREADYREGISTRED(client.getNickName()));

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