#include "../Server.hpp"

void Server::topic(Client *client, Message *msg)
{
	if (!client->isRegistered())
		return (client->sendMsg(ERR_NOTREGISTERED));
		
    if (msg->params.empty())
		return (client->sendMsg(ERR_NEEDMOREPARAMS(client->getNickname(), msg->command[0])));
    
    std::string channelName = msg->params[0];
    Channel *ch = getChannel(channelName);
    if (!ch)        // 존재하지 않은 채널
        return (client->sendMsg(ERR_NOSUCHCHANNEL(client->getNickname(), channelName)));

    if (!client->isInChannel(channelName))  // 클라이언트가 채널에 속해있지 않을 때
		return (client->sendMsg(ERR_NOTONCHANNEL(client->getNickname(), channelName)));

    if (ch->hasMode('t') && !ch->isOperator(client))    // mode가 t인데 클라이언트가 oper가 아닐 때
        return (client->sendMsg(ERR_CHANOPRIVSNEEDED(client->getNickname(), channelName)));

    if (msg->params.size() == 1)    // topic 정보
    {
        std::string topic = ch->getTopic();
        if (topic.empty())  // topic 설정 x
            client->sendMsg(RPL_NOTOPIC(client->getNickname(), channelName));
        else                // topic 설정 o
            client->sendMsg(RPL_TOPIC(client->getNickname(), channelName, topic));
    }
    else if (msg->params.size() == 2)    // topic 설정
    {
        ch->setTopic(msg->params[1]);
        client->sendMsg(RPL_SET_TOPIC(client->getNickname(), client->getUsername(), client->getHostname() , channelName, msg->params[1]));
        client->sendMsgToChannel(RPL_SET_TOPIC(client->getNickname(), client->getUsername(), client->getHostname() , channelName, msg->params[1]), ch);
    }
}
