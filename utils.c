#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>  
#include<linux/limits.h>
#include "utils.h"

void util(char * tok,char * buf2){
    if(strcmp(tok,"echo") == 0){

        char * temp = (char *)malloc(1000*sizeof(char));
        tok = strtok(NULL," ");
        strcpy(temp,tok);
        while((tok = strtok(NULL," ")) != NULL){
            strcat(temp," ");
            strcat(temp,tok);
        }
        if(tok[strlen(tok)-1] == '\n'){tok[strlen(tok)-1] = '\0';}
        printf("%s\n",temp);

    } else {
        char pwd[PATH_MAX];
        getcwd(pwd,sizeof(pwd));
        printf("%s\n",pwd);
    }
}