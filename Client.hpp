#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>

class Client {
	private:
		int				_clientSocket;
		std::string		_readBuf;
		std::string		_sendBuf;
		bool			_toDeconnect;
		std::string		_nickName;
		std::string		_oldNickName;
		std::string		_userName;
		std::string		_realName;
		std::string		_mode;
		bool			_connexionPassword;
		bool			_registrationDone;
		bool			_welcomeSent;
		bool			_hasAllInfo;
		int				_nbInfo;

	public:
		Client(int clientSocket);
		~Client();

		int	getClientSocket();
		std::string	getReadBuf() const;
		std::string&	getSendBuf() const;
		bool			getToDeconnect() const;
		std::string&	getNickName() const;
		std::string&	getOldNickName() const;
		std::string&	getUserName() const;
		std::string&	getRealName() const;
		std::string&	getMode() const;
		bool			getConnexionPassword() const;
		bool			getRegistrationDone() const;
		bool			getWelecomeSent() const;
		bool			getHasAllInfo() const;
		int				getNbInfo() const;
};

#endif
