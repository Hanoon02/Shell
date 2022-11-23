#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, const char *argv[])
{
    int length = 0;
    char str[100];    
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
    char * splitWord = strtok(copy, " ");
    while (splitWord != NULL){
        length++;
        if(length==2) strcpy(str, splitWord);
        splitWord = strtok(NULL, " ");
    }
    if(length==1) {
        struct dirent *file;
        DIR *directory = opendir(".");
        if (!directory)
        {
            if (errno == ENOENT)
            {
                perror("Directory doesn't exist");
            }
            else
            {
                perror("Unable to read directory");
            }
            exit(EXIT_FAILURE);
        }
        while ((file = readdir(directory)) != NULL)
        {
            if (file->d_name[0] == '.') continue;
            printf("%s  ", file->d_name);
        }
        printf("\n");
    }
    else if(length==2){
        if(str[0]=='-' && str[1]=='l'){
            struct dirent *file;
            struct stat attr;
            DIR *directory = opendir(".");
            if (!directory)
            {
                if (errno == ENOENT)
                {
                    perror("Directory doesn't exist");
                }
                else
                {
                    perror("Unable to read directory");
                }
                exit(EXIT_FAILURE);
            }
            while ((file = readdir(directory)) != NULL)
            {
                struct stat fileInfo;
                stat(file->d_name, &fileInfo);
                struct passwd *pw;
                struct group  *gr;
                pw = getpwuid(fileInfo.st_uid);
                gr = getgrgid(fileInfo.st_gid);
                FILE* pointer = fopen(file->d_name, "r");
                if (pointer == NULL) {
                    printf("File Not Found!\n");
                }
                fseek(pointer, 0L, SEEK_END);
                long long int res = ftell(pointer);
                fclose(pointer);
                stat(file->d_name, &attr);
                if (file->d_name[0] == '.')
                    continue;
                char *line;
                line = strtok(ctime(&attr.st_mtime), "\n");
                printf("%s %s %s %8lld %s\n", pw->pw_name, gr->gr_name, line, res, file->d_name);
            }
        }
        else if(str[0]=='-' && str[1]=='a'){
            struct dirent *file;
            DIR *directory = opendir(".");
            if (!directory)
            {
                if (errno == ENOENT)
                {
                    perror("Directory doesn't exist");
                }
                else
                {
                    perror("Unable to read directory");
                }
                exit(EXIT_FAILURE);
            }
            while ((file = readdir(directory)) != NULL)
            {
                printf("%s  ", file->d_name);
            }
            printf("\n");
        }
        else{
            printf("Incorrect/Unsupported Command\n");
        }
        splitWord = strtok(NULL, " ");
    }
    else{
        printf("Incorrect/Unsupported Command\n");
    }
	return 0;
}