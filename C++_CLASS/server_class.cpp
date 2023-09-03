#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

class Server {
public:
    Server() {
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(8080);
    }

    bool bindSocket() {
        return (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) >= 0);
    }

    bool listenSocket() {
        return (listen(server_fd, 3) >= 0);
    }

    int acceptClient() {
        int addrlen = sizeof(address);
        return accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
    }

private:
    int server_fd;
    struct sockaddr_in address;
};

int main() {
    Server server;

    if (!server.bindSocket() || !server.listenSocket()) {
        std::cerr << "Socket operation failed.\n";
        return -1;
    }

    int new_socket = server.acceptClient();
    if (new_socket < 0) {
        std::cerr << "Accept failed.\n";
        return -1;
    }

    char buffer[1024] = {0};
    read(new_socket, buffer, 1024);
    std::cout << "Message received: " << buffer << std::endl;

    send(new_socket, "Hello from server", 17, 0);
    return 0;
}
