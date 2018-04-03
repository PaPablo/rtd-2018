#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include<arpa/inet.h>
#include<stdio.h> //printf
#include<stdlib.h> //exit(0);
#include<string.h> //memset
#include<sys/socket.h>
#define PORTNUMBER 12345
void server_func(int sock, const void *buf, size_t len, int flags,
                    const struct sockaddr *sockaddr_in, socklen_t addrlen){
    // Envío al cliente la misma data que nos envió
    // echo
    sendto(sock, buf, len, flags, sockaddr_in, addrlen);
}
int main(void){
    char buf[10];
    int sock, len, cliente;
    int len_recv;
    struct sockaddr_in src,dest;


    if((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
        printf("Error al crear socket\n");
        exit(1);
    }

    bzero((char *) &src, sizeof(src));

    src.sin_family = AF_INET;
    src.sin_port = htons(PORTNUMBER);
    src.sin_addr.s_addr = htonl(INADDR_ANY);

    len = sizeof(dest);

    bind(sock, (struct sockaddr *) &src, sizeof(src));

    while(1){
        // recibir por el socket
        if ((len_recv = recvfrom(
                        sock, 
                        buf, 
                        sizeof(buf),
                        0, 
                        (struct sockaddr *) &dest,
                        &len)) == -1) {
            printf("Error en el recieve\n");
            exit(1);
        }

        if(sendto(sock, buf, strlen(buf), 0, (struct sockaddr *)&dest, len) == -1){
            printf("error en send\n");
            exit(1);
        }
        bzero(buf, sizeof(buf));
    }
    
    close(sock);
    exit(0);
}