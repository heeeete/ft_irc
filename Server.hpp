#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <string>

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <poll.h>
#include <fcntl.h>

class Server
{

	public:

		Server();
		Server( Server const & src );
		~Server();

		Server &		operator=( Server const & rhs );

		int argumentCheck( int argc, char *argv[] );
		void setPollFd(int index, int fd, int events, int revents);
		int setServerSocket();
		int socketLoop();
		void checkSockets(int i);
		void closeFds();

	private:

		int                 serverSocket;
        struct sockaddr_in  serverAddr;
        struct pollfd       pollFDs[100];
        int          		port;
		std::string         pwd;

};

std::ostream &			operator<<( std::ostream & o, Server const & i );

#endif