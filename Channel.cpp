#include "Channel.hpp"

Channel::Channel(Client* owner, const std::string& channelName)
	:_name(channelName), _userLimit(-1), _modes("+nt") { _operators.push_back(owner); }
Channel::~Channel() {};

std::string Channel::getName() const { return _name; }
std::vector<Client *> Channel::getClients() const {return _clients; }
std::vector<Client *> Channel::getOperators() const {return _operators; }
std::vector<std::string> Channel::getKickedUsers() const { return _kickedUsers; }
std::vector<std::string> Channel::getBannedUsers() const { return _bannedUsers; }
std::vector<std::string> Channel::getVoicedUsers() const { return _voicedUsers; }
std::string Channel::getTopic() const { return _topic; }
std::string Channel::getChannelPassword() const { return _channelPassword; }
int Channel::getUserLimit() const { return _userLimit; }

bool Channel::hasMode(char mode) const {
	if (_modes.find(mode) == std::string::npos)//no encontramos el char
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
char Channel::setMode(char mode) {
	if (hasMode(mode))
		return 0;
	else
		_modes.push_back(mode);
	return mode;
}
void Channel::setChannelPassword(std::string password) { _channelPassword = password; }
void Channel::setCapacityLimit(int limit) { _userLimit = limit; }

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

void Channel::removeOperator(Client *client)
{
	for (std::vector<Client *>::iterator iter = _operators.begin(); iter != _operators.end(); ++iter)
	{
        if ((*iter) == client)
		{
            _operators.erase(iter);
			return ;
		}
    }
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
