#include "threads.h"

/**
 * Thread que monitora o botao e controla a rotação
 */
void *thread_button(void *arg){
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
void *thread_ldr(void *arg){
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
void *thread_potence(void *arg){
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

/**
 * thread que abre a coneão do servidor
 */
void * thread(void *arg){
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *hello = "Hello from server"; 
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 

    while( 1 ){
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
        { 
            perror("accept"); 
            exit(EXIT_FAILURE); 
        } 

        while (1){
            valread = read( new_socket , buffer, 1024); 
            if( valread == -1){
                //trata msg para controlar jogo
                break;
            } else if (valread == 0){
                exit(EXIT_SUCCESS);
            }
            printf("%s\n",buffer );
        }
    }
}