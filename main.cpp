#include "Server.hpp"

// argument가 유효한지 확인하는 함수 
static bool isArgumentValid(int argc, char *argv[])
{
	if (argc != 3) {
        std::cout << "Argument ERROR : ./ircserv [PORT] [PASSWORD]\n";
        return (false);
    }

	// [PORT]가 숫자만으로 구성되어 있는지 확인 
	for (int i = 0; i < strlen(argv[1]); i++)
	{
		if (!isdigit(argv[1][i]))
		{
			std::cout << "Argument ERROR : Wrong port num\n";
			return (false);
		}
	}

	// [PORT]의 범위 확인 
	unsigned int port = atoi(argv[1]);
	if (port < 0 || port > 65535) {
        std::cout << "Argument ERROR : Out range of port num (0~65535)\n";
        return (false);
    }
	return (true);
}

int main(int argc, char *argv[])
{
	if (!isArgumentValid(argc, argv))
		return (EXIT_FAILURE);

	int port = atoi(argv[1]);
	std::string password = argv[2];

	try 
	{
		Server server(port, password);
		server.run();
	}
	catch (Server::ServerException& e) 
	{
		std::cerr << e.what() << std::endl;
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}