#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>

#define PORT 8080

int main(int argc, char const* argv[]) {
    int status, valread, client_fd;
    struct sockaddr_in serv_addr;
    char* hello = "Hello from client";
    char buffer[1024] = { 0 };

    WSADATA wsaData;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed with error %d\n", WSAGetLastError());
        return -1;
    }

    // Create socket
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        WSACleanup(); // Cleanup Winsock
        return -1;
    }

    // Setup server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Use inet_addr (Windows-specific) for address conversion
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (serv_addr.sin_addr.s_addr == INADDR_NONE) {
        printf("\nInvalid address/Address not supported \n");
        closesocket(client_fd); // Close socket before cleanup
        WSACleanup();
        return -1;
    }

    // Connect to the server
    if ((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
        printf("\nConnection Failed \n");
        closesocket(client_fd); // Close socket before cleanup
        WSACleanup();
        return -1;
    }

    // Send message to the server
    send(client_fd, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    // Read response from the server
    valread = recv(client_fd, buffer, 1024, 0); // Using recv() instead of read() on Windows
    if (valread > 0) {
        buffer[valread] = '\0'; // Null-terminate the string
        printf("Server: %s\n", buffer);
    } else {
        printf("No response or connection closed by server.\n");
    }

    // Close the socket and clean up Winsock
    closesocket(client_fd);
    WSACleanup();

    return 0;
}
