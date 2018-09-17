#include "threads.h"

void initThreads(struct tetris *t){
    pthread_t thread_id_btn; 
    pthread_t thread_id_ldr;
    pthread_t thread_id_potenciometer;

    int priority_max = sched_get_priority_max(SCHED_FIFO);
    int priority_min = sched_get_priority_min(SCHED_FIFO);

    int rc_btn;
    pthread_attr_t attr_btn;
    struct sched_param param_btn;

    rc_btn = pthread_attr_init (&attr_btn);
    rc_btn = pthread_attr_getschedparam (&attr_btn, &param_btn);
    param_btn.sched_priority=priority_min;
    rc_btn = pthread_attr_setschedparam (&attr_btn, &param_btn);

    int rc_ldr;
    pthread_attr_t attr_ldr;
    struct sched_param param_ldr;

    rc_ldr = pthread_attr_init (&attr_ldr);
    rc_ldr = pthread_attr_getschedparam (&attr_ldr, &param_ldr);
    param_ldr.sched_priority = (priority_max + priority_min) /2;
    rc_ldr = pthread_attr_setschedparam (&attr_ldr, &param_ldr);

    // Configura prioridade do potenciometro
    int rc_pot;
    pthread_attr_t attr_pot;
    struct sched_param param_pot;

    rc_pot = pthread_attr_init (&attr_pot);
    rc_pot = pthread_attr_getschedparam (&attr_pot, &param_pot);
    param_pot.sched_priority=priority_max;
    rc_pot = pthread_attr_setschedparam (&attr_pot, &param_pot);

    // Cria as threads
    pthread_create(&thread_id_btn, &attr_btn, threadButton, t);
    pthread_create(&thread_id_ldr, &attr_ldr, threadLdr, t);
    pthread_create(&thread_id_potenciometer, &attr_pot, threadPotenciometer, t);

    //pthread_join(thread_id_btn, NULL);
    //pthread_join(thread_id_ldr, NULL);
    //pthread_join(thread_id_potenciometer, NULL);

}

/**
 * Thread que monitora o botao e controla a rotação
 */
void *threadButton(void *arg){
    char cmd;
    struct tetris *t = (struct tetris *) arg;
    for(;;){
        while ((cmd=getchar())>0) {
            switch (cmd) {
                case ' ':
                    tetris_rotate(t);
                    break;
            }
        }
    }
    
    
    return NULL;
}

/**
 * Thread que monitora o sensor e controla a velocidade
 */
void *threadLdr(void *arg){
    char cmd;
    struct tetris *t = (struct tetris *) arg;
    for(;;){
        while ((cmd=getchar())>0) {
            switch (cmd) {
                case 's':
                    tetris_gravity(t);
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
void *threadPotenciometer(void *arg){
    char cmd;
    struct tetris *t = (struct tetris *) arg;
    for(;;){
        while ((cmd=getchar())>0) {
            switch (cmd) {
                case 'q':
                    t->x--;
                    if (tetris_hittest(t))
                        t->x++;
                    break;
                case 'd':
                    t->x++;
                    if (tetris_hittest(t))
                        t->x--;
                    break;
            }
        }
    }
    
    
    return NULL;
}