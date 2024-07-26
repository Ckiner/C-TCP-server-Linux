#include "signalhandler.h"

void cleanup(int signalNum) {
    printf("\nShutting down\n");
    close(sockfd);
    exit(0);
}

int signalHandlerSetup() {
    struct sigaction sa;
    sa.sa_handler = cleanup;  // Call cleanup when signal is recieved
    sigemptyset(&sa.sa_mask);  // Allow all signals
    return sigaction(SIGINT, &sa, NULL); // utilize sa when keyboard interrupt occurs
}