#include "Server.hpp"
#include "Client.hpp"
#include "Irc.hpp"

Server::Server(): _name("PPL ft_irc")
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
		this->_serverSocket = rhs._serverSocket;
        this->_serverAddr = rhs._serverAddr;
        this->_port = rhs._port;
        this->_pwd = rhs._pwd;
        this->_name = rhs._name;
        this->_startTime = rhs._startTime;
	}
	return *this;
}

int				Server::getServerSocket() const {return _serverSocket;}
int				Server::getPort() const {return _port;}
std::string		Server::getPassword() const {return _pwd;}
std::string     Server::getName() const {return _name;}
time_t const*	Server::getStartTime() const { return &_startTime;}
std::map<int, Client *>& Server::getClientsList() {return _clientsList;}
struct pollfd*	Server::getPollFDs() {return _pollFDs;}
Channel*		Server::getChannel(const std::string channelName) {
    std::vector<Channel *>::iterator isbegin = _channelList.begin();

    while (isbegin != _channelList.end()) {
        if ((*isbegin)->getName() == channelName)
            return *isbegin;
        isbegin++;
    }
    return NULL;
}

bool	Server::nickNameDupCheck(const std::string& nick){
    std::map<int, Client *>::iterator isbegin = _clientsList.begin();

    while (isbegin != _clientsList.end()){
        if (isbegin->second->getNickName() == nick)
            return true;
        isbegin++;
    }
    return false;
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
	this->_port = port_num;
    this->_pwd = argv[2];
	return (0);
}

void	Server::setPollFd(int index, int fd, int events, int revents)
{
	_pollFDs[index].fd = fd;
	_pollFDs[index].events = events;
	_pollFDs[index].revents = revents;
}

int Server::setServerSocket()
{
    time(&_startTime);

    // 1. 서버 소켓 생성
    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverSocket == -1) {
        std::cerr << "Server socket creation failed!" << std::endl;
        return -1;
    }

    // 서버 주소 설정
    _serverAddr.sin_family = AF_INET;
    _serverAddr.sin_port = htons(_port); // Port number
    _serverAddr.sin_addr.s_addr = INADDR_ANY; // 모든 인터페이스에서 듣기

    // 2. Bind
    if (bind(_serverSocket, (struct sockaddr*)&_serverAddr, sizeof(_serverAddr)) == -1) {
        std::cerr << "Binding failed!" << std::endl;
        close(_serverSocket);
        return -1;
    }

    // 3. Listen
    if (listen(_serverSocket, 5) == -1) {
        std::cerr << "Listening failed!" << std::endl;
        close(_serverSocket);
        return -1;
    }

	std::cout << "Process ID: " << getpid() << std::endl;

	setPollFd(0, _serverSocket, POLLIN, 0);

    for (int i = 1; i < 100 ; i++)
        setPollFd(i, -1, 0, 0);

	// SET serverSocket in non block mode
	fcntl(_serverSocket, F_SETFL, O_NONBLOCK);

    socketLoop();

	return (0);
}

int Server::socketLoop()
{
    while (1)
    {
        int result = poll(_pollFDs, 100, -1);
        if (result > 0) {
            for (int i = 0; i < 100; i++) // 모든 파일 디스크립터를 체크
            {
                if (_pollFDs[i].revents & POLLIN) // 이벤트가 발생한 소켓
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

	if (i == 0) // 서버 소켓
    {
        int clientSocket = accept(_serverSocket, (struct sockaddr *)&clientAddr, &addrLen);
        std::cout << "클라이언트 SOCKET FD: " << clientSocket << "\n";
        // 새로운 클라이언트 소켓을 pollFDs 배열에 추가
        for (int j = 1; j < 100; j++)
        {
            if (_pollFDs[j].fd == -1)
            {
                Client *client = new Client(clientSocket, this); // 새로운 클라이언트 생성
                _clientsList.insert(std::pair<int , Client *>(client->getClientSocket(), client));
                setPollFd(j, clientSocket, POLLIN, 0);
				client->setPollFDsIdx(j);
                fcntl(clientSocket, F_SETFL, O_NONBLOCK);
            	std::cout << "connection successful\n";
                break;
            }
        }
    }
    else // 클라이언트 소켓
    {
        std::cout << "클라이언트 이벤트 발생!!\n";
        char buffer[1024];
        ssize_t bytes_received = recv(_pollFDs[i].fd, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0)
        {
            // 연결 종료 혹은 오류 발생
			// _clientsList에서도 빼주기
            close(_pollFDs[i].fd);
            _pollFDs[i].fd = -1;
        }
    	else
        {
            buffer[bytes_received] = '\0'; // 문자열 종료 문자 추가
            _clientsList[_pollFDs[i].fd]->setReadBuf(buffer);
        }
    }
}

void Server::closeFds()
{
	close(_serverSocket);
	// TODO: clients fd 삭제
}

void	Server::createChannel(Client *owner, const std::string& channelName) {
    std::vector<Channel *>::iterator isbegin = _channelList.begin();

    while (isbegin != _channelList.end()) {
        if ((*isbegin)->getName() == channelName) {
            std::cout << channelName << " 채널이 이미 존재합니다." << std::endl;
            return;
        }
        isbegin++;
    }
    try
    {
        Channel* newChannel = new Channel(owner, channelName);
        _channelList.push_back(newChannel);
        std::cout << channelName << " 채널이 만들어졌습니다." << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return ;
    }

}

void	Server::addClientToChannel(Client* client, Channel* channel) {
    channel->addClient(client);
}
