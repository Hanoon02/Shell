#include <stdio.h>
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
    int num;
    FILE *file;
    if(length==3){
        if(argument[0] == 'w'){
            char input[10000];
            file = fopen(filename,"w");
            if(file == NULL){
                printf("Error!");   
                exit(1);             
            }
            scanf("%[^\n]", input);
            fputs(input, file);
        }
        if(argument[0] =='-' && argument[1]=='n'){
            if ((file = fopen(filename,"r")) == NULL){
                printf("Error! opening file");
                exit(1);
            }
            char read = fgetc(file);
            int line = 1;
            printf("%d) ",line);
            while (read != EOF)
            {
                if(read=='\n'){
                    line++;
                    printf("\n%d) ",line);
                }
                else{
                    printf("%c",read);
                }
                read = fgetc(file);
            }
        }
        else if(argument[0] == '-' && argument[1] == 'e'){
            if ((file = fopen(filename,"r")) == NULL){
                printf("Error! opening file");
                exit(1);
            }
            char read = fgetc(file);
            while (read != EOF)
            {
                if(read=='\n'){
                    printf("$\n");
                }
                else{
                    printf("%c",read);
                }
                read = fgetc(file);
            }
            printf("$");
        }
    }
    else if(length==2){
        if ((file = fopen(argument,"r")) == NULL){
            printf("Error! opening file");
            exit(1);
        }
        char read = fgetc(file);
        while (read != EOF)
        {
            printf ("%c", read);
            read = fgetc(file);
        }
    }
    else if(length==1){
        printf("Incorrect/Unsupported Command\n");
    }
    fclose(file);
    return 0;
}