#include "../Server.hpp"

void Server::ping(Client *client, Message *msg)
{
    if (msg->params.empty())
        client->sendMsg(ERR_NOORIGIN);
    else
        client->sendMsg(RPL_PONG(msg->params[0]));
}