#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdbool.h>
#include<termios.h>
#include <sys/ioctl.h>
#include<time.h>
#include "nwatch.h"

bool keyDown() {
    struct termios oldt, newt;
    int bytes;

    tcgetattr(STDIN_FILENO, &oldt);

    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ioctl(STDIN_FILENO, FIONREAD, &bytes);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return bytes > 0;
}

void nwatch(char * tok){
    int flag = 0;
    tok = strtok(NULL," ");
    int c=0;
    char * w = (char *)malloc(100*sizeof(char));

    while(tok != NULL){
        if(c == 1){
            strcpy(w,tok);
        } else if(c == 2){
                if(tok[strlen(tok)-1] == '\n'){tok[strlen(tok)-1]='\0';}
                if(strcmp("dirty",tok) == 0){flag = 1;}
        }
        c++;
        tok = strtok(NULL," ");
    }

    if(flag){
        
        char * p = "/proc/meminfo";
        char * data = (char *)malloc(1000*sizeof(char));
        char * tok = (char *)malloc(100*sizeof(char));

        time_t t;
        
        while(1){
            t = clock();
            FILE * fp = fopen(p,"r");
            while(fgets(data,100,fp) != NULL){
                tok = strtok(data," ");
                if(strcmp(tok,"Dirty:") == 0){
                    tok = strtok(NULL," ");
                    if(tok[strlen(tok)-1] == '\n'){tok[strlen(tok)-1] = '\0';}
                    printf("%s kB\n",tok);
                }
            }
            
            while(((clock()-t)/CLOCKS_PER_SEC) < atoi(w)){
                if(keyDown()){
                    
                    if(getchar() == 'q'){
                        return;
                    }
                }
            }
        }
        
    } else {
        char * p = "/proc/interrupts";
        char * data = (char *)malloc(1000*sizeof(char));

        time_t t;

        while(1){   
            t = clock();
            FILE * fp = fopen(p,"r");
            int c=0;
            while(fgets(data,100,fp) != NULL){
                if(c == 0 || c == 2){
                    printf("%s",data);
                }
                c++;
            }

            while(((clock()-t)/CLOCKS_PER_SEC) < atoi(w)){
                if(keyDown()){
                    
                    if(getchar() == 'q'){
                        return;
                    }
                }
            }

            
            
        }
    }
}