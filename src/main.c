#include <stdio.h>
#include <stdlib.h>
#include "server.h"


int main(int argc, char * argv[]) {
    if (argc < 4) {
        printf("Please specify all arguments.\n ./{filename} {address} {port} {maximum backlog}\n");
        return 1;
    }
    if (atoi(argv[3]) < 0) {
        printf("Invalid backlog argument. Must be a positive integer.\n");
        return 1;
    }
    const int MAX_BACKLOG = atoi(argv[3]);  // The amount of connections that can be pending acceptance.
    const short FAMILY = AF_INET;
    const char * ADDRESS = argv[1];

    if (atoi(argv[2]) < 0) {
        printf("Invalid port argument. Must be a positive integer.\n");
        return 1;
    }
    const unsigned short PORT = (unsigned short)atoi(argv[2]);

    int sockfd = socket(FAMILY, SOCK_STREAM, 0);

    if (sockfd == -1) {
        printf("Error creating socket.\n");
        return 1;
    }

    struct sockaddr_in saddr;
    saddr.sin_family = FAMILY;  // e.g. AF_INET
    saddr.sin_port = htons(PORT); // Transforms port to unsigned short in network byte order
    inet_aton(ADDRESS, &saddr.sin_addr);  // Transform ascii ip to an unsigned long in network byte order


    // Bind the primary socket to {ADDRESS}:{PORT} as described above
    if (bind(sockfd, (struct sockaddr *)(&saddr), sizeof(struct sockaddr_in)) == -1) {
        printf("Error binding the socket.\n");
        return 1;
    }
    // Set the socket to listening mode
    if (listen(sockfd, MAX_BACKLOG) == -1) {
        printf("Error setting the socket to listening mode.\n");
        return 1;
    }

    acceptConnections(sockfd);

    return 0;
}