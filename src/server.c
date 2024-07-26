#include "server.h"

List connectionList;

void acceptConnections(int sockfd) {
    connectionList = createList();
    if (!connectionList) {
        printf("Error creating the connection list.\n");
        close(sockfd);
        exit(0);
    }

    int * connfd;
    struct sockaddr_in connaddr;
    socklen_t connsize = sizeof(struct sockaddr_in);

    while (1) {
        connfd = (int *)malloc(sizeof(int));
        if (!connfd) {
            continue;
        }

        *connfd = accept(sockfd, (struct sockaddr *)&connaddr, &connsize);

        if (*connfd == -1) {
            free(connfd);
            continue;
        }
        else {
            addConnection(connectionList, connfd);
            pthread_t threadID;
            pthread_create(&threadID, NULL, handleConnection, connfd);
        }
    }
}

void * handleConnection(void * args) {
    int connfd = *((int *)args);
    int count = 0;
    char * message = "abc";
    while (count < 10) {
        send(connfd, message, strlen(message), MSG_NOSIGNAL);
        if (errno == EPIPE) {
            removeConnection(connectionList, connfd);
            close(connfd);
            break;
        }
        sleep(3);
        count++;
    }
}