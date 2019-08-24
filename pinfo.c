#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include "pinfo.h"

void getPinfo(char * tok){

    char i[100];
    int flag = 0;

    while((tok = strtok(NULL," ")) != NULL){
        flag = 1;
        if(tok[strlen(tok)-1] == '\n'){tok[strlen(tok)-1] = '\0';}
        strcpy(i,tok);
    }

    char path[100];

    if(!flag){
        printf("PID: %d\n",getpid());
        sprintf(i,"%d",(int)getpid());
    } else {
        printf("PID: %s\n",i);
    }

    
    strcpy(path,"/proc/");
    strcat(path,i);
    strcat(path,"/status");

    char procstat[100];

    FILE * fp = fopen(path,"r");

    char *tok1 = (char *)malloc(100*sizeof(char));
    tok1 = strtok(procstat," ");   

    int c=0;
    
    char status[100];
    char mem[100];

    while(fgets(tok1,50,fp) != NULL){
        if(c == 2){
            strcpy(status,tok1);
        } else if(c == 17){ 
            strcpy(mem,tok1);
        }
        c++;
    }
    printf("%s%s",status,mem);

    fclose(fp);

    strcpy(path,"/proc/");
    strcat(path,i);
    strcat(path,"/exe");
    
    char execpath[100];

    int s = readlink(path,execpath,sizeof(execpath));
    execpath[s] = '\0';

    printf("Executable path: %s\n",execpath);
    
    fclose(fp);



}
