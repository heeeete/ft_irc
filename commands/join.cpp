#include "../Server.hpp"

#define MAX_JOINED_CHANNEL 3

void Server::join(Client *client, Message *msg)
{
	if (msg->params.empty())
		client->sendMsg(ERR_NEEDMOREPARAMS(client->getNickname(), msg->command));

	std::stringstream	ss(msg->params[0]);
	std::string			channelName;
	while (std::getline(ss, channelName, ','))
	{
		if (client->getJoinedChannels().size() >= MAX_JOINED_CHANNEL)
		{
			client->sendMsg(ERR_TOOMANYCHANNELS(client->getNickname(), channelName));
			return ;
		}
		if ((channelName[0] != '&' && channelName[0] != '#') || channelName.length() > 200 || channelName.find(" ") != std::string::npos )
		{
			client->sendMsg(ERR_NOSUCHCHANNEL(client->getNickname(), channelName));
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
			ch->addClient(client);
			std::cout << client->getNickname() << ' ' << ch->getName() << "접속\n";
		}
		client->sendMsgToChannel(USER_JOIN(client->getNickname(), client->getUsername(), client->getHostname(), ch->getName()), ch);
		client->sendMsg(RPL_NAMREPLY(client->getNickname(), ch->getName(), ch->getClientsName()));
		client->sendMsg(RPL_ENDOFNAMES(client->getNickname(), ch->getName()));
	}
}
