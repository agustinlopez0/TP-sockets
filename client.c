#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "sockets.h"


int main(int argc, char* argv[]){

    if (argc != 3) {
        fprintf(stderr,"No se recibio la cantidad esperada de argumentos:\n");
        fprintf(stderr,"    ./cliente <IP servidor> <Puerto servidor>");
        exit(1);
    }

    // 1. Apertura de un socket, como el servidor, por medio de la función socket()

    int sockfd, status;
    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; //IPV4
    hints.ai_socktype = SOCK_STREAM; //TCP

    status = getaddrinfo(argv[1], argv[2], &hints, &res);

    if (status != 0) {
        fprintf(stderr, "Error: %s\n", gai_strerror(status));
        return 2;
    } else {
        printf("Get address info successful\n");
    }

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    // 2. Solicitar conexión con el servidor por medio de la función connect(). 
    // Dicha función quedará bloqueada hasta que el servidor acepte nuestra conexión o bien si no hay servidor en el sitio indicado, saldrá dando un error. 
    // En esta llamada se debe facilitar la dirección IP del servidor y el número de servicio que se desea.

    int connectStatus = connect(sockfd, res->ai_addr, res->ai_addrlen);

    if(connectStatus == -1){
        fprintf(stderr,"Error %s\n", gai_strerror(connectStatus));
        return -1;
    } else {
        printf("Connect successful\n");
    }

    // 3. Escribir y recibir datos del servidor por medio de las funciones send() y recv().


    char msg[MAX_BUFF_LENGTH], buff[MAX_BUFF_LENGTH];
    // char *msg = "HOLA REY";

    int sentBytes, receivedBytes, i = 0, r;

    while(1){
        memset(buff, 0, sizeof(buff));
        memset(buff, 0, sizeof(msg));
        printf("%i:\n", i);

        switch( i ){
            case 0:
                strcpy(msg, "Hola rey");
                break;
            case 1:
                printf(("Ingrese el nombre de usuario: "));
                scanf("%[^\n]", msg);
                getchar();
                break;
            case 2:
                printf(("Ingrese su contraseña: "));
                scanf("%[^\n]", msg);
                getchar();
                break;
            default: 
                memset(msg, 0, sizeof(msg));
                printf("Ingresar el mensaje a enviar: ");
                scanf("%[^\n]", msg);
        }

        // mensaje enviado 
        sentBytes = send(sockfd, msg, strlen(msg), 0);
        if(sentBytes < 0){
            fprintf(stderr, "Error %s\n", gai_strerror(sentBytes));
            return -1;
        } else {
            printf("\nMensaje enviado: %s\n", msg);
        }
        
        // mensaje recibido
        receivedBytes = recv(sockfd, buff, MAX_BUFF_LENGTH, 0);
        if (receivedBytes < 0) {
            fprintf(stderr,"Error: %s\n", gai_strerror(receivedBytes));
            return -1;
        } else {
            printf("Server response: %s\n", buff);
        }


        if( !strcmp(buff, "230" ) ){
            i++;
        }


    }

    //4. Cerrar la comunicación por medio de close().





    return 0;
}