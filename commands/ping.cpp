#include "../Server.hpp"

void Server::ping(Client *client, Message *msg)
{
	if (!client->isRegistered())
		return (client->sendMsg(ERR_NOTREGISTERED));
		
    if (msg->params.empty())
        client->sendMsg(ERR_NOORIGIN);
    else
        client->sendMsg(RPL_PONG(client->getNickname(), client->getUsername(), client->getHostname(), msg->params[0]));
}