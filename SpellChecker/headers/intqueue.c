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
  intQ->rear = (intQ->rear++) % intQ->capacity;
  intQ->arr[intQ->rear] = item;
}

void intQPop(IntQ *intQ) {
  if (intQ->size <= 0) {
    fprintf(stderr, "Popping from intQ when intQ is empty");
    exit(EXIT_FAILURE);
  }

  intQ->size--;
  intQ->front = (intQ->front++) % intQ->capacity;
}

int intQPeek(IntQ *intQ) {
  if (intQ->size <= 0) {
    fprintf(stderr, "Peeking into intQ when intQ is empty");
    exit(EXIT_FAILURE);
  }

  return intQ->arr[intQ->front];
}