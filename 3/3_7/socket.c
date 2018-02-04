#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
 
extern int errno;

int main(int argc, char* argv[]) {
    char* ip = "127.0.0.1";

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(8000);
 
    int sock = socket(PF_INET, SOCK_STREAM, 0);
#ifdef SERVER
    bind(sock, (struct sockaddr*)&address, sizeof(address));
    listen(sock, 100);

    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof(client);
    int connfd = accept(sock, (struct sockaddr*)&client, &client_addrlength);
    char buffer[101];
    recv(connfd, buffer, 100, 0);
    printf("server_get_data: %s\n", buffer);
    send(connfd, "ok", 2, 0);
    close(connfd);
#elif CLIENT
    connect(sock, (struct sockaddr*)&address, sizeof(address));
    send(sock, "abc", 3, 0);
    char buffer[101];
    recv(sock, buffer, 100, 0);
    printf( "client_get_data: %s\n", buffer);
#endif

    close(sock);
    return 0;
}
