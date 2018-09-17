#include "threads.h"

void initThreads(struct tetris *t){
    pthread_t thread_id_btn; 
    pthread_t thread_id_ldr;
    pthread_t thread_id_potenciometer;

    int priority_max = sched_get_priority_max(SCHED_FIFO);
    int priority_min = sched_get_priority_min(SCHED_FIFO);

    // Configura prioridade do botão (99)
    int rc_btn;
    pthread_attr_t attr_btn;
    struct sched_param param_btn;

    rc_btn = pthread_attr_init (&attr_btn);
    rc_btn = pthread_attr_getschedparam (&attr_btn, &param_btn);
    param_btn.sched_priority=priority_max;
    rc_btn = pthread_attr_setschedparam (&attr_btn, &param_btn);

    // Configura prioridade do LDR (50)
    int rc_ldr;
    pthread_attr_t attr_ldr;
    struct sched_param param_ldr;

    rc_ldr = pthread_attr_init (&attr_ldr);
    rc_ldr = pthread_attr_getschedparam (&attr_ldr, &param_ldr);
    param_ldr.sched_priority = (priority_max + priority_min) /2;
    rc_ldr = pthread_attr_setschedparam (&attr_ldr, &param_ldr);

    // Configura prioridade do potenciometro (1)
    int rc_pot;
    pthread_attr_t attr_pot;
    struct sched_param param_pot;

    rc_pot = pthread_attr_init (&attr_pot);
    rc_pot = pthread_attr_getschedparam (&attr_pot, &param_pot);
    param_pot.sched_priority=priority_min;
    rc_pot = pthread_attr_setschedparam (&attr_pot, &param_pot);

    // Cria as threads
    pthread_create(&thread_id_btn, &attr_btn, threadButton, t);
    pthread_create(&thread_id_ldr, &attr_ldr, threadLdr, t);
    pthread_create(&thread_id_potenciometer, &attr_pot, threadPotenciometer, t);

}

/**
 * Thread que monitora o botao e controla a rotação
 */
void *threadButton(void *arg){
    FILE *btn;
    char btnValue[10];
    
    char cmd;
    struct tetris *t = (struct tetris *) arg;
    for(;;){

        /** RECUPERANDO STATUS DO BOTÃO **/
        btn = popen("cat /sys/class/gpio/gpio115/value", "r");
        if (btn == NULL) {
            printf("Failed to run command\n" );
            exit(1);
        }
	

	    /* Consome a primeira linha da saída do comando */
        if (fgets(btnValue, sizeof(btnValue)-1, btn) != NULL ) {
            int pressed = atoi(btnValue);
            if( pressed == 1 ){
                
            // ação: girar peça
            tetris_rotate(t);

	        }
	    }

    }
    
    
    return NULL;
}

/**
 * Thread que monitora o sensor e controla a velocidade
 */
void *threadLdr(void *arg){

    FILE *res;
    char resValue[10];

    char cmd;
    struct tetris *t = (struct tetris *) arg;
    for(;;){


        /** RECUPERANDO STATUS DO FOTORESISTOR **/
        res = popen("cat /sys/bus/iio/devices/iio:device0/in_voltage3_raw", "r");
        if (res == NULL) {
            printf("Failed to run command\n" );
            exit(1);
        }

 	    /* Consome a primeira linha da saída do comando */
        if (fgets(resValue, sizeof(resValue)-1, res) != NULL ) {
            int speed = atoi(resValue);
            if( speed < 100 ){
                
                // ação: acelera descida dos blocos
                tetris_gravity(t);
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

    FILE *pot;
    char potValue[10];
    char cmd;
    struct tetris *t = (struct tetris *) arg;
    for(;;){
        

        /** RECUPERANDO STATUS DO POTENCIOMETRO **/
        pot = popen("cat /sys/bus/iio/devices/iio:device0/in_voltage1_raw", "r");
        if (pot == NULL) {
            printf("Failed to run command\n" );
            exit(1);
        }

	    /* Consome a primeira linha da saída do comando */
        if (fgets(potValue, sizeof(potValue)-1, pot) != NULL ) {
            int move = atoi(potValue);
            if( move < 800 ){
                
                // ação: mover para a direita
                t->x++;
                if (tetris_hittest(t))
                    t->x--;

            } 
            else if( move > 1500 ){
                    
                // ação: mover para a esquerda
                t->x--;
                if (tetris_hittest(t))
                    t->x++;

            }
	    }

    }
    
    
    return NULL;
}
