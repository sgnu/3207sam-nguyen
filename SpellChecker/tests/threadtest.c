/**
 * Multithreading test
 * One producer adds ints to a queue
 * Consumers remove ints from the queue and print them
 */

#include "../headers/intqueue.h"

#define QUEUE_SIZE 16
#define WORKERS 4

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t qReady = PTHREAD_COND_INITIALIZER;
pthread_cond_t qEmpty = PTHREAD_COND_INITIALIZER;
pthread_cond_t qFull  = PTHREAD_COND_INITIALIZER;
struct IntQ *queue;
int count = 0;

void *consumerFunction(void *param);
void *producerFunction(void *param);

int main(void) {
  pthread_t producer;
  pthread_t consumers[WORKERS];

  queue = createIntQ(QUEUE_SIZE);

  // Create producer
  pthread_create(&producer, NULL, producerFunction, NULL);

  // Create consumers
  for (int i = 0; i < WORKERS; i++) {
    pthread_create(&consumers[i], NULL, consumerFunction, i);
  }

  while(1) {}
}

void *consumerFunction(void *param) {
  while(1){
    int num;

    // Lock mutex
    pthread_mutex_lock(&mutex);

    // Wait while queue is empty
    while (queue->size == 0) {
      pthread_cond_wait(&qEmpty, &mutex);
    }

    num = intQPeek(queue);
    intQPop(queue);

    printf("Consumer %d: %d\n", (int) param, num);

    // Signal that queue is no longer full
    pthread_cond_signal(&qFull);
    // Unlock mutex
    pthread_mutex_unlock(&mutex);

    // Sleep used to make output readable as test runs
    sleep(1);
  }
}

void *producerFunction(void *param) {
  while(1) {
    // Lock mutex
    pthread_mutex_lock(&mutex);

    // Wait while queue is full
    while (queue->size == QUEUE_SIZE) {
      pthread_cond_wait(&qFull, &mutex);
    }

    printf("Producer  : %d\n", count);

    intQPush(queue, count++);
    // Signal that queue is no longer empty
    pthread_cond_signal(&qEmpty);
    // Unlock mutex
    pthread_mutex_unlock(&mutex);
  }
}
