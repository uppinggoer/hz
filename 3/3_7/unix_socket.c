#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/un.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

 // rm /tmp/sock.unix

int main(int argc, char* argv[]) {
    struct sockaddr_un address;
    address.sun_family=AF_UNIX;
    strcpy(address.sun_path, "/tmp/sock.unix");

    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
#ifdef SERVER
    bind(sock, (struct sockaddr *)&address, sizeof(address));
    listen(sock, 100);

    struct sockaddr_un client;
    int client_addrlength = sizeof(client);
    int connfd = accept(sock, (struct sockaddr*)&client, &client_addrlength);
   
    char buffer[101];
    read(connfd, buffer, 100);
    printf("server_get_data: %s\n", buffer);
    write(connfd, "ok", 2);
    close(connfd);
#elif CLIENT
    connect(sock, (struct sockaddr*)&address, sizeof(address));
    write(sock, "abc", 3);
    char buffer[101];
    read(sock, buffer, 100);
    printf( "client_get_data: %s\n", buffer);
#endif

    close(sock);
    return 0;
}


