#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>  
#include<linux/limits.h>
#include "cd.h"

void changeDir(char * buf3,char * tok,char * home){
    do {
        tok = strtok(NULL," ");
    } while(strcmp(tok,"cd") == 0);

    tok[strlen(tok)-1] = '\0';

    if(strcmp(tok,"~") == 0){
        chdir(home);
    } else {
        chdir(tok);
    }
}