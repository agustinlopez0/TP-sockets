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
    }

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    // 2. Solicitar conexión con el servidor por medio de la función connect(). 
    // Dicha función quedará bloqueada hasta que el servidor acepte nuestra conexión o bien si no hay servidor en el sitio indicado, saldrá dando un error. 
    // En esta llamada se debe facilitar la dirección IP del servidor y el número de servicio que se desea.

    int connectStatus = connect(sockfd, res->ai_addr, res->ai_addrlen);

    if(connectStatus == -1){
        fprintf(stderr,"Error %s\n", gai_strerror(connectStatus));
        return -1;
    }







    return 0;
}