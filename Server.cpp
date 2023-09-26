#include "Server.hpp"

Server::Server()
{
}

Server::Server( const Server & src )
{
    *this = src;
}

Server::~Server()
{
}

Server &				Server::operator=( Server const & rhs )
{
	if ( this != &rhs )
	{
		this->serverSocket = rhs.serverSocket;
        this->serverAddr = rhs.serverAddr;
        this->port = rhs.port;
        this->pwd = rhs.pwd;
	}
	return *this;
}

int Server::argumentCheck(int argc, char *argv[])
{
    if (argc != 3) {
        std::cout << "Argument ERROR : ./ircserv [PORT] [PASSWORD]\n";
        return (-1);
    }

    std::string str = argv[1];
    for (int i = 0; i < static_cast<int>(str.length()); i++) {
        if (str[i] < '0' || str[i] > '9') {
            std::cout << "Argument ERROR : Wrong port num\n";
            return (-1);
        }
    }

    unsigned int port_num = std::atoi(argv[1]);
    if (port_num < 0 || port_num > 65535) {
        std::cout << "Argument ERROR : Out range of port num (0~65535)\n";
        return (-1);
    }
	this->port = port_num;
	return (0);
}

void	Server::setPollFd(int index, int fd, int events, int revents)
{
	pollFDs[index].fd = fd;
	pollFDs[index].events = events;
	pollFDs[index].revents = revents;
}

int Server::setServerSocket()
{
    // 1. 서버 소켓 생성
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Server socket creation failed!" << std::endl;
        return -1;
    }

    // 서버 주소 설정
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port); // Port number
    serverAddr.sin_addr.s_addr = INADDR_ANY; // 모든 인터페이스에서 듣기

    // 2. Bind
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Binding failed!" << std::endl;
        close(serverSocket);
        return -1;
    }

    // 3. Listen
    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Listening failed!" << std::endl;
        close(serverSocket);
        return -1;
    }

	std::cout << "InspIRCd Process ID: " << getpid() << std::endl;

	setPollFd(0, serverSocket, POLLIN, 0);

    for (int i = 1; i < 100 ; i++)
        setPollFd(i, -1, 0, 0);

	// SET serverSocket in non block mode
	fcntl(serverSocket, F_SETFL, O_NONBLOCK);

    socketLoop();

	return (0);
}

int Server::socketLoop()
{
    while (1)
    {
        int result = poll(pollFDs, 100, -1);
        if (result > 0) {
            for (int i = 0; i < 100; i++) // 모든 파일 디스크립터를 체크
            {
                if (pollFDs[i].revents & POLLIN) // 이벤트가 발생한 소켓
                {
                   checkSockets(i);
                }
            }
        }
    }

    // 6. Close sockets and finish
	closeFds();

	return (0);
}

void Server::checkSockets(int i)
{
    struct sockaddr_in clientAddr;
    socklen_t addrLen;

    std::string welcomeMsg = ":server 001 <nickname> :Welcome to the Internet Relay Network <nickname>!\r\n";
    std::string yourHostMsg = ":server 002 <nickname> :Your host is <servername>, running version <version>\r\n";
    std::string createdMsg = ":server 003 <nickname> :This server was created <date>\r\n";
    std::string myInfoMsg = ":server 004 <nickname> :<servername> <version> <available user modes> <available channel modes>\r\n";

    // 위의 문자열에서 <nickname>, <servername>, <version>, <date>, <available user modes>, <available channel modes> 등은 적절한 값으로 대체해야 합니다.

	if (i == 0) // 서버 소켓
    {
        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrLen);
        // 새로운 클라이언트 소켓을 pollFDs 배열에 추가
        for (int j = 1; j < 100; j++)
        {
            if (pollFDs[j].fd == -1)
            {
                setPollFd(j, clientSocket, POLLIN, 0);
                fcntl(clientSocket, F_SETFL, O_NONBLOCK);
            	std::cout << "connection successful\n";
                send(clientSocket, welcomeMsg.c_str(), welcomeMsg.length(), 0);
                send(clientSocket, yourHostMsg.c_str(), yourHostMsg.length(), 0);
                send(clientSocket, createdMsg.c_str(), createdMsg.length(), 0);
                send(clientSocket, myInfoMsg.c_str(), myInfoMsg.length(), 0);
                break;
            }
        }
    }
    else // 클라이언트 소켓
    {
        std::cout << "클라이언트 이벤트 발생!!\n";
        char buffer[1024];
        ssize_t bytes_received = recv(pollFDs[i].fd, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0)
        {
            // 연결 종료 혹은 오류 발생
            close(pollFDs[i].fd);
            pollFDs[i].fd = -1;
        }
    	else
        {
            buffer[bytes_received] = '\0'; // 문자열 종료 문자 추가
            std::cout << "Received: " << buffer << std::endl;
        }
    }
}

void Server::closeFds()
{
	close(serverSocket);
	// TODO: clients fd 삭제
}