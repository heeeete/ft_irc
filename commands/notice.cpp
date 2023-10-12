#include "../Server.hpp"

void Server::notice(Client *client, Message *msg)
{
	if (!client->isRegistered())
		return (client->sendMsg(ERR_NOTREGISTERED));
		
	if (msg->params.empty())
		return;
	else if (msg->params.size() == 1)// 메세지 내용 없음
		return;

	Client	*target = getClient(msg->params[0]);
	if (target == NULL)
		return;
	else
		client->sendMsgClient(RPL_PRIVMSG(client->getNickname(), client->getUsername(), client->getHostname(), msg->params[0], msg->params[1]), target);
}
