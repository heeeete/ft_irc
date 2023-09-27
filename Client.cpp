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

void		Client::setNickName(const std::string& nickName) {_nickName = nickName;}
