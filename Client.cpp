#include "Client.hpp"
#include "commands.hpp"

Client::Client(int clientSocket, Server *s): _clientSocket(clientSocket), _server(s) {}
Client::~Client(){}

int			Client::getClientSocket() const {return _clientSocket;}
std::string	Client::getReadBuf() const {return _readBuf;}
std::string	Client::getSendBuf() const {return _sendBuf;}
bool		Client::getToDeconnect() const {return _toDeconnect;}
std::string	Client::getNickName() const {return _nickName;}
std::string	Client::getOldNickName() const {return _oldNickName;}
std::string	Client::getUserName() const {return _userName;}
std::string	Client::getRealName() const { return _realName;}
std::string Client::getHostName() const { return _hostName;}
std::string	Client::getMode() const {return _mode;}
bool		Client::getConnexionPassword() const {return _connexionPassword;}
bool		Client::getRegistrationDone() const {return _registrationDone;}
bool		Client::getWelecomeSent() const {return _welcomeSent;}
bool		Client::getHasAllInfo() const {return _hasAllInfo;}
int			Client::getNbInfo() const {return _nbInfo;}
Server		Client::getServer() const {return *_server;}

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
		executeCmd(&m);
		token = strtok(NULL, END_CHARACTERS);
	}
}

void    Client::executeCmd(Message *msg)
{
	std::string validCmds[] = {
		"NICK", "USER", "PASS", "JOIN", "KICK", "INVITE", "TOPIC", "MODE", "PART",
		"QUIT", "LIST", "NAMES", "PRIVMSG", "NOTICE", "PING", "PONG", "WHOIS", "WHOWAS"
	};

	int index = 0;
	while (index < 18 && validCmds[index] != msg->command) {
		index++;
	}

	switch(index) {
		case 0: nick(*this, msg); break;
		case 1: user(*this, msg); break;
		case 2: pass(); break;
		case 3: join(); break;
		case 4: kick(); break;
		case 5: invite(); break;
		case 6: topic(); break;
		case 7: mode(); break;
		case 8: part(); break;
		case 9: quit(); break;
		case 10: list(); break;
		case 11: names(); break;
		case 12: privmsg(); break;
		case 13: notice(); break;
		case 14: ping(); break;
		case 15: pong(); break;
		case 16: whois(); break;
		case 17: whowas(); break;
	}
}

void		Client::setToDeconnect(const bool status) {_toDeconnect = status;}
void		Client::setNickName(const std::string& str) {_nickName = str;}
void		Client::setOldNickName(const std::string& str) {_oldNickName = str;}
void		Client::setUserName(const std::string& str) {_userName = str;}
void		Client::setRealName(const std::string& str) {_realName = str;}
void		Client::setHostName(const std::string& str) {_hostName = str;}
void		Client::setMode(const std::string& str) {_mode = str;};
void		Client::setConnexionPassword(const bool status) {_connexionPassword = status;}
void		Client::setRegistrationDone(const bool status) {_registrationDone = status;}
void		Client::setWelecomeSent(const bool status) {_welcomeSent = status;}
void		Client::setHasAllInfo(const bool status) {_hasAllInfo = status;}
void		Client::setNbInfo(const int count) {_nbInfo = count;}

void	Client::sendMsg(int socket, std::string msg)
{
	if (send(socket, msg.c_str(), msg.length(), 0) < 0)
		perror("SEND FAILED");
	std::cout << "========== send client " << socket << " ==========\n";
	std::cout << msg << "\n\n";
}
