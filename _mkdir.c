#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[]){
    int length = 0;
    char argument[100], filename[100];    
    char *copy = (char*)malloc(1000);
    if(argc==1) strcpy(copy, *argv);
    else{
        int i=0;
        strcpy(copy, argv[i]);
        strcat(copy, " ");
        while(argc-2>0){
            i++;
            strcat(copy, argv[i]);
            strcat(copy, " ");
            argc--;
        }
    }
    char * token = strtok(copy, " ");
    while (token != NULL){
        length++;
        if(length==2) strcpy(argument, token);
        if(length==3) strcpy(filename, token);
        token = strtok(NULL, " ");
    }
    if(length==2){
        if(mkdir(argument, 0700)!=0) printf("Error! Directory not created\n");
    }
    else if(length>=3){
        if(argument[0]=='-'){
            if(argument[1] == 'v'){
                if(mkdir(filename, 0700)!=0) printf("Error! Directory not created\n");
                else printf("mkdir: created directory '%s'\n", filename);
            }
            else if(argument[1] == 'p'){
                char parentFile[1000] = "";
                token = strtok(filename, "/");
                while (token != NULL){
                    strcat(parentFile, token);
                    mkdir(parentFile, 0700);
                    strcat(parentFile, "/");
                    token = strtok(NULL, " ");
                }
            }
        }
    }
    else if(length==1){
        printf("Please enter a name for directory\n");
    }
}