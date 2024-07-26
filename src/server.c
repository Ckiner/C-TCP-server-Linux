#include "server.h"


void acceptConnections(int sockfd) {
    struct sockaddr_in connaddr;
    socklen_t connsize = sizeof(struct sockaddr_in);

    char * message = "Hello world!";
    int count = 0;
    while (count < 3) {
        int connfd = accept(sockfd, (struct sockaddr *)&connaddr, &connsize);

        if (connfd == -1) {
            continue;
        }
        else {
            handleConnection(connfd);
            count++;
        }
    }
    close(sockfd);
    return NULL;
}

void handleConnection(int connfd) {
    send(connfd, message, strlen(message), 0);
    close(connfd);
}