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
	if (msg->params.size() < 2)
	{
		client->sendMsg(ERR_NEEDMOREPARAMS(client->getNickname(), msg->command[0]));
		return ;
	}
	Client *toInvite = getClient(msg->params[0]);
	if (!toInvite) //없는 유저를 초대할 때
		client->sendMsg(ERR_NOSUCHNICK(client->getNickname()));
	else if (!isClientInChannel(client, msg)) //자신이 속한 채널이 아닌 채널을 초대할 때, inspircd는 채널 먼저 확인하고 없으면 403 에러 날리고 채널이 있고 그 채널에 안 들어가고 해당 채널로 초대 요청을 날리면 442 에러 근데 뭐 어차피 해당 채널에 들어가 있어야 초대를 날릴 수 있는데 채널 탐색까지는 너무 굳이스러워서 안 할래 어차피 우리 마음이잖아
		client->sendMsg(ERR_NOTONCHANNEL(client->getNickname(), msg->params[1]));
	else if (!alreadyExists(toInvite, msg)) //이미 유저가 해당 채널에 속해 있을 때
		client->sendMsg(ERR_USERONCHANNEL(client->getNickname(), toInvite->getNickname(), msg->params[1]));
	//아마 초대하는 메시지 같은 걸 추가하겠죠? 
}

