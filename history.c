#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<linux/limits.h>
#include<string.h>
#include "history.h"

void history(char *h[],int c){
    int t = c;

    do {
        if(h[t]){
            printf("%s\n",h[t]);
        }

        t = (t+1)%20;
    } while(t != c);

    return;
}