#include "headers/network.h"
#include "headers/intqueue.h"

#define QUEUE_SIZE 16
#define WORKERS 2

pthread_mutex_t fdMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t fdQEmpty = PTHREAD_COND_INITIALIZER;
pthread_cond_t fdQFull  = PTHREAD_COND_INITIALIZER;

struct IntQ *fdQ;

void enqueueFD(int fd);
void dequeueFD(int fd);

int main(int argc, char*argv[]) {
  int listenFD, clientFD, port, clientLength;
  struct hostent *hp;
  struct sockaddr_in clientAddress;
  rio_t rio;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <port>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  port = atoi(argv[1]);
  
  fdQ = createIntQ(QUEUE_SIZE);

  fprintf(stdout, "Server started at: %d\n", port);

  listenFD = open_listenfd(port);

  while (1) {
    clientLength = sizeof(clientAddress);
    clientFD = accept(listenFD, (SA *) &clientAddress, &clientLength);
    enqueueFD(clientFD);
  }
}

void enqueueFD(int fd) {
  pthread_mutex_lock(&fdMutex);

  while (fdQ->size == QUEUE_SIZE) {
    pthread_cond_wait(&fdQFull, &fdMutex);
  }

  intQPush(fdQ, fd);

  pthread_cond_signal(&fdQEmpty);
  pthread_mutex_unlock(&fdMutex);
}

int dequeueFD() {
  pthread_mutex_lock(&fdMutex);
  
  while (fdQ->size == 0) {
    pthread_cond_wait(&qEmpty, &fdMutex);
  }

  int num = intQPeek(fdQ);
  intQPop(fdQ);

  p_thread_cond_signal(&fdQFull);
  pthread_mutex_unlock(&fdMutex);

  return num;
}
