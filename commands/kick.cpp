#include "../Server.hpp"

void Server::kick(Client *client, Message *msg)
{
    if (!client->isRegistered())
      return (client->sendMsg(ERR_NOTREGISTERED));
		
    if (msg->params.size() < 2)
		  return (client->sendMsg(ERR_NEEDMOREPARAMS(client->getNickname(), msg->command[0])));
    
    std::string channelName = msg->params[0];
    std::string kickedName = msg->params[1];

    Channel *ch = getChannel(channelName);
    if (!ch)        // 존재하지 않은 채널
      return (client->sendMsg(ERR_NOSUCHCHANNEL(client->getNickname(), channelName)));
    
    Client *toKick = getClient(kickedName);
    if (!toKick)    // 존재하지 않는 사용자
      return (client->sendMsg(ERR_NOSUCHNICK(client->getNickname(), kickedName)));

    if (!client->isInChannel(channelName))    // 강퇴시키는 유저가 채널에 없을 때
		  return (client->sendMsg(ERR_NOTONCHANNEL(client->getNickname(), channelName)));
    if (!toKick->isInChannel(channelName))    // 강퇴당하는 유저가 채널에 없을 때
		  return (client->sendMsg(ERR_USERNOTINCHANNEL(client->getNickname(), kickedName, channelName)));

    if (!ch->isOperator(client))        // 강퇴시키는 유저가 operator가 아닐 때
      return (client->sendMsg(ERR_CHANOPRIVSNEEDED(client->getNickname(), channelName)));

    std::string kickMsg = "kicked out";
    if (!msg->params[2].empty())    // 설정 kick 메세지가 있을 때
      kickMsg = msg->params[2];
    client->sendMsg(RPL_KICK(client->getNickname(), client->getUsername(), client->getHostname(), channelName, kickedName, kickMsg));
    client->sendMsgToChannel(RPL_KICK(client->getNickname(), client->getUsername(), client->getHostname(), channelName, kickedName, kickMsg), ch);
    ch->removeClient(toKick);
} 
