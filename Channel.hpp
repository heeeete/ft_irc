#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <map>
#include "Client.hpp"

class Client;

class Channel {
	private:
		std::map<std::string, Client>	_clientList;
		std::vector<std::string>		_kicked_users;
		std::vector<std::string>		_banned_users;
		std::vector<std::string>		_operators;
		std::vector<std::string>		_voiced_users;
		std::string 					_name;
		std::string						_operatorPassword;
		std::string						_topic;
		std::string						_mode;
		std::string						_channel_password;
		int								_capacity_limit;
	public:
		Channel(const std::string& channelName);
};

#endif
