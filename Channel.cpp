#include "Channel.hpp"

Channel::Channel(const std::string& channalName): _name(channalName), _capacityLimit(-1) {}
Channel::~Channel(){}

std::map<std::string, Client>	Channel::getClientList () const {return _clientList;}
std::vector<std::string>		Channel::getKicked_users () const {return _kicked_users;}
std::vector<std::string>		Channel::getBanned_users () const {return _banned_users;}
std::vector<std::string>		Channel::getOperators () const {return _operators;}
std::vector<std::string>		Channel::getVoiced_users () const {return _voiced_users;}
std::string 					Channel::getName () const {return _name;}
std::string						Channel::getTopic () const {return _topic;}
std::string						Channel::getMode () const {return _mode;}
std::string						Channel::getChannelPassword () const {return _channelPassword;}
int								Channel::getCapacityLimit () const {return _capacityLimit;}

void							setCapacityLimit(const int Limit)
