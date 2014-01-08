/*********************************************************************************//**
* @file semaphore.h
* @author Jacob Hegna
* Header file for mocking pthread functionality on an arbitrary OS
*************************************************************************************/

#ifndef __SEMAPHORE_H_
#define __SEMAPHORE_H_

/*************************************************************************************
* Typedefs
*************************************************************************************/
typedef int 				sem_t;

/*************************************************************************************
* Global functions
*************************************************************************************/
sem_t* sem_open(char *a, int b, int c, int d);
void   sem_post(sem_t *a);
void   sem_getvalue(sem_t *a, int *b);
int    sem_trywait(sem_t *a);

#endif