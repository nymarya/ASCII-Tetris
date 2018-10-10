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
     
    char *rotate = "rotate__";
    char *gravity = "gravity_";
    char *go_left = "go_left_";
    char *go_right = "go_right";
    char cmd;
    while ((cmd=getchar())>0) {
        switch (cmd) {
            case 'q':
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
                send(sock , go_left , strlen(rotate) , 0 );
                valread = read( sock , buffer, 1024);
                break;
            case 'd':
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
                send(sock , go_right , strlen(rotate) , 0 );
                valread = read( sock , buffer, 1024);
                break;
            case 's':
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
                send(sock , gravity , strlen(rotate) , 0 );
                valread = read( sock , buffer, 1024);
                break;
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
   
    
    
    close(sock);
    return 0; 

} 