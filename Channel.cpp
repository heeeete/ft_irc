#include "Channel.hpp"

Channel::Channel(Client* owner, const std::string& channelName) 
	:_name(channelName), _capacityLimit(-1) { _operators.push_back(owner); }
Channel::~Channel() {};

std::string Channel::getName() const { return _name; }
std::vector<Client *> Channel::getClients() const {return _clients; }
std::vector<Client *> Channel::getOperators() const {return _operators; }
std::vector<std::string> Channel::getKickedUsers() const { return _kickedUsers; }
std::vector<std::string> Channel::getBannedUsers() const { return _bannedUsers; }
std::vector<std::string> Channel::getVoicedUsers() const { return _voicedUsers; }
std::string Channel::getTopic() const { return _topic; }
std::string Channel::getMode() const { return _mode; }
std::string Channel::getChannelPassword() const { return _channelPassword; }
int Channel::getCapacityLimit() const { return _capacityLimit; }

void Channel::setTopic(std::string topic) { _topic = topic; }
void Channel::setMode(std::string mode) { _mode = mode; }
void Channel::setChannelPassword(std::string password) { _channelPassword = password; }
void Channel::setCapacityLimit(int limit) { _capacityLimit = limit; }

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
}

void Channel::removeClient(Client *client)
{
	for(std::vector<Client*>::iterator iter = _clients.begin(); iter != _clients.end(); ++iter) {
        if ((*iter)->getNickname() == client->getNickname())
            _clients.erase(iter);
        if (isOperator(client))
            removeOperator(client);
        client->delJoinedChannel(this);
    }
}

void Channel::removeOperator(Client *client)
{
	for (std::vector<Client *>::iterator iter = _operators.begin(); iter != _operators.end(); ++iter) 
	{
        if ((*iter)->getNickname() == client->getNickname())
            _operators.erase(iter);
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