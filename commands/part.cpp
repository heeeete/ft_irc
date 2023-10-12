#include "../Server.hpp"

static int checkJoinedChannels(Client* client, std::string &channelName)
{
	std::vector<Channel *> joinedChannel = client->getJoinedChannels();
    std::vector<Channel *>::iterator iter = joinedChannel.begin();
    for ( ; iter != joinedChannel.end(); ++iter) {
        if ((*iter)->getName() == channelName)
            return (1);
    }
    return (0);
}

static std::string getPartMsg(Message *msg)
{
    std::string m = "See ya!";
	if (msg->params.size() == 1) // PART_MSG not_defined
		return (m);
	return(msg->params[1]);
}

void Server::part(Client *client, Message *msg)
{
	if (!client->isRegistered())
		return (client->sendMsg(ERR_NOTREGISTERED));
		
    if (msg->params.empty())
		return (client->sendMsg(ERR_NEEDMOREPARAMS(client->getNickname(), msg->command[0])));

    std::stringstream	ss(msg->params[0]);
	std::string			channelName;
	while (std::getline(ss, channelName, ','))
	{
        Channel *ch = getChannel(channelName);
		if (!ch)    // 해당 채널이 존재하는가
			client->sendMsg(ERR_NOSUCHCHANNEL(client->getNickname(), channelName));
        else if (!checkJoinedChannels(client, channelName)) // 해당 사용자가 채널에 join한 상태인가
            client->sendMsg(ERR_NOTONCHANNEL(client->getNickname(), channelName));
        else
		{
            std::string part_msg = getPartMsg(msg);
            client->sendMsg(RPL_PART(client->getNickname(), client->getUsername(), client->getHostname(), channelName, part_msg));
            client->sendMsgToChannel(RPL_PART(client->getNickname(), client->getUsername(), client->getHostname(), channelName, part_msg), ch);
            ch->removeClient(client);
            client->delJoinedChannel(ch);
            if (ch->getClients().empty())  // 채널 안에 클라이언트가 0명일 때
                delChannel(channelName);
        }
    }
}
