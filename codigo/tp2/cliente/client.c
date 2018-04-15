#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <string.h> 

#define PORT 12345

int main(int argc, char const* argv[]){

    int sock = 0;

    // estructura para guardar la dirección del servidor
    struct sockaddr_in server_address;

    // buffers para escribir y leer del socket
    char *buffer = malloc(sizeof(char) * 256);
    char *answer = malloc(sizeof(char) * 256);

    // creamos el socket
    sock = socket(AF_INET, SOCK_STREAM,0);


    // manejo de error en la creación del socket
    if (sock < 0){
        printf("Socket no se pudo crear");
        exit(1);
    }

    // limpieza
    bzero((char *) &server_address, sizeof(server_address));


    // setup de la dirección y puerto del socket
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    // se limpia
    memset(server_address.sin_zero, '\0', sizeof(server_address.sin_zero));  


    // Hasta EOF
        fgets(buffer,256,stdin);
        // Conexión
        if( connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
        {
            printf("\n Error : Connect Failed \n");
            return 1;
        } 
        // Escribo lo que tenga en buffer
        
        send(sock, buffer, strlen(buffer)+1,0);
        
        bzero(buffer, 256);
        bzero(answer, 256);

        // Recibo del servidor
        int valread = recv(sock, (void *)answer, 256,0);

        // Muestro
        printf("%s",answer);

        close(sock);
        

    return 0;
}
