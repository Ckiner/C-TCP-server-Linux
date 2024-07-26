#include "signalhandler.h"

void cleanup(int signalNum) {
    printf("\nShutting down\n");
    close(sockfd);
    int connfd;

    while (!isEmpty(connectionList)) {
        connfd = popConnection(connectionList);
        if (connfd != -1) {
            close(connfd);
        }
    }
    printf("Shutdown complete\n");
    exit(0);
}

int signalHandlerSetup() {
    struct sigaction sa;
    sa.sa_handler = cleanup;  // Call cleanup when signal is recieved
    sigemptyset(&sa.sa_mask);  // Allow all signals
    sigaction(SIGPIPE, &sa, NULL);
    return sigaction(SIGINT, &sa, NULL); // utilize sa when keyboard interrupt occurs
}