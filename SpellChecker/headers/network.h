#ifndef NETWORK_H
#define NETWORK_H
#include "csapp.h"

/**
 * Establishes a connection to a client through a socket
 * @returns fd of client
 */
int openClientFD(char* hostName, int port);

#endif