#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "Irc.hpp"
#include "Channel.hpp"

class Channel;

class Client {
private:
	int _clientSocket;
	int	_pollFdIdx;

	std::string _nickname;
	std::string _hostname;
	std::string _username;
	std::string _realname;

	std::string _readBuf;

	bool _hasValidPassword; // 유효한 비밀번호를 가지고 있는지 
	bool _isNicknameRegistered; // 닉네임 등록됐는지  
	bool _isUserinfoRegistered; // 유저정보 등록됐는지  
	bool _isRegistered; // 최종 등록됐는지 
	bool _shouldBeDeleted; // 삭제되어야 하는지 

	std::vector<Channel *> _joinedChannels; // 클라이언트가 들어간 채널

public:
	Client(int clientSocket);

	// readBuf 관련 함수 
	std::string getReadBuf() const;
	void setReadBuf(const std::string buf);
	void clearReadBuf();

	// getter
	int getClientSocket() const;
	int getPollFdIdx() const;
	std::string getNickname() const;
	std::string getHostname() const;
	std::string getUsername() const;
	std::string getRealname() const;
	std::vector<Channel *> getJoinedChannels() const;

	bool hasValidPassword() const;
	bool isNicknameRegistered() const;
	bool isUserinfoRegistered() const;
	bool isRegistered() const;
	bool shouldBeDeleted() const;

	// setter
	void setPollFdIdx(const int pollFdIdx);
	void setNickname(const std::string nickname);
	void setHostname(const std::string hostname);
	void setUsername(const std::string username);
	void setRealname(const std::string realname);
	void setHasValidPassword(bool hasValidPassword);
	void setIsNicknameRegistered(bool isRegistered);
	void setIsUserinfoRegistered(bool isRegistered);
	void setIsRegistered(bool isRegistered);
	void setShouldBeDeleted(bool shouldBeDeleted);

	//채널 관련 함수 
	void addJoinedChannel(Channel *channel);
	void delJoinedChannel(Channel *channel);

	//기타 util 
	void sendMsg(std::string msg);
	void sendMsgToChannel(std::string msg, Channel *target);
	bool isRegistrationRequired();
	void registration();

};

#endif 