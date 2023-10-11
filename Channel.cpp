#include "Channel.hpp"

Channel::Channel(Client* owner, const std::string& channelName)
	:_name(channelName), _userLimit(-1), _modes("+nt") { _operators.push_back(owner); }
Channel::~Channel() {};

std::string Channel::getName() const { return _name; }
std::string Channel::getModes() const { return _modes; }
std::vector<Client *> Channel::getClients() const {return _clients; }
std::vector<Client *> Channel::getOperators() const {return _operators; }
std::string Channel::getTopic() const { return _topic; }
std::string Channel::getChannelPassword() const { return _channelPassword; }
size_t Channel::getUserLimit() const { return _userLimit; }

bool Channel::hasMode(char mode) const {
	if (_modes.find(mode) == std::string::npos)
		return (false);
	return (true);
}

bool	Channel::hasClient(Client *client) const {
	std::vector<Client*>::const_iterator isBegin = _clients.begin();
	std::string nick = client->getNickname();

	while (isBegin != _clients.end()){
		if (nick == (*isBegin)->getNickname())
			return true;
		isBegin++;
	}
	return false;
}

void Channel::setTopic(std::string topic) { _topic = topic; }
int Channel::setMode(char mode) {
	if (hasMode(mode))
		return -1;
	else
		_modes.push_back(mode);
	return static_cast<char>(mode);
}
int	Channel::unSetMode(char mode)
{
	if (hasMode(mode))
	{
	    _modes.erase(_modes.find(mode), 1);
		return static_cast<char>(mode);
	}
	else
		return -1;
}
void Channel::setChannelPassword(std::string password) { _channelPassword = password; }
void Channel::setUserLimit(std::string limit) {
	std::stringstream ss;
	size_t val;
	ss << limit;
	ss >> val;
	_userLimit = val;
	}

std::string Channel::getClientsName()
{
	std::vector<Client *>::iterator iter = _clients.begin();
	std::string names;
	while (iter != _clients.end())
	{
		if (isOperator(*iter))
			names += '@';
		names += (*iter)->getNickname() + " ";
		iter++;
	}
	return names;
}

bool Channel::addOperator(Client* client) {
	std::vector<Client*>::iterator isBegin = _operators.begin();
	while (isBegin != _operators.end()){
		if ((*isBegin) == client)
			return false;
		isBegin++;
	}
	_operators.push_back(client);
	return true;
}

void Channel::addClient(Client *client)
{
	_clients.push_back(client);
	client->addJoinedChannel(this);
}

void Channel::addInviteds(Client *client){
	_inviteds.push_back(client);
}

void Channel::removeClient(Client *client)
{
	for(std::vector<Client*>::iterator iter = _clients.begin(); iter != _clients.end(); ++iter) {
        if ((*iter) == client)
		{
            _clients.erase(iter);
			break;
		}
    }
    if (isOperator(client))
        removeOperator(client);
}



bool Channel::removeOperator(Client *client)
{
	for (std::vector<Client *>::iterator iter = _operators.begin(); iter != _operators.end(); ++iter)
	{
        if ((*iter) == client)
		{
            _operators.erase(iter);
			return true;
		}
    }
	return false;
}

bool Channel::isOperator(Client *client)
{
	std::vector<Client *>::iterator iter = _operators.begin();

	while (iter != _operators.end())
	{
		if (client == *iter)
			return (true);
		iter++;
	}
	return (false);
}


bool	Channel::isInvited(Client *client) const {
	std::vector<Client*>::const_iterator isBegin = _inviteds.begin();
	std::string nick = client->getNickname();

	while (isBegin != _inviteds.end()){
		if (nick == (*isBegin)->getNickname())
			return true;
		isBegin++;
	}
	return false;
}

bool	Channel::isValidKey(std::string ps) const {
	if (_channelPassword != ps)
		return false;
	return true;
}
