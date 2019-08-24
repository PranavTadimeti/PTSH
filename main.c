#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<linux/limits.h>
#include<string.h>
#include<signal.h>
#include<wait.h>
#include<fcntl.h>
#include "prompt.h"
#include "cd.h"
#include "utils.h"
#include "ls.h"
#include "pinfo.h"
#include "exec.h"
#include "history.h"
#include "nwatch.h"

void runShell(){
    char * buf;
    char * buf2;
    char * tok;
    char home[PATH_MAX];

    buf = (char *)malloc(4096*sizeof(char));
    buf2 = (char *)malloc(4096*sizeof(char));
 
    size_t s=0;

    getcwd(home, sizeof(home));

    char * histp = (char *)malloc(100*sizeof(char));
    strcpy(histp,home);
    strcat(histp,"/hist.txt");
    int fd = open(histp, O_WRONLY | O_CREAT,0700);
    close(fd);

    int curr=0;
    char *h[25];

    for(int i=0;i<25;i++){h[i] = NULL;}

    while(1){
        makePrompt(home);

        int i = getline(&buf,&s,stdin);
        if(i == -1){exit(0);}
        strcpy(buf2,buf);

        char * t;
        t = strtok(buf,";");

        char toks[10][100];
        int c=0;

        while(t != NULL){
            strcpy(toks[c],t);
            t = strtok(NULL,";");
            c++;
        }

        char **argv = (char **)malloc(100*sizeof(char *));

        for(int i=0;i<100;i++){argv[i] = (char *)malloc(100*sizeof(char));}

        for(int i=0;i<c;i++){
            
            tok = strtok(toks[i]," ");
            //if(tok[strlen(tok)-1] == '\n'){tok[strlen(tok)-1] = '\0';}

            if(strcmp(tok,"cd") == 0 || strcmp(tok,"cd\n") == 0){changeDir(tok,home);}

            else if(strcmp(tok,"pwd\n") == 0 || strcmp(tok,"pwd") == 0 || strcmp(tok,"echo") == 0){util(tok,buf2);}
            else if(strcmp(tok,"ls") == 0 || strcmp(tok,"ls\n") == 0){printDir(tok,home);} 
            else if(strcmp(tok,"pinfo\n") == 0 || strcmp(tok,"pinfo") == 0){getPinfo(tok);}
            else if(strcmp(tok,"exit") == 0 || strcmp(tok,"exit\n") == 0){return;} 
            else if(strcmp(tok,"history") == 0 || strcmp(tok,"history\n") == 0){printHistory(curr);}
            else if(strcmp(tok,"nightswatch") == 0){nwatch(tok);}
            
            else {
                if(tok[strlen(tok)-1] == '\n'){tok[strlen(tok)-1] = '\0';}
                strcpy(argv[0],tok);
                execProc(argv,tok);
            }
            if(i != c-1){printf("\n");}

        }

        //curr = (curr+1)%20;

    }
}

int main(){
    signal(SIGCHLD,endProc);
    runShell();
}
