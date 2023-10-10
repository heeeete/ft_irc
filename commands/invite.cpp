#include "../Server.hpp"

static bool isClientInChannel(Client* client, Message* msg){
	std::vector<Channel *> joinedChannel = client->getJoinedChannels();
	std::vector<Channel *>::iterator iter = joinedChannel.begin();

	while(iter != joinedChannel.end()){
		if ((*iter)->getName() == msg->params[1])
			return true;
		iter++;
	}
	return false;
}

static bool alreadyExists(Client* toInvite, Message* msg) {
	std::vector<Channel *> joinedChannel = toInvite->getJoinedChannels();
	std::vector<Channel *>::iterator iter = joinedChannel.begin();

	while (iter != joinedChannel.end()) {
		if ((*iter)->getName() == msg->params[1])
			return false;
		iter++;
	}
	return true;
}

void Server::invite(Client *client, Message *msg)
{
	if (!client->isRegistered())
		return (client->sendMsg(ERR_NOTREGISTERED));
		
	if (msg->params.size() < 2)
		return (client->sendMsg(ERR_NEEDMOREPARAMS(client->getNickname(), msg->command[0])));

	std::string nick = client->getNickname();
	Client *toInvite = getClient(msg->params[0]);
	if (!toInvite) //없는 유저를 초대할 때
		return(client->sendMsg(ERR_NOSUCHNICK(nick, msg->params[0])));
	Channel *ch = getChannel(msg->params[1]);
    if (!ch)       // 존재하지 않은 채널
        return(client->sendMsg(ERR_NOSUCHCHANNEL(nick, msg->params[1])));
	if (!isClientInChannel(client, msg)) //자신이 속한 채널이 아닌 채널을 초대할 때
		return(client->sendMsg(ERR_NOTONCHANNEL(nick, msg->params[1])));
	if (!alreadyExists(toInvite, msg)) //이미 유저가 해당 채널에 속해 있을 때
		return(client->sendMsg(ERR_USERONCHANNEL(nick, toInvite->getNickname(), msg->params[1])));

	if (!ch->isOperator(client))	// oper가 아닐 때
	 	return(client->sendMsg(ERR_CHANOPRIVSNEEDED(nick, ch->getName())));
	ch->addInviteds(toInvite);
	toInvite->sendMsg(nick + " invites you to " + msg->params[1] + END_CHARACTERS);
	client->sendMsg(RPL_INVITING(nick, msg->params[0], msg->params[1]));
}

