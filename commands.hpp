#ifndef COMMANDS_HPP
# define COMMANDS_HPP

#include "Client.hpp"

void    nick(Client &client, Message *msg);
void    user(Client &client, Message *msg);
void    welcomeMsg(Client &client);
void    pass(Client &client, Message *msg);
void    join(Client* client, Message *msg);
void    kick();
void    invite();
void    topic();
void    mode();
void    part();
void    quit(Client &client, Message *msg);
void    privmsg();
void    notice();
void    ping(Client &client, Message *msg);

#endif
