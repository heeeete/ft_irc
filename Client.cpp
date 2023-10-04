#include "Client.hpp"

Client::Client(int clientSocket) : _clientSocket(clientSocket) {}
Client::~Client(){}

int			Client::getClientSocket() const {return _clientSocket;}
std::string	Client::getReadBuf() const {return _readBuf;}
std::string	Client::getSendBuf() const {return _sendBuf;}
bool		Client::getToDeconnect() const {return _toDeconnect;}
std::string	Client::getNickName() const {return _nickName;}
std::string	Client::getOldNickName() const {return _oldNickName;}
std::string	Client::getUserName() const {return _userName;}
std::string	Client::getRealName() const { return _realName;}
std::string	Client::getMode() const {return _mode;}
bool		Client::getConnexionPassword() const {return _connexionPassword;}
bool		Client::getRegistrationDone() const {return _registrationDone;}
bool		Client::getWelecomeSent() const {return _welcomeSent;}
bool		Client::getHasAllInfo() const {return _hasAllInfo;}
int			Client::getNbInfo() const {return _nbInfo;}

void		Client::setReadBuf(const std::string buf) {
	_readBuf += buf;

	if (_readBuf.find(END_CHARACTERS) != std::string::npos )
	{
		processBuffer(_readBuf);
		_readBuf.clear();
	}
}

void		Client::processBuffer(const std::string& buf) {
	Message	m;

	if (buf.find_first_of(VALID_CHARACTERS) == std::string::npos)
		return ;

	std::cout << "BUF = " << buf << "\n";
	char	*token = strtok(const_cast<char *>(buf.c_str()), END_CHARACTERS);
	std::cout << "token = " << token << "\n";
	if (token == NULL)
		return ;
	while(token != NULL) {
		std::string command(token);
		m = parseMessage(token);
		print_message(m);
		execCmd(&m);
		token = strtok(NULL, END_CHARACTERS);
	}
}

void			Client::execCmd(Message *msg)
{
}

void		Client::setToDeconnect(const bool status) {_toDeconnect = status;}
void		Client::setNickName(const std::string& str) {_nickName = str;}
void		Client::setOldNickName(const std::string& str) {_oldNickName = str;};
void		Client::setUserName(const std::string& str) {_userName = str;};
void		Client::setRealName(const std::string& str) {_realName = str;};
void		Client::setMode(const std::string& str) {_mode = str;};
void		Client::setConnexionPassword(const bool status) {_connexionPassword = status;}
void		Client::setRegistrationDone(const bool status) {_registrationDone = status;}
void		Client::setWelecomeSent(const bool status) {_welcomeSent = status;}
void		Client::setHasAllInfo(const bool status) {_hasAllInfo = status;}
void		Client::setNbInfo(const int count) {_nbInfo = count;}
