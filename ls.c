#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>  
#include<dirent.h>
#include<linux/limits.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include "ls.h"

int filter(const struct dirent *d){
    if(d->d_name[0] == '.'){
        return 0;
    }
    return 1;
}

void checkPerm(char * path){
    struct stat s;
    stat(path,&s);

    if(stat(path,&s) == 0){

        //User

        if(S_ISREG(s.st_mode)){printf("-");}
        else{printf("d");}
        
        if(s.st_mode & S_IRUSR ){printf("r");} 
        else {printf("-");}

        if(s.st_mode & S_IWUSR ){printf("w");} 
        else {printf("-");} }

        if(s.st_mode & S_IXUSR ){printf("x");} 
        else {printf("-");}  

        //Group

        if(s.st_mode & S_IRGRP ){printf("r");} 
        else {printf("-");}

        if(s.st_mode & S_IWGRP ){printf("w");} 
        else {printf("-");} 

        if(s.st_mode & S_IXGRP ){printf("x");} 
        else {printf("-");} 

        //Others

        if(s.st_mode & S_IROTH ){printf("r");} 
        else {printf("-");}

        if(s.st_mode & S_IWOTH ){printf("w");} 
        else {printf("-");} 

        if(s.st_mode & S_IXOTH ){printf("x");} 
        else {printf("-");} 

        printf("\t%d\t",(int)s.st_nlink);

        char * p = getpwuid(s.st_uid)->pw_name;
        char * g = getgrgid(s.st_gid)->gr_name; 

        printf("%s\t%s\t",p,g);
        printf("%ld\t",s.st_size);


        time_t t;
        struct tm * tmp;
        char tim[100];

        time(&t);
        tmp = localtime(&s.st_ctime);


        strftime(tim,100,"%b\t%d\t%H:%M",tmp);

        printf("%s\t",tim);


}


void printDir(char * tok,char * home){
    struct dirent **namelist;
    int n;
    int aflag=0;
    int lflag=0; 
    int dirpres = 0;

    char * dir = (char *)malloc(100*sizeof(char));

    while((tok = strtok(NULL," ")) != NULL){

        if(tok[0] == '-'){
            if(tok[1] == 'a'){
                aflag = 1;
                if(tok[2] != '\0'){
                    if(tok[2] == 'l'){lflag = 1;}
                }
            }
            else if(tok[1] == 'l'){
                lflag = 1;
                if(tok[2] != '\0'){
                    if(tok[2] == 'a'){aflag = 1;}
                }
            }
        } else {
            dirpres = 1;
            if(tok[0] == '~'){
                tok[strlen(tok)-1]='\0';
                strcpy(dir,home);
                strcat(dir,++tok);
                continue;
            } else {
                if(tok[strlen(tok)-1] == '\n'){
                    tok[strlen(tok)-1] = '\0';
                }
                strcpy(dir,tok);
            }
        } 
        tok[strlen(tok)-1] = '\0';
    }

    if(!dirpres){dir = ".";}
    
    n = scandir(dir,&namelist,filter,alphasort);
    if(aflag){n = scandir(dir,&namelist,NULL,alphasort);}
    
    if(lflag){
        if(dirpres){

            for(int i=0;i<n;i++){
                char * temp = (char *)malloc(100*sizeof(char));
                strcpy(temp,dir);
                strcat(temp,"/");
                strcat(temp,namelist[i]->d_name);
                checkPerm(temp);
                printf("%s\n",namelist[i]->d_name);
            }
            
        } else {
            for(int i=0;i<n;i++){
                checkPerm(namelist[i]->d_name);
                printf("%s\n",namelist[i]->d_name);
            }
        }
        return;
    }

    for(int i=0;i<n;i++) {
        printf("%s\n", namelist[i]->d_name);
        free(namelist[i]);
    }
   
}