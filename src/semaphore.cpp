/*********************************************************************************//**
* @file semaphore.cpp
* @author Jacob Hegna
* Header file for mocking pthread functionality on an arbitrary OS
*************************************************************************************/

#include "semaphore.h"

/*************************************************************************************
* Global functions
*************************************************************************************/
sem_t* sem_open(char *a, int b, int c, int d) {
    return nullptr;
}

void sem_post(sem_t *a) {

}

void sem_getvalue(sem_t *a, int *b) {

}

int  sem_trywait(sem_t *a) {
    return 0;
}