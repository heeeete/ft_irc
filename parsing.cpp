#include "Message.hpp"

Message parseMessage(std::string input)
{
   	Message msg;

    if (input.find(' ') == std::string::npos)
	{
		msg.command = input;
		return msg;
    }

    while (input[0] == ' ' || input[0] == '\r' ||  input[0] == '\n' \
			|| input[0] == 'v' || input[0] == '\t' || input[0] == '\f')
        input = input.substr(1);

    if (input[0] == ':')
	{
        size_t prefixEnd = input.find(' ');
        if (prefixEnd != std::string::npos)
		{
            msg.prefix = input.substr(1, prefixEnd - 1);
            input = input.substr(prefixEnd + 1);
        }
		else	
			return msg;
    }

    size_t commandEnd = input.find(' ');
    if (commandEnd != std::string::npos)
	{
        msg.command = input.substr(0, commandEnd);
        input = input.substr(commandEnd + 1);
    }
	else 
        return msg;

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


void	printMessage(const Message& msg)
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

