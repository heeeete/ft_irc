#include "Channel.hpp"

Channel::Channel(Client* owner, const std::string& channalName): _name(channalName), _capacityLimit(-1) {
	_operators.push_back(owner);
}
Channel::~Channel(){}

std::vector<Client*>			Channel::getClientList () const {return _clients;}
std::vector<Client*>			Channel::getOperators () const {return _operators;}
std::vector<std::string>		Channel::getKicked_users () const {return _kicked_users;}
std::vector<std::string>		Channel::getBanned_users () const {return _banned_users;}
std::vector<std::string>		Channel::getVoiced_users () const {return _voiced_users;}
std::string 					Channel::getName () const {return _name;}
std::string						Channel::getNames () {
	std::vector<Client*>::iterator isbegin = _clients.begin();
	std::string names;
	while(isbegin != _clients.end()) {
		if (isOperator(*isbegin))
			names += '@';
		names += (*isbegin)->getNickName() + " ";
		isbegin++;
	}
	return names;
}
std::string						Channel::getTopic () const {return _topic;}
std::string						Channel::getMode () const {return _mode;}
std::string						Channel::getChannelPassword () const {return _channelPassword;}
int								Channel::getCapacityLimit () const {return _capacityLimit;}

void							Channel::addClient(Client* client) {
	_clients.push_back(client);
	client->addJoinedChannel(this);
}

void							Channel::setCapacityLimit(const int Limit) {_capacityLimit = Limit;}
void							Channel::setChannelPassword(const std::string& str) {_channelPassword = str;}
void							Channel::setTopic(const std::string& str) {_topic = str;}

bool							Channel::isOperator(Client* client){
	std::vector<Client*>::iterator isbegin = _operators.begin();

	while (isbegin != _operators.end()){
		if (client == *isbegin)
			return true;
		isbegin++;
	}
	return false;
}
