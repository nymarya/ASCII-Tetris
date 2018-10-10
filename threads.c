#include "threads.h"



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

        send(new_socket , hello , strlen(hello) , 0 ); 

        //printf("aa");

        while (1){
            valread = read( new_socket , buffer, 1024); 
            if( valread != 0){
                send(new_socket,buffer,strlen(buffer),0);
                //trata msg para controlar jogo
                struct tetris *t = (struct tetris *) arg;
                char * rotate = "rotate__";
                char * gravity = "gravity_";
                char * left = "go_left_";
                char * right = "go_right";
                if( strcmp(buffer,rotate) == 0){
                    tetris_rotate(t);
                } else if( strcmp(buffer,left) == 0){
                    t->x--;
                    if (tetris_hittest(t))
                        t->x++;
                } else if( strcmp(buffer,gravity) == 0){
                    tetris_gravity(t);
                } else if( strcmp(buffer, right) == 0){
                    t->x--;
                    if (tetris_hittest(t))
                        t->x--;
                }
                break;
            } else if (valread == 0){
                pthread_exit(NULL);
            } else {
                printf("erro");
            }
            
        }
    }

    pthread_exit(NULL);
}