#include "sockets.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int loginUsername(char *file, char* user){

    if( strcmp("schujman", user) == 0 ){
        return 1;
    }

    return 0;
}

int loginPassword(char *file, char* pass){

    if( strcmp("contrasena", pass) == 0 ){
        return 1;
    }

    return 0;
}
// int loginUsername(char *file, char* user){

//     FILE* fp = fopen(file, "r");

//     char* delim = ":";
//     char buff[255];
    
//     fscanf(fp,"%[^\n]", buff);


//     if( !strcmp(user,buff) )
//         return 0;
    
//     fclose(fp);
//     return 1;
// }