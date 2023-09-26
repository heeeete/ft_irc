#include "Server.hpp"

int main(int argc, char* argv[]) {
    Server server;

    if (server.argumentCheck(argc, argv) == -1)
        return (-1);
    if (server.setServerSocket() == -1)
        return (-1);
    return 0;
}
