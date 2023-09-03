#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

class Server {
public:
    void run() {
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(8080);

        bind(server_fd, (struct sockaddr *)&address, sizeof(address));
        listen(server_fd, 3);

        int addrlen = sizeof(address);
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

        char buffer[1024] = {0};
        read(new_socket, buffer, 1024);
        std::cout << "Received: " << buffer << std::endl;

        const char *response = "Hello from server";
        send(new_socket, response, strlen(response), 0);
        std::cout << "Response sent" << std::endl;

        close(new_socket);
        close(server_fd);
    }

private:
    int server_fd, new_socket;
    struct sockaddr_in address;
};

int main() {
    Server server;
    server.run();
    return 0;
}
