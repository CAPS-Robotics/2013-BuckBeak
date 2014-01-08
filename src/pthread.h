#ifndef __PTHREAD_H_
#define __PTHREAD_H_

#define O_CREAT 0

#include "semaphore.h"

typedef int pthread_t;

void   pthread_create(pthread_t *a, int *b, void* (c)(void*), int *d);

#endif