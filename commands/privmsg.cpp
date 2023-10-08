#include "../Server.hpp"

void Server::privmsg(Client *client, Message *msg)
{
	std::string receiver = msg->params[0];
	std::string toSend = msg->params[1];

	std::string reply = RPL_PRIVMSG(client->getNickname(), client->getUsername(), client->getHostname() , receiver, toSend);

	if (receiver[0] == '#') // 채널이면 
	{
		Channel *channel = getChannel(receiver); //	채널 찾기
		client->sendMsgToChannel(reply, channel); // 채널 클라이언트들한테 메시지 보내기 
	}
	else // 닉네임이면
	{
		Client *clientToSend = getClient(receiver); // 보내려는 클라이언트 찾기 
		clientToSend->sendMsg(reply); // 클라이언트한테 메시지 보내기 
	}
}