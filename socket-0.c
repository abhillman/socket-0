#include <stdio.h>                                                                                                            
#include <stdlib.h>                                                                                                           
#include <sys/socket.h>                                                                                                       
#include <netinet/in.h>                                                                                                       
                                                                                                                              
int main() {                                                                                                                  
    int sockfd;                                                                                                               
    struct sockaddr_in server_addr;                                                                                           
    socklen_t addr_len = sizeof(server_addr);                                                                                 
                                                                                                                              
    // Create socket                                                                                                          
    sockfd = socket(AF_INET, SOCK_STREAM, 0);                                                                                 
    if (sockfd < 0) {                                                                                                         
        perror("Socket creation failed");                                                                                     
        exit(EXIT_FAILURE);                                                                                                   
    }                                                                                                                         
                                                                                                                              
    // Bind to 127.0.0.1:0                                                                                                    
    server_addr.sin_family = AF_INET;                                                                                         
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);                                                                     
    server_addr.sin_port = 0;  // Let the OS choose the port                                                                  
                                                                                                                              
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {                                             
        perror("Bind failed");                                                                                                
        exit(EXIT_FAILURE);                                                                                                   
    }                                                                                                                         
                                                                                                                              
    // Get the chosen port                                                                                                    
    if (getsockname(sockfd, (struct sockaddr *)&server_addr, &addr_len) < 0) {                                                
        perror("Getsockname failed");                                                                                         
        exit(EXIT_FAILURE);                                                                                                   
    }                                                                                                                         
                                                                                                                              
    // Print the chosen port                                                                                                  
    printf("Chosen port: %d\n", ntohs(server_addr.sin_port));                                                                 
                                                                                                                              
    return 0;                                                                                                                 
}                                                                                                                             
