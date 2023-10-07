#ifndef SERVER_HPP
# define SERVER_HPP

# include "Irc.hpp"
# include "Client.hpp"
# include "Message.hpp"
# include "DefineReplies.hpp"

class Server
{
private:
	int _port; // 포트 번호
	std::string _password; // 비밀번호 
	std::string _name; // 서버 이름 
	time_t _startTime; //서버 시작 시간 

	int _serverSocket; //서버 소켓 
	struct pollfd _pollFd[POLLFD_SIZE];

	std::map<int, Client *> _clientList; //소켓fd를 key로 가지는 클라이언트 리스트 
	std::vector<Channel *> _channelList; // 서버가 가진 채널 리스트 

	// 여러 util 함수들 
	void addClient();
	void handleReceivedData(int pollIdx);
	void processBuffer(Client *client);
	void executeCmd(Client *client, Message *msg);
	bool nicknameDupCheck(const std::string nick);
	Client *getClient(const std::string& nickname);

public:
	Server(int port, std::string password);
	~Server();

	void run(); // 서버 시작 
	void registration(Client &client); // 서버에 클라이언트 등록

	// command
	void    nick(Client *client, Message *msg);
	void    user(Client *client, Message *msg);
	void    pass(Client *client, Message *msg);
	void    join(Client *client, Message *msg);
	void    kick();
	void    invite(Client *client, Message* msg);
	void    topic();
	void    mode();
	void    part(Client *client, Message *msg);
	void    quit(Client *client, Message *msg);
	void    privmsg();
	void    notice();
	void    ping(Client *client, Message *msg);
	void	cap(Client *client);

	// 채널 관련 함수
	void createChannel(Client *owner, const std::string& channelName);
	void delChannel(const std::string& channelName);
	Channel *getChannel(const std::string channelName);

	// 예외 클래스 - 예외 생기면 던지기 
	class ServerException : public std::exception 
	{
	private:
		std::string msg;
	public:
		ServerException(std::string msg) : msg(msg) {}
		~ServerException() throw() {}
		const char *what() const throw() { return msg.c_str(); }
	};
};

#endif