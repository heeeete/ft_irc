#include "../Server.hpp"

void Server::privmsg(Client *client, Message *msg)
{
	if (!client->isRegistered())
		return (client->sendMsg(ERR_NOTREGISTERED));
		
	if (msg->params.size() != 2) // 파라미터가 제대로 안들어온 경우 그냥 return
		return ;
	std::string receiver = msg->params[0]; // 보낼 채널 또는 유저
	std::string toSend = msg->params[1]; // 보낼 메시지
	std::string nick = client->getNickname(); //보내는 유저의 닉네임 

	std::string reply = RPL_PRIVMSG(nick, client->getUsername(), client->getHostname() , receiver, toSend);

	if (receiver[0] == '#') // 채널이면 
	{
		if (!client->isInChannel(receiver)) // 클라이언트가 채널 안에 있는지 확인 
			return (client->sendMsg(ERR_CANNOTSENDTOCHAN(nick, receiver)));
		Channel *channel = getChannel(receiver); //	채널 찾기
		if (!channel) //채널 없는 경우
			throw ServerException("Can't find channel!!");
		else
			client->sendMsgToChannel(reply, channel); // 채널 클라이언트들한테 메시지 보내기 
	}
	else // 닉네임이면
	{
		Client *clientToSend = getClient(receiver); // 보내려는 클라이언트 찾기 
		if (!clientToSend) // 해당 닉네임의 클라이언트 없는 경우 
		 	client->sendMsg(ERR_NOSUCHNICK(nick, receiver));
		else 
			clientToSend->sendMsg(reply); // 클라이언트한테 메시지 보내기 
	}
}