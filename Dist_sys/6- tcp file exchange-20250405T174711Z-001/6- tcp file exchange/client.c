#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(int argc, char const* argv[]) {
    int client_fd, status;
    struct sockaddr_in serv_addr;
    FILE *file;
    char buffer[BUFFER_SIZE] = { 0 };

    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed with error %d\n", WSAGetLastError());
        return -1;
    }

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error\n");
        WSACleanup();
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (serv_addr.sin_addr.s_addr == INADDR_NONE) {
        printf("Invalid address\n");
        closesocket(client_fd);
        WSACleanup();
        return -1;
    }

    if ((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
        printf("Connection Failed\n");
        closesocket(client_fd);
        WSACleanup();
        return -1;
    }

    file = fopen("text_file.txt", "rb");
    if (file == NULL) {
        printf("File not found\n");
        closesocket(client_fd);
        WSACleanup();
        return -1;
    }

    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        if (send(client_fd, buffer, bytes_read, 0) == -1) {
            perror("Send failed");
            fclose(file);
            closesocket(client_fd);
            WSACleanup();
            return -1;
        }
    }

    printf("File sent successfully.\n");

    fclose(file);
    closesocket(client_fd);
    WSACleanup();

    return 0;
}
