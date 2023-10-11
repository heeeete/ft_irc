#include "../Server.hpp"

void Server::quit(Client *client, Message *msg) 
{
	if (!client->isRegistered())
		return (client->sendMsg(ERR_NOTREGISTERED));
		
    std::string quit_msg = "See ya!";
    if (!msg->params.empty())   // quit 메세지가 존재할 때
        quit_msg = msg->params[0];
    
    client->sendMsg(RPL_QUIT(client->getNickname(), client->getUsername(), client->getHostname(), quit_msg));

	closeClient(client->getPollFdIdx(), quit_msg);
}
