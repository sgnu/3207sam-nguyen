#include "intqueue.h"

IntQ *createIntQueue(int capacity) {
  // Create the intQ
  IntQ *intQ;
  intQ = (IntQ *) malloc(sizeof(IntQ));

  // Initialize
  intQ->arr = (int*) malloc(sizeof(int) * capacity);
  intQ->size = 0;
  intQ->capacity = capacity;
  intQ->front = 0;
  intQ->rear = -1;

  return intQ;
}

void intQPush(IntQ *intQ, int item) {
  if (intQ->size >= intQ->capacity) {
    fprintf(stderr, "Pushing to intQ when intQ is full");
    exit(EXIT_FAILURE);
  }

  intQ->size++;
  intQ->rear = (intQ->rear + 1) % intQ->capacity;
  intQ->arr[intQ->rear] = item;
}

void intQPop(IntQ *intQ) {
  if (intQ->size <= 0) {
    fprintf(stderr, "Popping from intQ when intQ is empty");
    exit(EXIT_FAILURE);
  }

  intQ->size--;
  intQ->front = (intQ->front + 1) % intQ->capacity;
}

int intQPeek(IntQ *intQ) {
  if (intQ->size <= 0) {
    fprintf(stderr, "Peeking into intQ when intQ is empty");
    exit(EXIT_FAILURE);
  }

  return intQ->arr[intQ->front];
}

void intQPrint(IntQ *intQ) {
  int i = intQ->front;

  while (i != intQ->rear) {
    printf("%d\n", intQ->arr[i]);
    i = (i + 1) % intQ->capacity;
  } // Prints up to rear

  // Print the rear
  printf("%d\n", intQ->arr[intQ->rear]);
}
