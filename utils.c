#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>  
#include<linux/limits.h>
#include "utils.h"

void util(char * tok,char * buf2){
    if(strcmp(tok,"echo") == 0){

        char * temp = (char *)malloc(100*sizeof(char));
        tok = strtok(NULL," ");
        
        while(tok != NULL){
            strcat(temp,tok);
            strcat(temp," ");
            tok = strtok(NULL," ");
        }

        if(temp[strlen(temp)-2] == '\n'){
            temp[strlen(temp)-2] = '\0';
        }
        printf("%s\n",temp);

    } else {
        char pwd[PATH_MAX];
        getcwd(pwd,sizeof(pwd));
        printf("%s\n",pwd);
    }
}