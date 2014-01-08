#ifndef __SEMAPHORE_H_
#define __SEMAPHORE_H_

typedef int sem_t;

sem_t* sem_open(char *a, int b, int c, int d);
void   sem_post(sem_t *a);
void   sem_getvalue(sem_t *a, int *b);
int    sem_trywait(sem_t *a);

#endif