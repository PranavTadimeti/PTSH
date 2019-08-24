#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<linux/limits.h>
#include<string.h>
#include<fcntl.h>
#include "history.h"

void printHistory(int c){

    FILE * fp = fopen("hist.txt","r");
    char cmd[100];

    while(fgets(cmd,100,fp) != NULL){
        printf("%s",cmd);   
    }
    return;
}

void writeHistory(char * cmd){
    FILE * fp = fopen("hist.txt", "a");
    cmd[strlen(cmd)-1] = '\0';
    fwrite(cmd,1,100,fp);
    fclose(fp);
}