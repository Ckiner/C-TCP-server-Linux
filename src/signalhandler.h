#ifndef _SIGNALHANDLER_H
#define _SIGNALHANDLER_H

#include <signal.h>
#include "server.h"

extern int sockfd;
extern List connectionList;

void cleanup(int);
int signalHandlerSetup();

#endif