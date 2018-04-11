#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define PORTNUMBER 12345

int int_sum(char *str, int *result){

    int *arg1 = malloc(sizeof(int));

    int *arg2 = malloc(sizeof(int));

    int scaneo = sscanf(str,"%d + %d", arg1, arg2);

    if (scaneo == 2){
        *result = *arg1 + *arg2;
        return 0;
    } 
    else if (scaneo == 1){
        return 1;
    } 
    else if (scaneo == 0){
        return 2;
    }
    else {
        return scaneo;
    }
}

void server_func(int client, char * buf, int n){

    int result;

    char respuesta[256];
    /*bzero(respuesta, 256);*/

    int suma = int_sum(buf,&result);

    if(suma == 2){
        sprintf(respuesta,"%s","Mal formato");
    } 
    else if (suma == 1){
        sprintf(respuesta,"%s","Falta un operando más");
    }
    else {
        sprintf(respuesta,"Resultado: %d", result);
    }

    write(client, (void *)respuesta, strlen(respuesta)+1);

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