#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Irc.hpp"
# include "Client.hpp"

class Client;

class Channel
{
private:
	std::string _name; // 채널 이름
	std::string _modes;
	std::vector<Client *> _clients; // 채널에 속한 클라이언트들
	std::vector<Client *> _operators; //채널 오퍼레이터들
	std::vector<Client *> _inviteds;

	std::string _topic;
	std::string _channelPassword;
	size_t _userLimit;

public:
	Channel(Client* owner, const std::string& channelName);
	~Channel();

	// getter
	std::string getName() const;
	std::string getModes() const;
	std::vector<Client *> getClients() const;
	std::vector<Client *> getOperators() const;
	std::string getTopic() const;
	std::string getChannelPassword() const;
	size_t getUserLimit() const;


	// setter
	void setTopic(std::string topic);
	int setMode(char mode);
	int unSetMode(char mode);
	void setChannelPassword(std::string password);
	void setUserLimit(std::string limit);

	bool	hasMode(char mode) const;
	bool	hasClient(Client *client) const;

	std::string getClientsName(); // 채널에 속한 클라이언트 이름들 가공
	void addClient(Client *client);
	void addInviteds(Client *client);
	void removeClient(Client *client);
	bool addOperator(Client* client);
	bool removeOperator(Client* client);

	bool	isOperator(Client *client);
	bool	isInvited(Client *client) const;
	bool	isValidKey(std::string ps) const;
};

#endif
