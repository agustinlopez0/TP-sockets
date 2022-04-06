#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


#include "sockets.h"

int main(int argc, char* argv[]){
    
    int s;
    
    struct addrinfo hints, *res;
    
    // argvv[1] es el numero de puerto
    getaddrinfo(NULL, argv[1], &hints, &res);




    s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    
    return 0;
}