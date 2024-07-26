#include "server.h"

void acceptConnections(int sockfd) {
    struct sockaddr_in connaddr;
    socklen_t connsize = sizeof(struct sockaddr_in);

    int count = 0;
    while (count < 3) {
        int connfd = accept(sockfd, (struct sockaddr *)&connaddr, &connsize);

        if (connfd == -1) {
            continue;
        }
        else {
            pthread_t threadID;
            pthread_create(&threadID, NULL, handleConnection, &connfd);
            count++;
        }
    }
    close(sockfd);
    return NULL;
}

void * handleConnection(void * args) {
    int connfd = *((int *)args);
    char * message = "Hello world!";
    send(connfd, message, strlen(message), 0);
    close(connfd);
}