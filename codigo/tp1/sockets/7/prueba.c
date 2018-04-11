#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int int_sum(char *str, int *result){

    int *arg1 = malloc(sizeof(int));

    int *arg2 = malloc(sizeof(int));

    if (sscanf(str,"%d + %d", arg1, arg2) == 2){
        *result = *arg1 + *arg2;
        return 0;
    } else {
        return 1;
    }
}

int main(void){

    char * buff = malloc(sizeof(char) * 1024);

    while(fgets(buff,1024,stdin) >0){

        int *result = malloc(sizeof(int));

        if(int_sum(buff, result)){
            printf("Bad format\n");
        } else 

        printf("Resultado: %d\n", *result);
    }
    exit(0);
}
