/**
 * FIFO circular queue of integers using structs and methods that act on the struct
 */

#ifndef INT_QUEUE_H
#define INT_QUEUE_H

#include "csapp.h"

typedef struct IntQ {
  int capacity;
  int size;
  int front;
  int rear;
  int *arr;
} IntQ;

/**
 * Creates a queue of integers
 * @param size max size of queue
 * @returns a queue
 */
IntQ *createIntQueue(int size);

/**
 * Adds an int to the rear of the queue
 */
void intQPush(IntQ *intQ, int item);

/**
 * Removes the int from the front
 */
void intQPop(IntQ *intQ);

/**
 * Gets the int from the front without removing it
 */
int intQPeek(IntQ *intQ);

#endif