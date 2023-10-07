#include "../Server.hpp"

void Server::user(Client *client, Message *msg)
{
	if (!client->hasValidPassword()) // PASS 틀린 경우, 없는 경우 
		return ;
	if (msg->params.size() < 4)
		client->sendMsg(ERR_NEEDMOREPARAMS(client->getNickname(), msg->command));
	if (client->isRegistered())
		client->sendMsg(ERR_ALREADYREGISTRED(client->getNickname()));

	client->setUsername(msg->params[1]);
	client->setHostname(msg->params[2]);
	client->setRealname(msg->params[3]);

	client->setIsUserinfoRegistered(true);
}