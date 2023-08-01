/*#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int port = 12345;
    const char* serverIP = "127.0.0.1"; // Loopback IP address for localhost

    // Create socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // Set up server address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, serverIP, &(serverAddr.sin_addr));

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        return 1;
    }

    char message[] = "Hello, server!";
    if (send(clientSocket, message, sizeof(message), 0) == -1) {
        std::cerr << "Error sending data" << std::endl;
    }

    char buffer[1024] = { 0 };
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead == -1) {
        std::cerr << "Error receiving data" << std::endl;
    }
    else {
        std::cout << "Received from server: " << buffer << std::endl;
    }

    close(clientSocket);

    return 0;
}
*/