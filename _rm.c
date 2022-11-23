#include<stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
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
        if(argument[0]=='a' && argument[1]=='l' && argument[2]=='l'){
            struct dirent *file;
            DIR *directory = opendir(".");
            if (!directory)
            {
                exit(EXIT_FAILURE);
            }
            while ((file = readdir(directory)) != NULL)
            {
                if (!0 && file->d_name[0] == '.')
                    continue;
                if(strcmp(file->d_name, "_rm.c")==0 || strcmp(file->d_name, "_ls.c")==0 || strcmp(file->d_name, "shell.c")==0 || strcmp(file->d_name, "_date.c")==0 || strcmp(file->d_name, "_mkdir.c")==0 || strcmp(file->d_name, "_cat.c")==0 || strcmp(file->d_name, "documentation.txt")==0|| strcmp(file->d_name, "Makefile")==0) continue;
                if (remove(file->d_name) == 0)
                    printf("rm: deleted successfully\n");
                else
                    printf("rm: unable to delete the file\n");
            }
        }
        else{
            if (remove(argument) == 0)
                printf("rm: deleted successfully");
            else
                printf("rm: unable to delete the file");
        }
    }
    else if(length==3){
        if(argument[0]=='-' && argument[1]=='f'){
            remove(filename);
            printf("rm: deleted successfully");
        }
        else if(argument[0]=='-' && argument[1]=='i'){
            char check[100];
            printf("remove %s? ", filename);
            scanf("%[^\n]s",check);
            if(strcmp(check, "yes")==0) remove(filename);
        }
    }
    else{
        printf("Incorrect Command");
    }
    return 0;
}