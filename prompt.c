#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<linux/limits.h>
#include<string.h>
#include "prompt.h"

void makePrompt(char * home){
    //char home[PATH_MAX];
    //getcwd(home,sizeof(home));
    //printf("%s\n",home);

    char * buf1;
    char * buf2;
    char cwd[PATH_MAX];

    // Getting the username,hostname and filepath of the directory the shell is present in.

    buf1 = (char *)malloc(1000*sizeof(char));
    buf2 = (char *)malloc(_SC_HOST_NAME_MAX*sizeof(char));

    buf1 = getlogin();
    gethostname(buf2,_SC_HOST_NAME_MAX);

    // Takes input from user and parses it.
    // Depending on input given, different commands are executed.

    char temp[PATH_MAX] = "~";
    char temp2[PATH_MAX];
    getcwd(cwd, sizeof(cwd));

    if(strlen(cwd) < strlen(home) || strncmp(home,cwd,strlen(home)) != 0){
        printf("\033[1;36m"); 
        printf("=>%s@%s:%s > ",buf1,buf2,cwd);
        printf("\033[0m");
    } else {
        strncpy(temp2,cwd+strlen(home),strlen(home));
        strcat(temp,temp2);
        printf("\033[1;36m");
        printf("=>%s@%s:%s > ",buf1,buf2,temp);
        printf("\033[0m");
    }
}
