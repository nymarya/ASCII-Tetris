#ifndef THREADS_H
#define THREADS_H

#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include "common.h"
#include <sched.h>


void initThreads(struct tetris *t);
void *threadButton(void *arg);
void *threadLdr(void *arg);
void *threadPotenciometer(void *arg);

#endif