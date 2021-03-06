#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define PORTNUMBER 12345
void server_func(int client, char * buf, int n){
    // Envío al cliente la misma data que nos envió
    // echo
    write(client,buf,n);
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

    ns = accept(s, (struct sockaddr *) &direcc, &len);

    while ((n = recv(ns, buf, sizeof(buf), 0)) > 0){
        server_func(ns,buf,n);
        bzero(buf, sizeof(buf));
    }
    printf("cierror\n");
    
    close(ns)
    close(s);
    exit(0);
}    
