#include "network.h"

int openClientfd(char* hostName, int port) {
  // fd to return
  int clientfd;
  struct hostent* hp;
  struct sockaddr_in serverAddress;

  // Attempt to create a socket
  if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    return -1;
  }

  // Attempt to get host
  if ((hp = gethostbyname(hostName)) == NULL) {
    return -2;
  }

  // Fill in the server's IP and port
  bzero((char*)&serverAddress, sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;
  bcopy((char*)hp->h_addr_list[0], (char*)&serverAddress.sin_addr.s_addr,
        hp->h_length);
  serverAddress.sin_port = htons(port);

  // Attempt to connect to server
  if (connect(clientfd, (SA*)&serverAddress, sizeof(serverAddress)) < 0) {
    return -1;
  }

  return clientfd;
}
