#include "network.h"

void getUserInput(rio_t *rio, int fd, char* string) {
  char buffer[MAXLINE];

  rio_readlineb(rio, buffer, MAXLINE);

  strcpy(string, buffer);
}

void printToUser(rio_t *rio, int fd, char *message) {
  rio_writen(fd, message, strlen(message));
  printf("%s\n", message);
}
