#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>  
#include<linux/limits.h>
#include "cd.h"

void changeDir(char * tok,char * home){

    int dirpres=0;
    char * dir = (char *)malloc(100*sizeof(char));
    
    while((tok = strtok(NULL," ")) != NULL){
        dirpres = 1;
        if(tok[strlen(tok)-1] == '\n'){tok[strlen(tok)-1] = '\0';}
        strcpy(dir,tok);
    }


    if(strcmp(dir,"~") == 0 || dirpres == 0){
        chdir(home);
    } else {
        chdir(dir);
    }
}