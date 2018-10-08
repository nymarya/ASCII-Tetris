#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include "threads.h" 
#define PORT 5001
 
int main(int argc, char const *argv[]) 
{ 
    struct sockaddr_in address; 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char buffer[1024] = {0}; 
    char *hello = "Hello from client"; 
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "10.7.119.18", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    
    //pthread_t thread_id; 
    //pthread_create(&thread_id, NULL, thread_button, &sock);
    //pthread_create(&thread_id, NULL, thread_ldr, &sock);
    //pthread_create(&thread_id, NULL, thread_potence, &sock);
    char cmd;
    char *gravity = "gravity_";
    char *rotate = "rotate__";

    /*while ((cmd=getchar())>0) {
        switch (cmd) {
            /*case 'q':
                t.x--;
                if (tetris_hittest(&t))
                    t.x++;
                break;
            case 'd':
                t.x++;
                if (tetris_hittest(&t))
                    t.x--;
                break;*/
            /*case 's':    
                send(sock , gravity , strlen(gravity) , 0 ); 
                send(sock , gravity , strlen(gravity) , 0 ); 
                send(sock , gravity , strlen(gravity) , 0 ); 
                printf("GRAVITY");
                valread = read( sock , buffer, 1024); 
                printf("%s\n",buffer );
                break;
            case ' ':
                send(sock , rotate , strlen(rotate) , 0 ); 
                printf("ROTATE");
                valread = read( sock , buffer, 1024); 
                printf("%s\n",buffer );
                break;
        }
    }*/


   // char *rotate = "rotate__";
    send(sock , rotate , strlen(rotate) , 0 );
    
    //send(sock , rotate , strlen(rotate) , 0 );
    printf("Rotate message sent\n");  
    valread = read( sock , buffer, 1024); 
    printf("%s\n",buffer );

    send(sock , gravity , strlen(gravity) , 0 );
    printf("Gravity message sent\n");  
    valread = read( sock , buffer, 1024); 
    printf("%s\n",buffer );
    //valread = read( sock , buffer, 1024); 
    //printf("%s\n",buffer );


    //send(sock , hello , strlen(hello) , 0 ); 
    //printf("Hello message sent\n"); 
    //valread = read( sock , buffer, 1024); 
    //printf("%s\n",buffer ); 
    return 0; 

} 