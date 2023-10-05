#include "../Irc.hpp"
#include "../commands.hpp"
#include "../DefineReplies.hpp"

bool	isClientInChannel(Client* client, Message* msg){
	std::vector<Channel *> joinedChannel = client->getJoinedChannels();
	std::vector<Channel *>::iterator isBegin = joinedChannel.begin();

	while(isBegin != joinedChannel.end()){
		if ((*isBegin)->getName() == msg->params[1])
			return true;
		isBegin++;
	}
	return false;
}

bool	AlreadyExists(Client* toInvite, Message* msg) {
	std::vector<Channel *> joinedChannel = toInvite->getJoinedChannels();
	std::vector<Channel *>::iterator isBegin = joinedChannel.begin();

	while (isBegin != joinedChannel.end()) {
		if ((*isBegin)->getName() == msg->params[1])
			return false;
		isBegin++;
	}
	return true;
}

void    invite(Client* client, Message *msg) {
	if (msg->params.size() < 2)
		return (client->sendMsg(client->getClientSocket(), ERR_NEEDMOREPARAMS(client->getNickName(), msg->command[0])));
	Client* toInvite = client->getServer().getClient(msg->params[0]);
	if (!toInvite)							//없는 유저를 초대할 때
		return (client->sendMsg(client->getClientSocket(), ERR_NOSUCHNICK(client->getNickName())));
	else if (!isClientInChannel(client, msg))	//자신이 속한 채널이 아닌 채널을 초대할 때, inspircd는 채널 먼저 확인하고 없으면 403 에러 날리고 채널이 있고 그 채널에 안 들어가고 해당 채널로 초대 요청을 날리면 442 에러 근데 뭐 어차피 해당 채널에 들어가 있어야 초대를 날릴 수 있는데 채널 탐색까지는 너무 굳이스러워서 안 할래 어차피 우리 마음이잖아
		return (client->sendMsg(client->getClientSocket(), ERR_NOTONCHANNEL(client->getNickName(), msg->params[1])));
	else if(!AlreadyExists(toInvite, msg)) //이미 유저가 해당 채널에 속해 있을 때
		return (client->sendMsg(client->getClientSocket(), ERR_USERONCHANNEL(client->getNickName(), toInvite->getNickName(), msg->params[1])));

}
