#include "../Client.hpp"
#include "../DefineReplies.hpp"

void    welcomeMsg(Client &client)
{
    client.sendMsg(client.getClientSocket(), RPL_WELCOME(client.getNickName(), client.getUserName(), client.getHostName()));
	client.sendMsg(client.getClientSocket(), RPL_YOURHOST(client.getNickName(), client.getServer().getName(), "1.0"));
	client.sendMsg(client.getClientSocket(), RPL_CREATED(client.getNickName(), ctime(client.getServer().getStartTime())));
	client.sendMsg(client.getClientSocket(), RPL_MYINFO(client.getNickName(), client.getServer().getName(), "1.0", "Channel modes +ntikl", ""));
}

void    user(Client &client, Message *msg)
{
    if (msg->params.size() < 4)
        client.sendMsg(client.getClientSocket(), ERR_NEEDMOREPARAMS(client.getNickName(), msg->command));
    if (client.getRegistrationDone())
        client.sendMsg(client.getClientSocket(), ERR_ALREADYREGISTRED(client.getNickName()));

    client.setUserName(msg->params[1]);
    client.setHostName(msg->params[2]);
    client.setRealName(msg->params[3]);
    client.setRegistrationDone(true);

    if (!client.getWelecomeSent())
        welcomeMsg(client);
    client.setWelecomeSent(true);
}
