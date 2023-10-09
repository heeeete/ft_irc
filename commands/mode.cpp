#include "../Server.hpp"

static bool	isInt(std::string input)
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
	size_t cnt = 0;
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
		switch ((*isBegin)) {
			case 'n':
				++cnt;
				break;
			case 't':
				++cnt;
				if (sign == '+')
					ch->setMode('t');
				else if (sign == '-')
					ch->unSetMode('t');
				break;
			case '+':
				break;
			case '-':
				break;
			case 'i':
				if (sign == '+')
					ch->setMode('i');
				else if (sign == '-')
					ch->unSetMode('i');
				++cnt;
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
				++cnt;
				break;
			case 'o':
				if (msg->params.size() < arg_n + 1)
				{
					client->sendMsg(ERR_NONICK(nick,channelName));
					break;
				}
				oper = getClient((msg->params[arg_n]));
				if (!oper)
					client->sendMsg(ERR_NOSUCHNICK(nick, msg->params[arg_n]));
				else if (!ch->hasClient(oper))
					client->sendMsg(ERR_USERNOTINCHANNEL(nick, oper->getNickname(), channelName));
				else if (sign == '+')
					ch->addOperator(oper);
				else if (sign == '-')
					ch->removeOperator(oper);
				args += msg->params[arg_n] + " ";
				++cnt;
				++arg_n;
				break;
			case 'k':
				if (msg->params.size() < arg_n + 1)
					client->sendMsg(ERR_NONICK(nick,channelName));
				else if (sign == '+'){
					ch->setMode('k');
					ch->setChannelPassword(msg->params[arg_n]);
					args += msg->params[arg_n] + " ";
					++arg_n;
				}
				else if (sign == '-')
					ch->unSetMode('k');
				++cnt;
				break;
			default:
				error = *isBegin;
				modes.erase(modes.find(error, 1), 1);
				client->sendMsg(ERR_UNKNOWNMODE(nick, error));
				continue;
		}
		isBegin++;
	}
	std::string	temp;
	if (args.empty() && cnt)
		temp = RPL_MODE_NOARG(client->getNickname(), client->getUsername(), client->getHostname(), channelName, modes);
	else if (cnt)
		temp = RPL_MODE(client->getNickname(), client->getUsername(), client->getHostname(), channelName, modes, args);
	if (cnt){
		client->sendMsgToChannel(temp, ch);
		client->sendMsg(temp);
	}
}

void Server::mode(Client *client, Message *msg)
{
	std::string nick = client->getNickname();
	if (msg->params.empty())
		return (client->sendMsg(ERR_NEEDMOREPARAMS(nick, msg->command)));
	if (msg->params[0].at(0) == '#')
		channelModes(client, msg);
}
