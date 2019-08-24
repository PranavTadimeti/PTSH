#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<linux/limits.h>
#include<string.h>
#include "history.h"

void printHistory(int c){

    FILE * fp = fopen("hist.txt","r");
    char cmd[100];

    while(fgets(cmd,sizeof(cmd),fp) != NULL){
        printf("%s",cmd);
    }

    return;
}

void writeHistory(char * cmd){
    FILE * fp = fopen("hist.txt","w");
    
}