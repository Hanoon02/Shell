#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <sys/wait.h>
#include <pthread.h>
#include <dirent.h>
#include <errno.h>
#include <pwd.h>
#include <limits.h>
#include <string.h>
#include <limits.h>
char globalPath[1000];
int newLine = 0;

void cd(char *input){
    char c, s[100], str[100];
    scanf("%c", &c);
    int i=0, check =0;
    char * splitWord = strtok(input, " ");
    while (splitWord != NULL)
    {
        i++;
        strcpy(str, splitWord);
        if(i==2){
            if(str[0]=='.' && str[1]=='.'){
                check=1;
                i++;
                if(chdir("..") !=0){
                    check = 0;
                    printf("Error cannot find directory\n");
                }
                break;
            }
            else if(str[0]=='~'){
                check=1;
                i++;
                struct passwd *pw = getpwuid(getuid());
                const char *homeDirectory = pw->pw_dir;
                if(chdir(homeDirectory) !=0){
                    printf("Error cannot find directory\n");
                    check = 0;
                }
                break;
            }
            else if(str[0]=='-' && str[1]=='L'){
                check=1;
                i++;
                splitWord = strtok(NULL, " ");
                strcpy(str, splitWord);
                if(chdir(str) !=0){
                    check = 0;
                    printf("Error cannot find directory\n");
                }
                break;
            }
            else if(str[0]=='-' && str[1]=='O'){
                check=1;
                i++;
                if(chdir(globalPath) !=0){
                    check = 0;
                    printf("Cannot move to shell\n");
                }
                break;
            }
        }
        splitWord = strtok(NULL, " ");
    }
    if(i==2){
        check=1;
        if(chdir(str) !=0){
            check = 0;
            printf("Error cannot find directory\n");
        }
        
    }
    if(check==0) printf("Incorrect/Unsupported Commands Entered\n");
}
void echo(char *input){
    int strlength = 0;
    char str[1000], firstWord[1000], lastWord[1000], rest[1000];
    strcpy(str, "");
    char * splitWord = strtok(input, " ");
    while(splitWord!=NULL){
        strlength++;
        if(strlength>=2){
            strcat(str, splitWord);
            strcat(str, " ");
        }
        splitWord = strtok(NULL, " ");
    }
    int length=0;
    splitWord = strtok(str, " ");
    strcpy(rest, "");
    while(splitWord!=NULL){
        length++;
        if(length==1) strcpy(firstWord, splitWord);
        else if(length!=strlength-1){
            strcat(rest, splitWord);
            strcat(rest, " ");
        }
        if(length==strlength-1) strcpy(lastWord, splitWord);
        splitWord = strtok(NULL, " ");
    }
    if(firstWord[0]=='a' && firstWord[1]=='l' && firstWord[2]=='l'){
        struct dirent *file;
        DIR *directory = opendir(".");
        if (!directory)
        {
            printf("Directory doesn't exist");
            exit(EXIT_FAILURE);
        }
        while ((file = readdir(directory)) != NULL)
        {
            if (!0 && file->d_name[0] == '.') continue;
            printf("%s  ", file->d_name);
        }
        printf("\n");
    }
    else if(strcmp(firstWord,"--help")==0){
        FILE *file;
        char echo_man[1000];
        strcpy(echo_man, "");
        strcat(echo_man,globalPath);
        strcat(echo_man, "/echo_man.txt");
        if ((file = fopen(echo_man,"r")) == NULL){
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
    else{
        if(firstWord[0]!='-' && firstWord[1]!='n'){
            int stringPresent = 0;
            if(firstWord[0]=='"') stringPresent = 1;
            if(stringPresent==1 && lastWord[strlen(lastWord)-1]=='"'){
                if(strlength==2) {
                    for(int i =1; i<strlen(firstWord)-1; i++) printf("%c", firstWord[i]);
                    printf("\n");
                }
                else{
                    lastWord[strlen(lastWord)-1] = '\0';
                    for(int i =1; i<strlen(firstWord); i++) printf("%c", firstWord[i]);
                    printf(" %s%s\n", rest, lastWord);
                }
            }
            else if(stringPresent==1 && lastWord[strlen(lastWord)-1]!='"'){
                printf("Error: Add double quote on both ends of string\n");
            }
            else if(stringPresent==0){
                if(strlength==2) printf("%s\n", firstWord);
                else printf("%s %s%s\n",firstWord, rest, lastWord);
            }
        }
        else{
            if(str[0]=='-' && str[1]=='n'){
                newLine =1;
                int stringPresent = 0;
                if(strlength==3 && lastWord[0]=='"') stringPresent = 1;
                else if(rest[0]=='"') stringPresent = 1;
                if(stringPresent==1 && lastWord[strlen(lastWord)-1]=='"'){
                    if(strlength==3) for(int i =1; i<strlen(lastWord)-1; i++) printf("%c", lastWord[i]);
                    else{
                        lastWord[strlen(lastWord)-1] = '\0';
                        for(int i =1; i<strlen(rest); i++) printf("%c", rest[i]);
                        printf("%s", lastWord);
                    }
                }
                else if(stringPresent==1 && lastWord[strlen(lastWord)-1]!='"'){
                    printf("Error: Add double quote on both ends of string\n");
                }
                else if(stringPresent==0){
                    if(strlength==3) printf("%s", lastWord);
                    else {
                        for(int i=0; i<strlen(rest); i++) printf("%c", rest[i]);
                        printf("%s", lastWord);
                    }
                }
            }
            else{
                printf("Incorrect/Unsupported Command\n");
            }
        }
    }
}
void pwd(char *input){
    int length = 0;
    char argument[1000], directory[1000];
    char * splitWord = strtok(input, " ");
    while(splitWord!=NULL){
        length++;
        if(length == 2) strcpy(argument,splitWord);
        splitWord = strtok(NULL, " ");
    }
    if(length==1){
        if(getenv("PWD") == NULL){
            printf("Cannot find path to directory\n");
            return;
        }
        printf("%s\n", getenv("PWD"));
        return;
    }
    else if(length==2){
        if(argument[0]=='-' && argument[1]=='L'){
            if(getenv("PWD") == NULL){
                printf("Cannot find path to directory\n");
                return;
            }
            printf("%s\n", getenv("PWD"));
            return;
        }
        else if(argument[0]=='-' && argument[1]=='P') {
            printf("%s\n", getcwd(directory, 1000));
            return;
        }
    }
    if(length==2) printf("Incorrect/Unsupported PWD subcommand\n");
    else printf("Incorrect PWD Command\n");
}
void externalCommands(int n, char *input){
    char currentDirectory[1000];
    strcpy(currentDirectory, globalPath);
    int f = fork();
    if(f==0){
        if (n==1) {
            strcat(currentDirectory, "/_ls");
            execl(currentDirectory, input, NULL);
        }
        else if(n==2) {
            strcat(currentDirectory, "/_cat");
            execl(currentDirectory, input,NULL);
        }
        else if(n==3) {
            strcat(currentDirectory, "/_date");
            execl(currentDirectory, input, NULL);
        }
        else if(n==4) {
            strcat(currentDirectory, "/_rm");
            execl(currentDirectory, input, NULL);
        }
        else if(n==5) {
            strcat(currentDirectory, "/_mkdir");
            execl(currentDirectory, input, NULL);
        }
    }
    else if (f != 0) {
        wait(NULL);
    }
}
void *externalThreading(void *args)
{
    char *input = (char *)args;
    system(input);
    return NULL;
}
void threading(char *input){
    char *command = (char *)malloc(sizeof(char)*1000);
    strcpy(command, "");
    strcat(command, "./_");
    strcat(command, input);
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, externalThreading, (void *)command);
    pthread_join(thread_id, NULL);
}
void printInfo(){
    char location[1000];
    strcpy(location, globalPath);
    strcat(location, "/documentation.txt");
    printf("Sus-Shell Commands and Flags Handled:-\n");
    FILE *file;
    if ((file = fopen(location,"r")) == NULL){
        printf("Error! opening file");
        exit(1);
    }
    char read = fgetc(file);
    int line = 1;
    while (read != EOF)
    {
        if(read=='\n'){
            line++;
            if(line>=25)printf("\n");
        }
        else{
            if(line>=25) printf("%c",read);
        }
        read = fgetc(file);
    }
}
int main()
{   
    getcwd(globalPath, 1000);
    char str[1000], firstCommand[1000], lastCommand[1000], cleanCommand[1000], none;
    printf("Welcome to Sus-Shell\n");
    printf("Type 'info' to view documentation\n");
    printf("Type 'exit' to exit the shell\n");
    printf("\nsus$> ");
    scanf("%[^\n]s",str);
    while(strcmp(str, "exit")!=0){
        char *copy = (char*)malloc(1000);
        strcpy(copy, str);
        char * token = strtok(copy, " ");
        strcpy(firstCommand, token);
        strcpy(cleanCommand,"");
        while (token != NULL){
            strcpy(lastCommand, token);
            if(strcmp(token, "&t")!=0) {
                strcat(cleanCommand,token);
                strcat(cleanCommand," ");
            }
            token = strtok(NULL, " ");
        }
        if(strcmp(firstCommand, "info")==0) {
            printInfo();
            scanf("%c", &str[0]);
        }
        else if(strcmp(firstCommand, "cd")==0) cd(str);
        else if(strcmp(firstCommand, "echo")==0) {
            echo(str);
            scanf("%c", &str[0]);
        }
        else if(strcmp(firstCommand, "pwd")==0) {
            pwd(str);
            scanf("%c", &str[0]);
        }
        else {
            if(strcmp(lastCommand, "&t")==0) {
                strcat(cleanCommand,"thread");
                threading(cleanCommand);
            }
            else{
                if(strcmp(firstCommand, "ls")==0) externalCommands(1,str);
                else if(strcmp(firstCommand, "cat")==0) externalCommands(2,str);
                else if(strcmp(firstCommand, "date")==0) externalCommands(3,str);
                else if(strcmp(firstCommand, "rm")==0) externalCommands(4,str);
                else if(strcmp(firstCommand, "mkdir")==0) externalCommands(5,str);
                else printf("Invalid Command\n");
            }
            scanf("%c", &str[0]);
        }
        strcpy(str,"");
        strcpy(firstCommand,"");
        strcpy(lastCommand,"");
        strcpy(cleanCommand,"");
        if(newLine==0) printf("\nsus$> ");
        else printf("sus$> ");
        newLine = 0;
        scanf("%[^\n]s",str);
    }
    return 0;
}