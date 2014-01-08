#ifndef __PTHREAD_H_
#define __PTHREAD_H_

#define O_CREAT 0

typedef int sem_t;
typedef int pthread_t;

sem_t* sem_open(char *a, int b, int c, int d);
void   pthread_create(pthread_t *a, int *b, void* (c)(void*), int *d);
void   sem_post(sem_t *a);
void   sem_getvalue(sem_t *a, int *b);
int    sem_trywait(sem_t *a);


#endif