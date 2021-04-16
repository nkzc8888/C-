#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    int listen_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in server_addr;
    bzero((char*)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(6240);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int r = bind(listen_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(r == -1) return -1;

    printf("bind complete, port number: %d\n", ntohs(server_addr.sin_port));
    printf("------------------------------------------\n");

    r = listen(listen_fd, 10);
    if(r == -1) return -1;

    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(struct sockaddr_in));
    socklen_t client_addr_len = sizeof(client_addr);
    int accept_fd = 0;
    while(1) 
    {
    accept_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &client_addr_len);

    char buffer_recv[1024] = {0};
    read(accept_fd, buffer_recv, sizeof(buffer_recv));
    printf("the request send from client is: %s \n", buffer_recv);

    const char *buffer_send = "HTTP/1.1 200 OK ";
    send(accept_fd, buffer_send, strlen(buffer_send), 0);

    send(accept_fd, inet_ntoa(client_addr.sin_addr), 256, 0);
    close(accept_fd);
    }
    return 0;
}