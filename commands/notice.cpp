#include "../Server.hpp"

void Server::notice(Client *client, Message *msg)
{
	if (msg->params.empty())
		return;
	else if (msg->params.size() == 1)// 메세지 내용 없음
		return;

	Client	*target = getClient(msg->params[0]);
	if (target == NULL)//no esta ese nick
		return;
	else
	{
		std::string m = ":" + client->getNickname() + "!" + client->getUsername() + "@" + client->getHostname() + " " + "NOTICE " + msg->params[0] + " :" + msg->params[1] + END_CHARACTERS;
		client->sendMsgClient(m, target);
	}
}
