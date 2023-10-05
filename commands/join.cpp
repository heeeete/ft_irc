#include "../Irc.hpp"
#include "../commands.hpp"
#include "../DefineReplies.hpp"

#define MAX_JOINED_CHANNEL 3

void    join(Client* client, Message *msg) {
	if (msg->params.empty())
		client->sendMsg(client->getClientSocket(), ERR_NEEDMOREPARAMS(client->getNickName(), msg->command[0]));

	std::stringstream	ss(msg->params[0]);
	std::string			channelName;
	while (std::getline(ss, channelName, ',')) {
		if (client->getJoinedChannels().size() >= MAX_JOINED_CHANNEL){
			client->sendMsg(client->getClientSocket(), ERR_TOOMANYCHANNELS(client->getNickName(), channelName));
			return ;
		}
		if ((channelName[0] != '&' && channelName[0] != '#') || channelName.length() > 200 || (channelName.find(" ") != std::string::npos)){
			client->sendMsg(client->getClientSocket(), ERR_NOSUCHCHANNEL(client->getNickName(), channelName));
			continue;
		}
		std::cout << "채널 이름 : " << channelName << "\n";
		client->getServer().createChannel(client, channelName);
		Channel *ch = client->getServer().getChannel(channelName);
		if (!ch) {
			std::cerr << channelName << " 채널이 만들어지지 않았습니다." << std::endl;
			return ;
		}
		else {
			ch->addClient(client);
			std::cout << client->getNickName() << ch->getName() << "접속\n";
		}
		client->sendMsgChannel(USER_JOIN(client->getNickName(), client->getUserName(), client->getHostName(), ch->getName()), ch);
		client->sendMsg(client->getClientSocket(), RPL_NAMREPLY(client->getNickName(), ch->getName(), ch->getNames()));
		client->sendMsg(client->getClientSocket(), RPL_ENDOFNAMES(client->getNickName(), ch->getName()));
	}
}
