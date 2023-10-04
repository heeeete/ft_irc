#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Irc.hpp"
#include "Message.hpp"
#include "Server.hpp"

class Client {
	private:
		int				_clientSocket;		//클라이언트와의 통신을 위한 소켓 파일 디스크립터
		std::string		_readBuf;			//서버가 클라이언트로부터 읽은 데이터를 저장하는 버퍼
		std::string		_sendBuf;			//서버가 클라이언트로부터 보낸 데이터를 저장하는 버퍼
		bool			_toDeconnect;		//클라이언트가 연결을 종료했는지?? 여부
		std::string		_nickName;			//클라이언트의 현재 닉네임
		std::string		_oldNickName;		//클라이언트의 이전 닉네임
		std::string		_userName;			//클라이언트의 사용자 이름
		std::string		_realName;			//클라이언트의 실제 이름?
		std::string		_hostName;			//클라이언트 ip 주소
		std::string		_mode;				//클라이언트의 모드를(예: 운영자 모드, 보이스 모드 등).
		bool			_connectionPassword;	//클라이언트가 서버에 연결할 때 사용한 패스워드의 유무
		bool			_registrationDone;	//클라이언트 등록이 완료되었는지의 상태
		bool			_welcomeSent;		//환영 메시지 전송 상태
		bool			_hasAllInfo;		//클라이언트의 모든 필요한 정보가 수집되었는지의 상태
		bool			_correctPwd;
		int				_nbInfo;			//수집된 클라이언트 정보의 개수???
		int				_pollfds_idx;		//pollFDs에 저장된 index
		Server			*_server;

	public:
		Client(int clientSocket, Server *s);
		~Client();

		int				getClientSocket() const;
		std::string		getReadBuf() const;
		std::string		getSendBuf() const;
		bool			getToDeconnect() const;
		std::string		getNickName() const;
		std::string		getOldNickName() const;
		std::string		getUserName() const;
		std::string		getRealName() const;
		std::string		getHostName() const;
		std::string		getMode() const;
		bool			getConnectionPassword() const;
		bool			getRegistrationDone() const;
		bool			getWelecomeSent() const;
		bool			getHasAllInfo() const;
		int				getNbInfo() const;
		Server&			getServer() const;
		int				getPollFDsIdx() const;
		bool			getCorrectPwd() const;

		void			setReadBuf(const std::string buf);
		void			setToDeconnect(const bool status);
		void			setNickName(const std::string& str);
		void			setOldNickName(const std::string& str);
		void			setUserName(const std::string& str);
		void			setRealName(const std::string& str);
		void			setHostName(const std::string& str);
		void			setMode(const std::string& str);
		void			setConnectionPassword(const bool status);
		void			setRegistrationDone(const bool status);
		void			setWelecomeSent(const bool status);
		void			setHasAllInfo(const bool status);
		void			setNbInfo(const int count);
		void			setPollFDsIdx(const int idx);
		void			setCorrectPwd(const bool isCorrect);

		void			processBuffer(const std::string& buf);
		void			sendMsg(int socket, std::string msg);
		void			executeCmd(Message *msg);
};

#endif
