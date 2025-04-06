#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(int argc, char const* argv[]) {
    int server_fd, new_socket;
    ssize_t valread;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = { 0 };
    FILE *file;

    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed with error %d\n", WSAGetLastError());
        return -1;
    }

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        WSACleanup();
        return -1;
    }

    int reuse_addr_opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse_addr_opt, sizeof(reuse_addr_opt)) < 0) {
        perror("setsockopt");
        closesocket(server_fd);
        WSACleanup();
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        closesocket(server_fd);
        WSACleanup();
        return -1;
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        closesocket(server_fd);
        WSACleanup();
        return -1;
    }

    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) < 0) {
        perror("accept");
        closesocket(server_fd);
        WSACleanup();
        return -1;
    }

    printf("Client connected.\n");

    file = fopen("received_file.txt", "wb");
    if (file == NULL) {
        perror("File opening failed");
        closesocket(new_socket);
        closesocket(server_fd);
        WSACleanup();
        return -1;
    }

    printf("Receiving data...\n");

    while ((valread = recv(new_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        fwrite(buffer, 1, valread, file);
        buffer[valread] = '\0';  // Null-terminate for safe printing
        printf("Client sent: %s", buffer);
    }

    if (valread == 0) {
        printf("\nFile received successfully.\n");
    } else if (valread == -1) {
        perror("Receive failed");
    }

    fclose(file);
    closesocket(new_socket);
    closesocket(server_fd);
    WSACleanup();

    return 0;
}
