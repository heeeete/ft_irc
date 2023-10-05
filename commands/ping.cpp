#include "../Irc.hpp"
#include "../commands.hpp"
#include "../DefineReplies.hpp"

void    ping(Client &client, Message *msg)
{
    if (msg->params.empty())
        client.sendMsg(client.getClientSocket(), ERR_NOORIGIN);
    else
        client.sendMsg(client.getClientSocket(), RPL_PONG(msg->params[0]));
}