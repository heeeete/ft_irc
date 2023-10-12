#include "Client.hpp"

Client::Client(int clientSocket) : _clientSocket(clientSocket)
{
	_nickname = "*";
	_hasValidPassword = false;
	_isNicknameRegistered = false;
	_isUserinfoRegistered = false;
	_isRegistered = false;
	_shouldBeDeleted = false;
}

// readBuf 관련 함수
std::string Client::getReadBuf() const {return _readBuf; }
void Client::setReadBuf(const std::string buf) { _readBuf += buf; }
void Client::clearReadBuf() { _readBuf.clear(); }

// getter
int Client::getClientSocket() const {return _clientSocket; }
int Client::getPollFdIdx() const {return _pollFdIdx; }
std::string Client::getNickname() const { return _nickname; }
std::string Client::getHostname() const { return _hostname; }
std::string Client::getUsername() const { return _username; }
std::string Client::getRealname() const { return _realname; }
std::vector<Channel *> Client::getJoinedChannels() const { return _joinedChannels; }

bool Client::hasValidPassword() const { return _hasValidPassword; }
bool Client::isNicknameRegistered() const { return _isNicknameRegistered; }
bool Client::isUserinfoRegistered() const { return _isUserinfoRegistered; }
bool Client::isRegistered() const { return _isRegistered; }
bool Client::shouldBeDeleted() const { return _shouldBeDeleted; }

// setter
void Client::setPollFdIdx(const int pollFdIdx) { _pollFdIdx = pollFdIdx; }
void Client::setNickname(const std::string nickname) { _nickname = nickname; }
void Client::setHostname(const std::string hostname) { _hostname = hostname; }
void Client::setUsername(const std::string username) { _username = username; }
void Client::setRealname(const std::string realname) { _realname = realname; }
void Client::setHasValidPassword(bool hasValidPassword) { _hasValidPassword = hasValidPassword; }
void Client::setIsNicknameRegistered(bool isRegistered) { _isNicknameRegistered = isRegistered; }
void Client::setIsUserinfoRegistered(bool isRegistered) { _isUserinfoRegistered = isRegistered; }
void Client::setIsRegistered(bool isRegistered) { _isRegistered = isRegistered; }
void Client::setShouldBeDeleted(bool shouldBeDeleted) { _shouldBeDeleted = shouldBeDeleted; }

void Client::addJoinedChannel(Channel *channel) { _joinedChannels.push_back(channel); }
void Client::delJoinedChannel(Channel *channel)
{
	for (std::vector<Channel *>::iterator iter = _joinedChannels.begin(); iter != _joinedChannels.end(); ++iter)
	{
		if ((*iter) == channel)
		{
			_joinedChannels.erase(iter);
			return ;
		}
	}
}

// 클라이언트한테 메시지 보내기
void Client::sendMsg(std::string msg)
{
	ssize_t cnt = 0;
	int a = 0;
	while (1){
		cnt = send(_clientSocket, msg.c_str(), msg.length(), 0);
		a += cnt;
		if (cnt < 0) {
			perror("send failed");
			break;
		}
		else if (msg.find(END_CHARACTERS, 0) == std::string::npos){
			msg.erase(0, cnt);
		}
		else break;
	}
	std::cout << "========== send client " << _clientSocket << " ==========\n";
	std::cout << msg << "\n\n";
}

void	Client::sendMsgClient(std::string msg, Client *target)
{
	if (send(target->getClientSocket(), msg.c_str(), msg.length(), 0) < 0)
			perror("SEND FAILED");
}

// 등록 과정 필요한지 알려줌
bool Client::isRegistrationRequired()
{
	if (!_isRegistered && _isNicknameRegistered && _isUserinfoRegistered)
		return (true);
	return (false);
}

void Client::sendMsgToChannel(std::string msg, Channel *target)
{
	std::vector<Client *> clients = target->getClients();
	std::vector<Client *>::iterator iter = clients.begin();

	while (iter != clients.end())
	{
		if ((*iter)->getNickname() != _nickname)
			(*iter)->sendMsg(msg);
		iter++;
	}
}

bool Client::isInChannel(std::string channelName)
{
	std::vector<Channel *>::iterator iter = _joinedChannels.begin();
	while (iter != _joinedChannels.end())
	{
		if ((*iter)->getName() == channelName)
			return (true);
		iter++;
	}
	return (false);
}
