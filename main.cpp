#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <poll.h>


int argument_check(int argc, char *argv[])
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

	return (0);
}

int main(int argc, char* argv[]) {
    if (argument_check(argc, argv) == -1)
        return (-1);

    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len;

    // 1. 서버 소켓 생성
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Server socket creation failed!" << std::endl;
        return -1;
    }

    // 서버 주소 설정
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1])); // Port number
    server_addr.sin_addr.s_addr = INADDR_ANY; // 모든 인터페이스에서 듣기

    // 2. Bind
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Binding failed!" << std::endl;
        close(server_socket);
        return -1;
    }

    // 3. Listen
    if (listen(server_socket, 5) == -1) {
        std::cerr << "Listening failed!" << std::endl;
        close(server_socket);
        return -1;
    }

	std::cout << "InspIRCd Process ID: " << getpid() << std::endl;

    struct pollfd pollFDs[100];
    pollFDs[0].fd = server_socket;
    pollFDs[0].events = POLLIN; // 읽도록 만든다.
    pollFDs[0].revents = 0; // 처음에는 0으로 초기화 한다(아직 아무 일도 일어나지 않았으니)

    for (int i = 1; i < 100 ; i++)
        pollFDs[i].fd = -1;


    std::string welcomeMsg = ":server 001 <nickname> :Welcome to the Internet Relay Network <nickname>!\r\n";
    std::string yourHostMsg = ":server 002 <nickname> :Your host is <servername>, running version <version>\r\n";
    std::string createdMsg = ":server 003 <nickname> :This server was created <date>\r\n";
    std::string myInfoMsg = ":server 004 <nickname> <servername> <version> <available user modes> <available channel modes>\r\n";

    // 위의 문자열에서 <nickname>, <servername>, <version>, <date>, <available user modes>, <available channel modes> 등은 적절한 값으로 대체해야 합니다.


    while (1)
    {
        int result = poll(pollFDs, 100, -1);
        if (result > 0) {
            for (int i = 0; i < 100; i++) // 모든 파일 디스크립터를 체크
            {
                if (pollFDs[i].revents & POLLIN) // 이벤트가 발생한 소켓
                {
                    if (i == 0) // 서버 소켓
                    {
                        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
                        // 새로운 클라이언트 소켓을 pollFDs 배열에 추가
                        for (int j = 1; j < 100; j++)
                        {
                            if (pollFDs[j].fd == -1)
                            {
                                pollFDs[j].fd = client_socket;
                                pollFDs[j].events = POLLIN;
                                std::cout << "connection successful\n";
                                send(client_socket, welcomeMsg.c_str(), welcomeMsg.length(), 0);
                                send(client_socket, yourHostMsg.c_str(), yourHostMsg.length(), 0);
                                send(client_socket, createdMsg.c_str(), createdMsg.length(), 0);
                                send(client_socket, myInfoMsg.c_str(), myInfoMsg.length(), 0);
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
            }
        }
    }


    // 6. Close sockets and finish
    close(client_socket);
    close(server_socket);

    return 0;
}
