#include "../headers/network.h"

int doUserInput(int fd, rio_t *rio);

int main(int argc, char **argv) {
  int listenFD, clientFD, port, clientLength;
  struct hostent *hp;
  struct sockaddr_in clientAddress;
  rio_t rio;

  if (argc != 2) {  // Only receive the port ad an arg
    fprintf(stderr, "Usage: %s <port>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  port = atoi(argv[1]);

  fprintf(stdout, "Server started at: %s\n", argv[1]);

   listenFD = open_listenfd(port);

  while (1) {
    clientLength = sizeof(clientAddress);
    clientFD = accept(listenFD, (SA *)&clientAddress, &clientLength);

    hp = gethostbyaddr((const char *) &clientAddress.sin_addr.s_addr, sizeof(clientAddress.sin_addr.s_addr), AF_INET);

    dprintf(clientFD, "Connection Success!\n");
    doUserInput(clientFD, &rio);

    close(clientFD);
  }
}

int doUserInput(int fd, rio_t *rio) {
  size_t n;
  char buffer[MAXLINE];

  rio_readinitb(&rio, fd);

  while((n = rio_readlineb(&rio, buffer, MAXLINE)) != 0) {
    rio_writen(fd, buffer, n);
  }
}
