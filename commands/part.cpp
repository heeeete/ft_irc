#include "../Irc.hpp"
#include "../commands.hpp"
#include "../DefineReplies.hpp"

int checkJoinedChannels(Client* client, std::string &channelName)
{
    std::vector<Channel *>::iterator _it = client->getJoinedChannels().begin();
    std::vector<Channel *>::iterator _it_end = client->getJoinedChannels().end();
    for ( ; _it != _it_end; ++_it) {
        if ((*_it)->getName() == channelName)
            return (1);
    }
    return (0);
}

std::string getPartMsg(Message *msg)
{
	if (msg->params.size() == 1) // PART_MSG not_defined
		return ("See ya!");
	return(msg->params[1]);
}

void    part(Client* client, Message *msg)
{
    if (msg->params.empty())
		client->sendMsg(client->getClientSocket(), ERR_NEEDMOREPARAMS(client->getNickName(), msg->command[0]));

    std::stringstream	ss(msg->params[0]);
	std::string			channelName;
	while (std::getline(ss, channelName, ',')) {
        Channel *ch = client->getServer().getChannel(channelName);
		if (!ch)    // 해당 채널이 존재하는가
			client->sendMsg(client->getClientSocket(), ERR_NOSUCHCHANNEL(client->getNickName(), channelName));
        else if (!checkJoinedChannels(client, channelName)) // 해당 사용자가 채널에 join한 상태인가
            client->sendMsg(client->getClientSocket(), ERR_NOTONCHANNEL(client->getNickName(), channelName));
        else {
            std::string part_msg = getPartMsg(msg);
            client->sendMsg(client->getClientSocket(), RPL_PART(client->getNickName(), channelName, part_msg));
            ch->removeClient(client);
            if (!ch->getClientList().size())  // 채널 안에 클라이언트가 0명일 때
                client->getServer().delChannel(channelName);
            // else if (!ch->getOperators.size()) {    // 채널 안에 operator가 없을 때
            //     ch->removeAllClient();
            //     client->getServer()->delChannel(channelName);
            // }
        }
    }
}