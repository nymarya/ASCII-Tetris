#include "threads.h"

/**
 * Thread que monitora o botao e controla a rotação
 */
void *thread_button(void *arg){
    char cmd;
    char *rotate = "rotate__"; 
    int valread;
    char buffer[1024] = {0}; 


    int *sock = (int *) arg;
    for(;;){
        while ((cmd=getchar())>0) {
            switch (cmd) {
                case ' ':
                    send(sock , rotate , strlen(rotate) , 0 );
                    valread = read( sock , buffer, 1024);
                    printf("Rotate\n"); 
                    //tetris_rotate(t);
                    break;
            }
        }
    }
    
    
    return NULL;
}

/**
 * Thread que monitora o sensor e controla a velocidade
 */
void *thread_ldr(void *arg){
    char cmd;
    char *gravity = "gravity_"; 
    int valread;
    char buffer[1024] = {0}; 

    int *sock = (int *) arg;
    //struct tetris *t = (struct tetris *) arg;
    for(;;){
        while ((cmd=getchar())>0) {
            switch (cmd) {
                case 's':
                    send(sock , gravity, strlen(gravity) , 0 );
                    valread = read( sock , buffer, 1024);
                    printf("Gravity\n"); 
                    //tetris_gravity(t);
                    break;
            }
        }
    }
    
    
    return NULL;
}

/**
 * Thread que monitora o potenciometro e controla o movimento
 * para os lados
 */
void *thread_potence(void *arg){
    char cmd;
    //struct tetris *t = (struct tetris *) arg;
    for(;;){
        while ((cmd=getchar())>0) {
            switch (cmd) {
                case 'q':
                    //t->x--;
                    /*if (tetris_hittest(t))
                        t->x++;*/
                    break;
                case 'd':
                    //t->x++;
                    /*if (tetris_hittest(t))
                        t->x--;*/
                    break;
            }
        }
    }
    
    
    return NULL;
}