#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class Client {
public:
    Client() {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(8080);
    }

    bool connectToServer() {
        inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
        return (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) >= 0);
    }

    int getSock() {
        return sock;
    }

private:
    int sock;
    struct sockaddr_in serv_addr;
};

int main() {
    Client client;

    if (!client.connectToServer()) {
        std::cerr << "Connection failed.\n";
        return -1;
    }

    send(client.getSock(), "Hello from client", 17, 0);

    char buffer[1024] = {0};
    read(client.getSock(), buffer, 1024);
    std::cout << "Message received: " << buffer << std::endl;

    return 0;
}
