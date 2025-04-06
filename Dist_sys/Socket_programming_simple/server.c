#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8080

int main(int argc, char const* argv[]) {
    int server_fd, new_socket;
    size_t valread;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char buffer[1024] = { 0 };
    char* hello = "Hello from server";

    WSADATA wsaData;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed with error %d\n", WSAGetLastError());
        return -1;
    }

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        WSACleanup(); // Clean up Winsock before exiting
        return -1;
    }

    // Setting socket options (SO_REUSEADDR)
    int reuse_addr_opt = 1; // Enable SO_REUSEADDR
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (const char *)&reuse_addr_opt, sizeof(reuse_addr_opt)) < 0) {
        perror("setsockopt");
        closesocket(server_fd); // Close socket before cleanup
        WSACleanup();
        return -1;
    }

    // Setting up the server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Binding the socket
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        closesocket(server_fd); // Close socket before cleanup
        WSACleanup();
        return -1;
    }

    // Listening for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        closesocket(server_fd); // Close socket before cleanup
        WSACleanup();
        return -1;
    }

    // Accepting a connection
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) < 0) {
        perror("accept");
        closesocket(server_fd); // Close socket before cleanup
        WSACleanup();
        return -1;
    }

    // Reading from the client
    valread = recv(new_socket, buffer, 1024, 0); // Use recv() instead of read() on Windows
    if (valread > 0) {
        buffer[valread] = '\0'; // Null-terminate the string
        printf("Received: %s\n", buffer);
    }

    // Send a response to the client
    send(new_socket, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    // Closing the sockets
    closesocket(new_socket); // Close the client socket
    closesocket(server_fd);  // Close the server socket

    // Clean up Winsock
    WSACleanup();

    return 0;
}
