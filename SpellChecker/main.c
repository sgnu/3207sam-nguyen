#include "headers/network.h"
#include "headers/intqueue.h"

#define DICT_FILE "/usr/share/dict/words"
#define QUEUE_SIZE 16
#define WORKERS 2

pthread_mutex_t fdMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t fdQEmpty = PTHREAD_COND_INITIALIZER;
pthread_cond_t fdQFull  = PTHREAD_COND_INITIALIZER;

struct IntQ *fdQ;

char dict[256000][MAXLINE];
int count = 0;

void enqueueFD(int fd);
int dequeueFD();

void *spellChecker(void *param);

int main(int argc, char*argv[]) {
  int listenFD, clientFD, port, clientLength;
  struct hostent *hp;
  struct sockaddr_in clientAddress;
  pthread_t spellCheckers[WORKERS];

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <port>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  port = atoi(argv[1]);
  
  fdQ = createIntQ(QUEUE_SIZE);

  char buffer[MAXLINE];
  FILE * dictFile = fopen(DICT_FILE, "r");

  while(fscanf(dictFile, "%s", buffer) > 0) {
    strcpy(dict[count], buffer);
    count++;
  }

  for (int i = 0; i < WORKERS; i++) {
    pthread_create(&spellCheckers[i], NULL, spellChecker, NULL);
  }

  fprintf(stdout, "Server started at: %d\n", port);

  listenFD = open_listenfd(port);

  while (1) {
    clientLength = sizeof(clientAddress);
    clientFD = accept(listenFD, (SA *) &clientAddress, &clientLength);
    hp = gethostbyaddr((const char *) &clientAddress.sin_addr.s_addr, sizeof(clientAddress.sin_addr.s_addr), AF_INET);
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
    pthread_cond_wait(&fdQEmpty, &fdMutex);
  }

  int num = intQPeek(fdQ);
  intQPop(fdQ);

  pthread_cond_signal(&fdQFull);
  pthread_mutex_unlock(&fdMutex);

  return num;
}

void *spellChecker(void *param) {
  rio_t rio;
  while (1) {
    int clientFD;
    clientFD = dequeueFD();

    printf("Worker connected to %d\n", clientFD);

    rio_readinitb(&rio, clientFD);
    
    printToUser(&rio, clientFD, "Connection Success!\n");

    while (1) {

    }
  }
}
