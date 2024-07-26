#ifndef _CONNECTIONLIST_H
#define _CONNECTIONLIST_H

typedef struct list * List;

struct list {
    List next;
    int * connfd;
};

List createList();
int isEmpty(List);
void addConnection(List, int *);
int popConnection(List);

#endif;
