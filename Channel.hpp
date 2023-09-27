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
		std::string						_topic;
		std::string						_mode;
		std::string						_channelPassword;
		int								_capacityLimit;
	public:
		Channel(const std::string& channelName);
		~Channel();

		std::map<std::string, Client>	getClientList () const;
		std::vector<std::string>		getKicked_users () const;
		std::vector<std::string>		getBanned_users () const;
		std::vector<std::string>		getOperators () const;
		std::vector<std::string>		getVoiced_users () const;
		std::string 					getName () const;
		std::string						getOperatorPassword () const;
		std::string						getTopic () const;
		std::string						getMode () const;
		std::string						getChannelPassword () const;
		int								getCapacityLimit () const;

		void							setCapacityLimit(const int Limit);
		void							setChannelPassword(const std::string& str);
		void							setTopic(const std::string& str);
};

#endif
