#include "headers/network.h"
#include "headers/intqueue.h"

#define PORT 4200
#define DICT_FILE "/usr/share/dict/words"
#define QUEUE_SIZE 16
#define WORKERS 2

pthread_mutex_t fdMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t fdQEmpty = PTHREAD_COND_INITIALIZER;
pthread_cond_t fdQFull  = PTHREAD_COND_INITIALIZER;

pthread_mutex_t logMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t logQEmpty = PTHREAD_COND_INITIALIZER;
pthread_cond_t logQFull  = PTHREAD_COND_INITIALIZER;

struct IntQ *fdQ;
// Q just like intQ; didn't feel like implementing it the same way
char logQ[QUEUE_SIZE][MAXLINE];
int logFront = 0;
int logRear = -1;
int logSize = 0;

char dict[256000][MAXLINE];
int count = 0;

void enqueueFD(int fd);
int dequeueFD();

void enqueueLog(const char* string);
void dequeueLog(char* string);

void *spellChecker(void *param);
void *logger(void *param);

int checkWord(const char*word);

int main(int argc, char*argv[]) {
  int listenFD, clientFD, port, clientLength;
  char *dictionaryFile;
  struct hostent *hp;
  struct sockaddr_in clientAddress;
  pthread_t spellCheckers[WORKERS], loggerThread;

  if (argc == 1) {
    port = PORT;
    strcpy(dictionaryFile, DICT_FILE);
  } else if (argc == 2) {
    port = atoi(argv[1]);
    strcpy(dictionaryFile, DICT_FILE);
  } else {
    port = atoi(argv[1]);
    strcpy(dictionaryFile, argv[2]);
  }
  
  fdQ = createIntQ(QUEUE_SIZE);

  char buffer[MAXLINE];
  FILE * dictFile = fopen(dictionaryFile, "r");

  while(fscanf(dictFile, "%s", buffer) > 0) {
    strcpy(dict[count], buffer);
    count++;
  }

  pthread_create(&loggerThread, NULL, logger, NULL);

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

void enqueueLog(const char *string) {
  pthread_mutex_lock(&logMutex);

  while (logSize == QUEUE_SIZE) {
    pthread_cond_wait(&logQFull, &logMutex);
  }

  if (logSize >= QUEUE_SIZE) {
    fprintf(stderr, "Pushing into log queue when queue is full\n");
    exit(EXIT_FAILURE);
  }

  logSize++;
  logRear = (logRear + 1) % QUEUE_SIZE;
  strcpy(logQ[logRear], string);

  pthread_cond_signal(&logQEmpty);
  pthread_mutex_unlock(&logMutex);
}

void dequeueLog(char *string) {
  pthread_mutex_lock(&logMutex);

  while (logSize == 0) {
    pthread_cond_wait(&logQEmpty, &logMutex);
  }

  if (logSize <= 0) {
    fprintf(stderr, "Popping from log queue when queue is empty\n");
    exit(EXIT_FAILURE);
  }

  logSize--;

  strcpy(string, logQ[logFront]);
  memset(logQ[logFront], 0, MAXLINE);
  logFront = (logFront + 1) % QUEUE_SIZE;

  pthread_cond_signal(&logQFull);
  pthread_mutex_unlock(&logMutex);
}

void *spellChecker(void *param) {
  rio_t rio;
  while (1) {
    char buffer[MAXLINE];
    int clientFD = dequeueFD();

    printf("Worker connected to %d\n", clientFD);

    rio_readinitb(&rio, clientFD);
    
    printToUser(&rio, clientFD, "Connection Success!\n");

    do {
      memset(buffer, 0, sizeof(buffer));
      char toUser[MAXLINE];
      getUserInput(&rio, clientFD, buffer);
      strcpy(toUser, buffer);

      if (checkWord(buffer) == 1) {
        strcat(toUser, " OK\n");
      } else {
        strcat(toUser, " MISSPELLED\n");
      }

      printToUser(&rio, clientFD, toUser);
      enqueueLog(toUser);
    } while (buffer[0] != 27);

    close(clientFD);
  }
}

void *logger(void *param) {
  while(1) {
    FILE *logFile = fopen("log", "a");
    char buffer[MAXLINE];
    dequeueLog(buffer);

    printf("logger: %s\n", buffer);

    fprintf(logFile, "%s\n", buffer);

    fclose(logFile);
  }
}

int checkWord(const char *word) {
  int i = 0;
  
  while (strcmp(word, dict[i]) > 0) {
    i++;
    if (strcmp(word, dict[i]) == 0) {
      return 1;
    }
  }

  return 0;
}
