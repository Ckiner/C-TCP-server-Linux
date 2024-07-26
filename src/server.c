#include "server.h"

void acceptConnections(int sockfd) {
    struct sockaddr_in connaddr;
    socklen_t connsize = sizeof(struct sockaddr_in);

    while (1) {
        int connfd = accept(sockfd, (struct sockaddr *)&connaddr, &connsize);

        if (connfd == -1) {
            continue;
        }
        else {
            pthread_t threadID;
            pthread_create(&threadID, NULL, handleConnection, &connfd);
        }
    }
}

void * handleConnection(void * args) {
    int connfd = *((int *)args);
    char * message = "Hello world!";
    send(connfd, message, strlen(message), 0);
    close(connfd);
}