#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Irc.hpp"
#include "Client.hpp"

class Client;

class Channel {
	private:
		std::vector<Client*> 			_clients;
		std::vector<std::string>		_kicked_users;
		std::vector<std::string>		_banned_users;
		std::vector<Client*>			_operators;
		std::vector<std::string>		_voiced_users;
		std::string 					_name;
		std::string						_topic;
		std::string						_mode;
		std::string						_channelPassword;
		int								_capacityLimit;
	public:
		Channel(Client* owner, const std::string& channelName);
		~Channel();

		std::vector<Client*>			getClientList () const;
		std::vector<std::string>		getKicked_users () const;
		std::vector<std::string>		getBanned_users () const;
		std::vector<Client *>			getOperators () const;
		std::vector<std::string>		getVoiced_users () const;
		std::string 					getName () const;
		std::string						getNames ();
		std::string						getOperatorPassword () const;
		std::string						getTopic () const;
		std::string						getMode () const;
		std::string						getChannelPassword () const;
		int								getCapacityLimit () const;

		void							addClient(Client* client);
		void							removeClient(Client* client);
		void							removeOperator(Client* client);
		void							setCapacityLimit(const int Limit);
		void							setChannelPassword(const std::string& str);
		void							setTopic(const std::string& str);

		bool							isOperator(Client* client);
};

#endif
