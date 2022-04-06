#include "sockets.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int loginUsername(char *file, char* user){

    FILE* fp = fopen(file, "r");

    char* delim = ":";
    char buff[255];
    
    fscanf(fp,"%[^\n]", buff);

    fclose(fp);

    if( !strcmp(user,buff) )
        return 0;
    
    return 1;
}