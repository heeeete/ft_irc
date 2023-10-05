#include "../Irc.hpp"
#include "../commands.hpp"
#include "../DefineReplies.hpp"

void    join(Client &client, Message *msg) {
	if (msg->params.empty())
		client.sendMsg(client.getClientSocket(), ERR_NEEDMOREPARAMS(client.getNickName(), msg->command[0]));
}
