#ifndef COMMANDS_HPP
# define COMMANDS_HPP

#include "Client.hpp"

void    nick();
void    user(Client &client, Message *msg);
void    welcomeMsg(Client &client);
void    pass();
void    join();
void    kick();
void    invite();
void    topic();
void    mode();
void    part();
void    quit();
void    list();
void    names();
void    privmsg();
void    notice();
void    ping();
void    pong();
void    whois();
void    whowas();

#endif