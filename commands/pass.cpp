#include "../Server.hpp"

void Server::pass(Client *client, Message *msg)
{
	if (msg->params.empty())
		client->sendMsg(ERR_NEEDMOREPARAMS(client->getNickname(), msg->command));

	std::string inputPwd = msg->params[0];

	if (client->isRegistered())
		client->sendMsg(ERR_ALREADYREGISTRED(client->getNickname()));
	
	if (inputPwd == _password)
		client->setHasValidPassword(true);
	else
	{
		client->sendMsg(ERR_PASSWDMISMATCH);
		client->setShouldBeDeleted(true);
	}
}