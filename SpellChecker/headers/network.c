#include "network.h"

void getUserInput(rio_t *rio, int fd, char* string) {
  char buffer[MAXLINE];

  size_t length = rio_readlineb(rio, buffer, MAXLINE);

  strncpy(string, buffer, length - 2);
}

void printToUser(rio_t *rio, int fd, char *message) {
  rio_writen(fd, message, strlen(message));
  printf("%s", message);
}
