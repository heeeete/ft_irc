#include "Message.hpp"
#include "commands.hpp"

Message parseMessage(std::string input) {
	Message msg;

	// Validar que hay al menos un espacio
    if (input.find(' ') == std::string::npos)
	{
		msg.command = input;
		return msg;
    }
	// Eliminate empty spaces and special characters at the beginning of the entry
    while (input[0] == ' ' || input[0] == '\r' ||  input[0] == '\n' \
			|| input[0] == 'v' || input[0] == '\t' || input[0] == '\f')
        input = input.substr(1);
    // Parsing prefix
    if (input[0] == ':')
	{
        size_t prefixEnd = input.find(' ');
        if (prefixEnd != std::string::npos)
		{
            msg.prefix = input.substr(1, prefixEnd - 1);
            input = input.substr(prefixEnd + 1);
        }
		else	// Invalid message
			return msg;
    }

    // Parsing command
    size_t commandEnd = input.find(' ');
    if (commandEnd != std::string::npos)
	{
        msg.command = input.substr(0, commandEnd);
        input = input.substr(commandEnd + 1);
    }
	else // Invalid message
        return msg;

    // Parsing parameters
    while (input[0] == ' ')
        input = input.substr(1);
    while (input.length() > 0)
	{
        if (input[0] == ':')
		{
            msg.params.push_back(input.substr(1));
            break;
        }
		else
		{
            size_t paramEnd = input.find(' ');
            if (paramEnd != std::string::npos)
			{
                msg.params.push_back(input.substr(0, paramEnd));
                input = input.substr(paramEnd + 1);
            }
			else
			{
                msg.params.push_back(input);
                break;
            }
        }
    }
    return msg;
}


void	print_message(const Message& msg)
{
    if (!msg.prefix.empty()) {
        std::cout << ":" << msg.prefix << " ";
    }
    std::cout << "msg.command =";
    std::cout << msg.command;
    std::cout << std::endl;

    std::cout << "msg.params =";
	for (std::vector<std::string>::const_iterator it = msg.params.begin(); it != msg.params.end(); ++it)
	{
        std::cout << " " << *it << std::endl;
    }
    std::cout << std::endl << std::endl;
}

void    executeCmd(Message *msg)
{
	std::string validCmds[] = {
		"NICK", "USER", "PASS", "JOIN", "KICK", "INVITE", "TOPIC", "MODE", "PART",
		"QUIT", "LIST", "NAMES", "PRIVMSG", "NOTICE", "PING", "PONG", "WHOIS", "WHOWAS"
	};

	int index = 1;

	while (validCmds[index] != msg->command) {
		index++;
	}

	switch(index) {
		case 1: nick(); break;
		case 2: user(); break;
		case 3: pass(); break;
		case 4: join(); break;
		case 5: kick(); break;
		case 6: invite(); break;
		case 7: topic(); break;
		case 8: mode(); break;
		case 9: part(); break;
		case 10: quit(); break;
		case 11: list(); break;
		case 12: names(); break;
		case 13: privmsg(); break;
		case 14: notice(); break;
		case 15: ping(); break;
		case 16: pong(); break;
		case 17: whois(); break;
		case 18: whowas(); break;
	}
}