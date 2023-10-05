#ifndef SERVER_HPP
# define SERVER_HPP

#include "Irc.hpp"

class Client;

class Server
{

	public:

		Server();
		Server( Server const & src );
		~Server();

		Server &		operator=( Server const & rhs );

		int 	argumentCheck( int argc, char *argv[] );
		void 	setPollFd(int index, int fd, int events, int revents);
		int 	setServerSocket();
		int 	socketLoop();
		void 	checkSockets(int i);
		void 	closeFds();
		bool	nickNameDupCheck(const std::string& nick);

		// Getters
		int				getServerSocket() const;
		int				getPort() const;
		std::string		getPassword() const;
		std::string		getName() const;
		time_t const*	getStartTime() const;
		struct pollfd*	getPollFDs();
		std::map<int, Client *>& getClientsList();

	private:

		int                 _serverSocket;
        struct sockaddr_in  _serverAddr;
        struct pollfd       _pollFDs[100];
        int          		_port;
		std::string         _pwd;
		std::string			_name;
		time_t				_startTime;
		std::map<int , Client *>	_clientsList;
};

#endif
