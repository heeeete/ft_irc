#include "Client.hpp"

Client::Client(int clientSocket) : _clientSocket(clientSocket) {}
Client::~Client(){}

std::string	Client::getReadBuf() const {
	return _readBuf;
}
std::string&	Client::getSendBuf() const {
	return _sendBuf;
}
bool			Client::getToDeconnect() const
std::string&	Client::getNickName() const
std::string&	Client::getOldNickName() const
std::string&	Client::getUserName() const
std::string&	Client::getRealName() const
std::string&	Client::getMode() const
bool			Client::getConnexionPassword() const
bool			Client::getRegistrationDone() const
bool			Client::getWelecomeSent() const
bool			Client::getHasAllInfo() const
int				Client::getNbInfo() const
