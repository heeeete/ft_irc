#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

int argument_check(char *argv[]){
	return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Argument ERROR : ./ircserv [PORT] [PASSWORD]\n";
        return -1;
    }
    argument_check(argv);
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len;

    // 1. 소켓 생성
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Server socket creation failed!" << std::endl;
        return -1;
    }

    // 서버 주소 설정
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9000); // Port number
    server_addr.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces

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

    // 4. Accept
    addr_len = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_len);
    if (client_socket == -1) {
        std::cerr << "Accept failed!" << std::endl;
        close(server_socket);
        return -1;
    }

    std::cout << "Client connected!" << std::endl;

    // 5. Send message to client
    const char* msg = "Hello, Client!";
    send(client_socket, msg, strlen(msg), 0);

    // 6. Close sockets and finish
    close(client_socket);
    close(server_socket);

    return 0;
}
