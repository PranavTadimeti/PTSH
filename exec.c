#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<fcntl.h>
#include<wait.h>
#include<signal.h>
#include<linux/limits.h>
#include "exec.h"
#include "prompt.h"

void endProc(){
    int wstatus=0;
    pid_t pid;
    pid = waitpid(-1,&wstatus,WNOHANG); 
    if (pid>0){
        if(WIFEXITED(wstatus)){
            if(WEXITSTATUS(wstatus) == EXIT_SUCCESS){
                printf("Process with pid %d ended normally.\n",pid);
            } else {
                printf("Process with pid %d ended abnormally.\n",pid);
            }
        } else {
            printf("Process with pid %d ended abnormally.\n",pid);
        }
        char home[PATH_MAX];
        getcwd(home,sizeof(home));
        makePrompt(home);
        fflush(stdout);
    }

}

void execProc(char * argv[],char * tok){
    int flag = 0;
    int cnt = 1;
    tok = strtok(NULL," ");
    while(tok != NULL){
        if(tok[strlen(tok)-1] == '\n'){tok[strlen(tok)-1] = '\0';}
        strcpy(argv[cnt],tok);
        if(strcmp("&",argv[cnt]) == 0){flag = 1;}
        cnt++;
        tok = strtok(NULL," ");
    }

    argv[cnt] = NULL;
    
    int status = 0;
    pid_t cpid;

    if(flag){
        cpid = fork();
        if(cpid == 0){
            execvp(argv[0],argv);
        }

    } else {

        cpid = fork();
        if(cpid == 0){
            printf("%s\n",argv[0]);
            execvp(argv[0],argv);
        } else {
            do {
                wait(&status);
            } while(!WIFEXITED(status));
        }

    }
}