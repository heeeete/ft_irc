#include "../Server.hpp"

bool	isInt(std::string input)
{
	size_t	digit = 0;
	std::string::iterator it = input.begin();
	while (it != input.end() && std::isdigit(*it))
	{
		digit++;
		it++;
	}
	if (digit != input.size())
		return false;
	else if (digit >= 1 && digit < 4)
		return true;
	else
		std::cerr << "User limit exceeded" << std::endl;
	return false;
}

void Server::channelModes(Client *client, Message *msg) {
	std::string nick = client->getNickname();
	std::string channelName = msg->params[0];
	Channel	*ch = getChannel(channelName);

	if (!ch)
		return (client->sendMsg(ERR_NOSUCHCHANNEL(nick, channelName)));
	if (msg->params.size() == 1)
		return (client->sendMsg(RPL_CHANNELMODEIS(nick, channelName, ch->getModes())));
	std::string modes = msg->params[1];
	if (!ch->isOperator(client))
		return (client->sendMsg(ERR_CHANOPRIVSNEEDED(nick, channelName)));

	size_t arg_n = 2;
	char sign = modes[0];
	std::string args;
	std::string error;
	std::string::iterator isBegin = modes.begin() + 1;	// +nt 면 n 부터 시작
	Client *oper = NULL;
	while (isBegin != modes.end()) {
		if ((*isBegin) == '+')
			sign = '+';
		else if ((*isBegin) == '-')
			sign = '-';
		std::cout << (*isBegin) << "\n";
		switch ((*isBegin))
		{
		case 'n':
		case 't':
		case '+':
		case '-':
		case 'i':
			if (sign == '+')
				ch->setMode('i');
			else if (sign == '-')
				ch->unSetMode('i');
		break;
		case 'l':
			if (sign == '+')
			{
				if (msg->params.size() < arg_n + 1)
					client->sendMsg(ERR_NOLIMIT(nick, channelName));
				else if (isInt(msg->params[arg_n])){
					ch->setUserLimit(msg->params[arg_n]);
					args += msg->params[arg_n] + " ";
					++arg_n;
					ch->setMode('l');
				}
			}
			else if (sign == '-')
				ch->unSetMode('l');
		break;
		case 'o':
			if (msg->params.size() < arg_n + 1)
			{
				client->sendMsg(ERR_NONICK(nick,channelName));
				break;
			}
			oper = getClient((msg->params[arg_n]));
			if (!oper){
				client->sendMsg(ERR_NOSUCHNICK(nick, msg->params[arg_n]));
				break;
			}
			if (!ch->hasClient(oper)){
				client->sendMsg(ERR_USERNOTINCHANNEL(nick, oper->getNickname(), channelName));
				break;
			}
			if (sign == '+')
				ch->addOperator(oper);
			else if (sign == '-')
				ch->removeOperator(oper);
			args += msg->params[arg_n] + " ";
			++arg_n;
		break;

		default:
			error = *isBegin;
			modes.erase(modes.find(error, 1));
			std::cout << modes << "\n";
			client->sendMsg(ERR_UNKNOWNMODE(nick, error));
			continue;
		}
		isBegin++;
	}
	std::string	temp;
	if (args.empty())
		temp = ":" + client->getNickname() + "!" + client->getUsername() + "@" + client->getHostname() + " " + "MODE " + channelName + " :" + modes + END_CHARACTERS;
	else
		temp = ":" + client->getNickname() + "!" + client->getUsername() + "@" + client->getHostname() + " " + "MODE " + channelName + " " + modes + " :" + args + END_CHARACTERS;
	client->sendMsgToChannel(temp, ch);
	client->sendMsg(temp);
}

void Server::mode(Client *client, Message *msg)
{
	std::string nick = client->getNickname();
	if (msg->params.empty())
		return (client->sendMsg(ERR_NEEDMOREPARAMS(nick, msg->command)));
	if (msg->params[0].at(0) == '#')
		channelModes(client, msg);
}
