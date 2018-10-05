#ifndef THREADS_H
#define THREADS_H

#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include "common.h"

void *thread_button(void *arg);
void *thread_ldr(void *arg);
void *thread_potence(void *arg);

#endif