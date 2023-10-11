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

void	parseModes(std::string& modes) {
	if (modes.size() == 1)
		return modes.clear();
	if (modes.size() == 2 && !isalpha(modes.at(0)) && !isalpha(modes.at(1)))
		return modes.clear();
	if (modes[modes.size() - 1] == '+' || modes[modes.size() - 1] == '-')
		modes.erase(modes.size() - 1);
	else if (modes.size() == 3 && !isalpha(modes.at(0)) && !isalpha(modes.at(1)))
		modes.erase(0, 1);
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
	if (modes.size() == 1)
		return ;
	if (!ch->isOperator(client))
		return (client->sendMsg(ERR_CHANOPRIVSNEEDED(nick, channelName)));

	size_t arg_n = 2;
	char sign = modes[0];
	std::string set;
	std::string args;
	std::string error;
	std::string::iterator isBegin = modes.begin() + 1;
	Client *oper = NULL;
	if (modes[0] == '-' || modes[0] == '+')
		set += modes[0];
	while (isBegin != modes.end()) {
		if ((*isBegin) == '+' || (*isBegin) == '-'){
			sign = (*isBegin);
			set += (*isBegin);
		}
		switch ((*isBegin)) {
			case 'n':
				if (sign == '+' && ch->setMode('n') != -1)
					set += "n";
				else if (sign == '-' && ch->unSetMode('n') != -1)
					set += "n";
				break;
			case 't':
				if (sign == '+' && ch->setMode('t') != -1)
					set += "t";
				else if (sign == '-' && ch->unSetMode('t') != -1)
					set += "t";
				break;
			case '+':
				break;
			case '-':
				break;
			case 'i':
				if (sign == '+' && ch->setMode('i') != -1)
					set += "i";
				else if (sign == '-' && ch->unSetMode('i') != -1)
					set += "i";
				break;
			case 'l':
				if (sign == '+')
				{
					if (msg->params.size() < arg_n + 1) {
						client->sendMsg(ERR_NOLIMIT(nick, channelName));
						break;
					}
					else if (isInt(msg->params[arg_n])){
						ch->setUserLimit(msg->params[arg_n]);
						args += msg->params[arg_n] + " ";
						++arg_n;
						set += "l";
						ch->setMode('l');
					}
				}
				else if (sign == '-' && ch->unSetMode('l') != -1)
					set += "l";
				break;
			case 'o':
				if (msg->params.size() < arg_n + 1){
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
				else if (sign == '+' && ch->addOperator(oper))
					set += "o";
				else if (sign == '-' && ch->removeOperator(oper))
					set += "o";
				args += msg->params[arg_n] + " ";
				++arg_n;
				break;
			case 'k':
				if (msg->params.size() < arg_n + 1)
				{
					client->sendMsg(ERR_NOKEY(nick,channelName));
					break;
				}
				else if (sign == '+' && ch->setMode('k') != -1){
					set += "k";
					ch->setChannelPassword(msg->params[arg_n]);
					args += msg->params[arg_n] + " ";
				}
				else if (sign == '-' && ch->unSetMode('k') != -1)
					set += "k";
				++arg_n;
				break;
			default:
				error = *isBegin;
				client->sendMsg(ERR_UNKNOWNMODE(nick, error));
		}
		isBegin++;
	}

	std::string	sendMsg;
	parseModes(set);
	if (args.empty() && !set.empty())
		sendMsg = RPL_MODE_NOARG(client->getNickname(), client->getUsername(), client->getHostname(), channelName, set);
	else if (!set.empty())
		sendMsg = RPL_MODE(client->getNickname(), client->getUsername(), client->getHostname(), channelName, set, args);
	if (!set.empty()){
		client->sendMsgToChannel(sendMsg, ch);
		client->sendMsg(sendMsg);
	}
}

void Server::mode(Client *client, Message *msg)
{
	if (!client->isRegistered())
		return (client->sendMsg(ERR_NOTREGISTERED));
		
	std::string nick = client->getNickname();
	if (msg->params.empty())
		return (client->sendMsg(ERR_NEEDMOREPARAMS(nick, msg->command)));
	if (msg->params[0].at(0) == '#')
		channelModes(client, msg);
}
