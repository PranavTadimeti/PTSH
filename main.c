#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<linux/limits.h>
#include<string.h>
#include "prompt.h"
#include "cd.h"
#include "utils.h"
#include "ls.h"

void runShell(){
    char * buf;
    char * buf2;
    char * tok;
    char home[PATH_MAX];

    buf = (char *)malloc(4096*sizeof(char));
    buf2 = (char *)malloc(4096*sizeof(char));
 
    size_t s=0;

    getcwd(home, sizeof(home));

    while(1){
        makePrompt(home);

        int i = getline(&buf,&s,stdin);
        if(i == -1){exit(0);}
        strcpy(buf2,buf);

        tok = strtok(buf," ");

        if(strcmp(tok,"cd") == 0){
            changeDir(buf,tok,home);
        } else if(strcmp(tok,"pwd\n") == 0 || strcmp(tok,"pwd") == 0 || strcmp(tok,"echo") == 0){
            util(tok,buf2);
        } else if(strcmp(tok,"ls") == 0 || strcmp(tok,"ls\n") == 0){
            printDir(tok);
        }

    }
}

int main(){
    runShell();
}
