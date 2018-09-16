#include "threads.h"

/**
 * Thread que monitora o botao e controla a rotação
 */
void *thread_button(void *arg){

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
            while( pressed == 1 ){
                
		// ação: girar peça
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
void *thread_ldr(void *arg){

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
            while( speed < 100 ){
                
		// ação: acelera descida dos blocos
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
void *thread_potence(void *arg){

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
            while( move < 800 ){
                
		// ação: mover para a direita
		t->x++;
                if (tetris_hittest(t))
                    t->x--;
                break;

	    } 
	    while( move > 1500 ){
                
		// ação: mover para a esquerda
		t->x--;
                if (tetris_hittest(t))
                    t->x++;
                break;

	    }
	}

    }
    
    
    return NULL;
}
