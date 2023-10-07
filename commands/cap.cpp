#include "../Server.hpp"

void Server::cap(Client* client)
{
	client->sendMsg(ERR_NOTREGISTERED);
}