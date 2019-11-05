#include "../headers/intqueue.h"

int main(void) {
  struct IntQ *queue = createIntQ(4);
  for (int i = 0; i < 4; i++) {
    intQPush(queue, i);
  }

  printf("size: %d front: %d rear: %d\n", queue->size, queue->front, queue->rear);
  intQPrint(queue);

  intQPop(queue);
  intQPop(queue);

  printf("size: %d front: %d rear: %d\n", queue->size, queue->front, queue->rear);
  intQPrint(queue);

  return 0;
}
