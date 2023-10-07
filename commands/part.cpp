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
	if (msg->params.size() == 1) // PART_MSG not_defined
		return ("See ya!");
	return(msg->params[1]);
}

void Server::part(Client *client, Message *msg)
{
    if (msg->params.empty())
		client->sendMsg(ERR_NEEDMOREPARAMS(client->getNickname(), msg->command[0]));

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
            client->sendMsg(RPL_PART(client->getNickname(), channelName, part_msg));
            ch->removeClient(client); 
            if (!ch->getClients().size())  // 채널 안에 클라이언트가 0명일 때
                delChannel(channelName);
            // else if (!ch->getOperators().size()) {    // 채널 안에 operator가 없을 때
            //     ch->removeAllClient();
            //     delChannel(channelName);
            // }
        }
    }
}