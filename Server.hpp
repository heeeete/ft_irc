#ifndef SERVER_HPP
# define SERVER_HPP

#include "Irc.hpp"

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

		// Getters
		int				getServerSocket() const;
		int				getPort() const;
		std::string		getPassword() const;

	private:

		int                 _serverSocket;
        struct sockaddr_in  _serverAddr;
        struct pollfd       _pollFDs[100];
        int          		_port;
		std::string         _pwd;

};

#endif
