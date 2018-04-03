#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define PORTNUMBER 12345
char *character_generator(){
    static char c = 32;
    if (c>126){
        c=32;
    }
    char *buf = malloc(sizeof(char) * 2);
    snprintf(buf, sizeof(buf),"%c",c++);
    return buf;
}

void server_func(int client, char * buf, int n){
    for(int i=0;i<1000;i++){
      write(client,(void*)character_generator(),1);
    }
    
}
int main(void){
    char buf[10];
    int s, n, ns, len;
    struct sockaddr_in direcc;

    s = socket(AF_INET, SOCK_STREAM, 0);
    bzero((char *) &direcc, sizeof(direcc));

    direcc.sin_family = AF_INET;
    direcc.sin_port = htons(PORTNUMBER);
    direcc.sin_addr.s_addr = htonl(INADDR_ANY);

    len = sizeof(struct sockaddr_in);

    bind(s, (struct sockaddr *) &direcc, len);

    listen(s, 5);
    while(1){
        ns = accept(s, (struct sockaddr *) &direcc, &len);

        while ((n = recv(ns, buf, sizeof(buf), 0)) > 0){
            server_func(ns,buf,n);
        }
    }
    
    close(ns); close(s);
    exit(0);
}    