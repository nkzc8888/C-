#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

const char* server = "127.0.0.1";
const int BUF_SIZE = 256;

int main() {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in client_addr;
    bzero((char*)&client_addr, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(80);
    client_addr.sin_addr.s_addr = inet_addr(server);

    bind(client_fd, (struct sockaddr*)&client_fd, sizeof(client_fd));

    struct sockaddr_in server_addr;
    bzero((char*)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(6240);
    inet_aton(server, &server_addr.sin_addr);

    connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    char buffer_send[100] = {0};
    printf("please input the filename you want:");
    scanf("%s", buffer_send);

    send(client_fd, buffer_send, strlen(buffer_send), 0);
    printf("message successfully send\n");
    printf("------------------------------------------\n");

    printf("receive message from server:\n");
    char _message[BUF_SIZE] = {0};
    recv(client_fd, _message, BUF_SIZE, 0);
    printf("the message answered from server is: %s\n", _message);

    char _IP[BUF_SIZE] = {0};
    recv(client_fd, _IP, BUF_SIZE, 0);
    printf("the IP of Client is: %s\n", _IP);

    return 0;
}