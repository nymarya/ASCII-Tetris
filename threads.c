#include "threads.h"

struct tetris *t;
void *thread_button(void *arg){
   // char cmd;
    printf("Printing GeeksQuiz from Thread \n");
    /**
    while ((cmd=getchar())>0) {
        switch (cmd) {
            case ' ':
                t = (struct tetris *) arg;
                tetris_rotate(&t);
                break;
        }
    }**/
    return NULL;
}