#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<fcntl.h>
#include "exec.h"

void execProc(char * argv[],char * tok){

    int cnt = 1;
    tok = strtok(NULL," ");
    while(tok != NULL){
        if(tok[strlen(tok)-1] == '\n'){tok[strlen(tok)-1] = '\0';}
        strcpy(argv[cnt],tok);
        cnt++;
        tok = strtok(NULL," ");
    }

    argv[cnt] = NULL;
    //execvp(argv[0],argv);

    int status = 0;
    pid_t wpid,cpid;

    cpid = fork();
    if(cpid == 0){
        execvp(argv[0],argv);
    } else {
        do {
            pid_t ppid = wait(&status);
        } while(!WIFEXITED(status));
    }

    if (WEXITSTATUS(status)){
        printf("Exited Normally\n");
    }
}