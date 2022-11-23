#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
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
        if(argument[0]=='-' && argument[1]=='u'){
            time_t utc;
            struct tm* _time;
            time(&utc);
            _time = gmtime(&utc);
            printf("%2d %2d %2d:%2d:%2d UTC %4d\n", _time->tm_mday, _time->tm_mon + 1,(_time->tm_hour)%24, _time->tm_min, _time->tm_sec,_time->tm_year + 1900);
        }
        else{
        printf("Incorrect/Unsupported Command\n");
        }
    }
    else if(length==3){
        if(argument[0]=='-' && argument[1]=='r'){
            struct stat attr;
            stat(filename, &attr);
            if(ctime(&attr.st_mtime)==NULL){
                printf("Error! File not found\n");
            }
            else{
                printf("Last modified time: %s", ctime(&attr.st_mtime));
            }
        }
        else{
        printf("Incorrect/Unsupported Command\n");
        }
    }
    else if(length==1){
        time_t T = time(NULL);
        struct tm time = *localtime(&T);
        printf("%2d %2d %2d:%2d:%2d IST %4d\n", time.tm_mday, time.tm_mon + 1,time.tm_hour, time.tm_min, time.tm_sec,time.tm_year + 1900);
    }
    else{
        printf("Incorrect/Unsupported Command\n");
    }
    return 0;
}