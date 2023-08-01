#include "../headers/Car.h"
#include "../headers/Vehicle.h"
#include <iostream>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <thread> // For multithreading support


#pragma comment(lib, "ws2_32.lib")

// Function to handle individual client connections
void HandleClient(SOCKET clientSocket) {
    char buffer[1024];
    int bytesReceived;

    while (true) {
        // Receive data from the client
        bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            // If no data received or the client disconnected, break out of the loop
            break;
        }

        // Null-terminate the received data and print it
        buffer[bytesReceived] = '\0';
        std::cout << "Received message: " << buffer << std::endl;
    }

    // Close the client socket when the loop ends
    closesocket(clientSocket);
}

int main() {
    // Initialize WinSock
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return 1;
    }

    // Create a socket for the server
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Set up server address information
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // Bind to localhost
    serverAddress.sin_port = htons(8080); // Use any available port number

    // Bind the server socket to the specified address and port
    result = bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress));
    if (result == SOCKET_ERROR) {
        std::cerr << "Binding failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Start listening for incoming client connections
    result = listen(serverSocket, SOMAXCONN);
    if (result == SOCKET_ERROR) {
        std::cerr << "Listening failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server listening on port 8080..." << std::endl;

    // Accept and handle incoming client connections in an infinite loop
    SOCKET clientSocket;
    sockaddr_in clientAddress;
    int clientAddressSize = sizeof(clientAddress);

    while (true) {
        // Accept a new client connection
        clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddress), &clientAddressSize);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Accepting connection failed: " << WSAGetLastError() << std::endl;
            continue;
        }

        // Print client information and handle the client in a separate thread
        std::cout << "Accepted connection from " << inet_ntoa(clientAddress.sin_addr)
            << ":" << ntohs(clientAddress.sin_port) << std::endl;

        std::thread clientHandler(HandleClient, clientSocket);
        clientHandler.detach(); // Detach the thread to allow it to run independently
    }

    // Close the server socket and clean up WinSock resources
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
