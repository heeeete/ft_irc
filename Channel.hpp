#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Irc.hpp"
# include "Client.hpp"

class Client;

class Channel 
{
private:
	std::string _name; // 채널 이름
	std::vector<Client *> _clients; // 채널에 속한 클라이언트들
	std::vector<Client *> _operators; //채널 오퍼레이터들

	std::vector<std::string> _kickedUsers;
	std::vector<std::string> _bannedUsers;
	std::vector<std::string> _voicedUsers;

	std::string _topic;
	std::string _mode;
	std::string _channelPassword;
	int _capacityLimit; // 뭔지 모르겠음 

public:
	Channel(Client* owner, const std::string& channelName);
	~Channel();

	// getter
	std::string getName() const; 
	std::vector<Client *> getClients() const;
	std::vector<Client *> getOperators() const;
	std::vector<std::string> getKickedUsers() const;
	std::vector<std::string> getBannedUsers() const;
	std::vector<std::string> getVoicedUsers() const;
	std::string getTopic() const;
	std::string getMode() const;
	std::string getChannelPassword() const;
	int getCapacityLimit() const;

	// setter
	void setTopic(std::string topic);
	void setMode(std::string mode);
	void setChannelPassword(std::string password);
	void setCapacityLimit(int limit);

	std::string getClientsName(); // 채널에 속한 클라이언트 이름들 가공
	void addClient(Client *client);
	void removeClient(Client *client);
	void removeOperator(Client* client);

	bool isOperator(Client *client);
};

#endif