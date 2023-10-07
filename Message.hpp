#ifndef MESSAGE_HPP
# define MESSAGE_HPP

#include "Irc.hpp"

struct Message {
    std::string prefix;
    std::string command;
    std::vector<std::string> params;
};

Message		parseMessage(std::string input);
void		printMessage(const Message& msg);

#endif
