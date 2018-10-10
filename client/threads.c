#include "threads.h"

/**
 * Thread que monitora o botao e controla a rotação
 */
void *thread_button(void *arg){
    char cmd;
    char *rotate = "rotate__"; 
    int valread;
    char buffer[1024] = {0}; 
    struct sockaddr_in serv_addr;

    int sock = (int ) arg;
    for(;;){
        while ((cmd=getchar())>0) {
            switch (cmd) {
                case ' ':
                    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
                        printf("\n Socket creation error \n"); 
                        return -1; 
                    } 
                
                    memset(&serv_addr, '0', sizeof(serv_addr)); 
                
                    serv_addr.sin_family = AF_INET; 
                    serv_addr.sin_port = htons(PORT); 
                    
                    // Convert IPv4 and IPv6 addresses from text to binary form 
                    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
                    { 
                        printf("\nInvalid address/ Address not supported \n"); 
                        return -1; 
                    } 
                
                    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
                    { 
                        printf("\nConnection Failed \n"); 
                        return -1; 
                    } 
                    send(sock , rotate , strlen(rotate) , 0 );
                    valread = read( sock , buffer, 1024);
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