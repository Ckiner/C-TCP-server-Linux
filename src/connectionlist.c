#include <stdio.h>
#include <stdlib.h>
#include "connectionlist.h"

List createList() {
    // Returns a linked list
    List new = (List)malloc(sizeof(struct list));
    if (!new) {
        return NULL;
    }

    new->next = NULL;
    return new;
}

int isEmpty(List list) {
    if (!list) {
        return -1;
    }

    if (list->next){
        return 0;
    }

    return 1;
}

void addConnection(List list, int * connfd) {
    // Inserts a new socket descriptor into the list
    List new = createList();
    if (new) {
        new->connfd = connfd;
        new->next = list->next;
        list->next = new;
    }
}

int popConnection(List list) {
    // Removes the first value from the linked list
    if (!list || isEmpty(list)) {
        return -1;
    }

    List first = list->next;
    list->next = first->next;
    int val = *(first->connfd);
    free(first->connfd);
    free(first);
    return val;
}
