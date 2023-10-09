#include "../Server.hpp"

#define MAX_JOINED_CHANNEL 3

void Server::join(Client *client, Message *msg)
{
	std::string			nick = client->getNickname();
	if (msg->params.empty())
		client->sendMsg(ERR_NEEDMOREPARAMS(nick, msg->command));

	std::stringstream	ss(msg->params[0]);
	std::string			channelName;
	while (std::getline(ss, channelName, ','))
	{
		if (client->getJoinedChannels().size() >= MAX_JOINED_CHANNEL)
		{
			client->sendMsg(ERR_TOOMANYCHANNELS(nick, channelName));
			return ;
		}
		if ((channelName[0] != '&' && channelName[0] != '#') || channelName.length() > 200 || channelName.find(" ") != std::string::npos )
		{
			client->sendMsg(ERR_NOSUCHCHANNEL(nick, channelName));
			continue;
		}
		std::cout << "채널 이름 : " << channelName << "\n";
		createChannel(client, channelName); // 채널 없으면 채널 만듦
		Channel *ch = getChannel(channelName);
		if (!ch)
		{
			std::cerr << channelName << " 채널이 만들어지지 않았습니다." << std::endl;
			return ;
		}
		else
		{
			// ch->hasMode('i');
			// if (ch->hasMode('k'))
			// {
			// 	if (msg->params.size() < 2 || !ch->isValidKey(m->params[1]))
			// 		return (sendReply(475, chan, "", "", ""));
			// }		채널 패스워드 확인 근데 지금 채널 패스워드 기능 없어서 안함
			if (ch->hasMode('i') && !ch->isInvited(client))	//채널 모드가 i 일때 초대받은 클라이언트만 가능
				return (client->sendMsg(ERR_INVITEONLYCHAN(nick, channelName)));
			if (ch->hasMode('l') && ch->getClients().size() >= ch->getUserLimit())	//유저 인원 제한
				return (client->sendMsg(ERR_CHANNELISFULL(nick, channelName)));
			if (ch->hasClient(client))												//이미 있는 유저인지 확인
				return (client->sendMsg(ERR_USERONCHANNEL(nick, nick, channelName)));
			ch->addClient(client);
			std::cout << nick << ' ' << ch->getName() << "접속\n";
		}
		client->sendMsgToChannel(USER_JOIN(nick, client->getUsername(), client->getHostname(), ch->getName()), ch);
		client->sendMsg(USER_JOIN(nick, client->getUsername(), client->getHostname(), ch->getName()));
		//REPLY
		if (!ch->getTopic().empty())
			client->sendMsg(RPL_TOPIC(client->getNickname(), channelName, ch->getTopic()));
		client->sendMsg(RPL_NAMREPLY(nick, ch->getName(), ch->getClientsName()));
		client->sendMsg(RPL_ENDOFNAMES(nick, ch->getName()));
	}
}
