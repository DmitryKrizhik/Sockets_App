#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080

void sig_handler(int sig) {
    std::cout << "Received signal " << sig << ", shutting down server..." << std::endl;
    exit(sig);
}

int main() {

    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        return 1;
    }

    if (fork() != 0) {
        return 0;
    }

    if (setsid() < 0) {
        std::cerr << "Failed to create new session" << std::endl;
        return 1;
    }

    if (chdir("data") < 0) {
        std::cerr << "Failed to change directory" << std::endl;
        return 1;
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    signal(SIGTERM, sig_handler);
    signal(SIGHUP, sig_handler);

    if (listen(server_fd, 3) < 0) {
        std::cerr << "Failed to listen" << std::endl;
        return 1;
    }

    while (true) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            std::cerr << "Failed to accept connection" << std::endl;
            continue;
        }

        char filename[256];
        time_t now = time(NULL);
        strftime(filename, sizeof(filename), "%Y-%m-%d_%H-%M-%S.txt", localtime(&now));

        std::ofstream file(std::string(filename), std::ios::binary);

        if (!file.is_open()) {
            std::cerr << "Failed to create file" << std::endl;
            close(new_socket);
            continue;
        }

        char buffer[1024];
        int bytes_received;
        while ((bytes_received = recv(new_socket, buffer, sizeof(buffer), 0)) > 0) {
            file.write(buffer, bytes_received);
        }

        if (bytes_received == -1) {
            std::cerr << "Failed to receive data" << std::endl;
        }

        file.close();
        close(new_socket);
    }

    close(server_fd);

    return 0;
}