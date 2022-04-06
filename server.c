#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


#include "sockets.h"

int main(int argc, char* argv[]){
    
    if (argc != 2) {
        fprintf(stderr,"No se recibio la cantidad esperada de argumentos:\n");
        fprintf(stderr,"    ./server <Puerto servidor>");
        exit(1);
    }

    // 1. Apertura de un socket, mediante la función socket(). Esta función devuelve un descriptor de fichero normal, como puede devolverlo open(). 
    // La función socket() no hace absolutamente nada, 
    // salvo devolvernos y preparar un descriptor de fichero que el sistema posteriormente asociará a una conexión en red.
    
    int sockfd, status;
    
    struct addrinfo hints, *res;
    struct sockaddr_storage their_addr;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
    hints.ai_flags = AI_PASSIVE; // fill in my IP for me
    
    status = getaddrinfo(NULL, argv[1], &hints, &res);

    if (status != 0) {
        fprintf(stderr, "Error: %s\n", gai_strerror(status));
        return 2;
    }

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    // 2. Avisar al sistema operativo de que hemos abierto un socket y queremos que asocie nuestro programa a dicho socket. Se consigue mediante la función bind(). 
    // El sistema todavía no atenderá a las conexiones de clientes, simplemente anota que cuando empiece a hacerlo, tendrá que avisarnos a nosotros. 
    // Es en esta llamada cuando se debe indicar el número de servicio al que se quiere atender.

    int bindStatus = bind(sockfd, res->ai_addr, res->ai_addrlen);

    if (bindStatus < 0) {
        fprintf(stderr,"Error: %s\n", gai_strerror(bindStatus));
        return 2;
    }

    // 3. Pedir y aceptar las conexiones de clientes al sistema operativo. 
    // Para ello hacemos una llamada a la función accept(). 
    // Esta función le indica al sistema operativo que nos dé al siguiente cliente de la cola. 
    // Si no hay clientes se quedará bloqueada hasta que algún cliente se conecte.

    listen(sockfd, BACKLOG);
    printf("Listening...\n");

    socklen_t addr_size = sizeof(their_addr);
    int new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
    
    // 4. Escribir y recibir datos del cliente, por medio de las funciones send() y recv(), 
    // que son exactamente las mismas que usamos para escribir o leer de un fichero. 
    // Obviamente, tanto cliente como servidor deben saber qué datos esperan recibir, qué datos deben enviar y en qué formato. 
    // Puedes ver cómo se pueden poner de acuerdo en estos mensajes en el apartado de mensajes.

    char msg[MAX_BUFF_LENGTH], buff[MAX_BUFF_LENGTH];
    int receivedBytes, i = 0, sentBytes;

    while(1){
        memset(msg, 0, sizeof(buff));

        receivedBytes = recv(sockfd, buff, MAX_BUFF_LENGTH, 0);
        char *serverResponse;
        if( !strcmp(buff, "Hola rey") ){
            strcpy(serverResponse, "230");
        } else if ( !strcmp(buff, "quit") ){
            strcpy(serverResponse,"221");
        } else {
            strcpy(serverResponse, "");
        }

        if (receivedBytes < 0) {
            fprintf(stderr,"Error: %s\n", gai_strerror(receivedBytes));
            return -1;
        }
    
        printf("Client message: %s", buff);

        if( i == 0){
            sentBytes = send(sockfd, serverResponse,strlen(serverResponse),0);
            
            if(loginUsername("db.txt", buff))
                i++; 
        } else if(i == 1){
            
        }

    }


    // 5. Cierre de la comunicación y del socket, por medio de la función close(), que es la misma que sirve para cerrar un fichero.

    
    
    return 0;
}