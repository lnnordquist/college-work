#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <wait.h>

char error_message[30] = "An error has occurred\n";

void myPrint(char *msg)
{
    write(STDOUT_FILENO, msg, strlen(msg));
}

/* process_cmd_s: processes "simple" commands (exit; pwd; cd [path]). 
                            Takes an array w/ name of command and the (file 
                            path) argument. Returns nothing, since it either 
                            prints, changes directories, or exits.
*/
void process_cmd_s(char *args[]){
    if(strcmp(args[0],"exit")==0){
        if(args[1]!=NULL){
            write(STDOUT_FILENO, error_message, strlen(error_message));
            return;
        }
        exit(0);
    }
    if(strcmp(args[0],"pwd")==0){
        if(args[1]!=NULL){
            write(STDOUT_FILENO, error_message, strlen(error_message));
            return;
        }
        char out2[512];
        getcwd(out2,512);
        strcat(out2,"\n");
        myPrint(out2);
        return;
    }
    if(strcmp(args[0],"cd")==0){

        if(args[2]!=NULL){
            write(STDOUT_FILENO, error_message, strlen(error_message));
            return;
        }

        char *path = args[1];
        if(path==NULL){
            path = getenv("HOME");
            chdir(path);
            getcwd(path,512);
            return;
        }
        if(chdir(path)==-1){
            write(STDOUT_FILENO, error_message, strlen(error_message));
            return;
        }
        return;
    }
    else{
        write(STDOUT_FILENO, error_message, strlen(error_message));
        return;
    }
}

/* process_cmd_c:   process all other (not built in) commands. Takes an array
                    with f'n name, flags, arguments, etc and passes it to 
                    execvp(). Returns nothing.
*/

void process_cmd_c(char *args[]){
    if(execvp(args[0],args)==-1){
        write(STDOUT_FILENO, error_message, strlen(error_message));
        exit(1);
    }
    return;
}

int main(int argc, char *argv[]) {
    char *pinput;
    FILE *file;
    char *line = malloc(sizeof(char)*1500);
    int interactive = 0;

    if(argc == 1){
        interactive = 1;
        file = stdin;
    }
    if(argv[1] != NULL){
        file = fopen( argv[1], "r");
        if(file == NULL){
            write(STDOUT_FILENO, error_message, strlen(error_message));
        }
    }
    while(1){
        if(interactive){
            myPrint("myshell> ");
        }
        pinput=fgets(line, 1500, file);
        if(pinput == NULL){
            exit(0);
        }
        if(strlen(pinput)>=512){
            myPrint(pinput);
            write(STDOUT_FILENO, error_message, strlen(error_message));
            continue;
        }
        char *copy = line;
        char *cmd;

        int empty = 1;
        int i = 0;
        while(copy[i] != '\0'){
            if(copy[i] != ' ' && copy[i] != '\n' && copy[i] != '\t'){
                empty = 0;
                break;
            }
            i++;
        }
        if(empty){
            continue;
        }
        myPrint(copy);
        copy[strlen(copy)-1] = '\0';
        while((cmd = strtok_r(copy, ";", &copy))){
            char *flags[512];
            int i=0;
            while((flags[i] = strtok_r(cmd, " \t", &cmd))){
                i++;
            }
            flags[i+1] = NULL;
            if(flags[0]==NULL){
                continue;
            }
            if(strcmp(flags[0],"pwd")==0||strcmp(flags[0],"exit")==0||
                                                    strcmp(flags[0],"cd")==0){
                process_cmd_s(flags);
            }
            else{
                int f = fork();
                if(f>0){
                    wait(NULL);
                    continue;
                }
                if(f==0){
                    process_cmd_c(flags);
                }
                else{
                    write(STDOUT_FILENO, error_message, strlen(error_message));
                    return 0;
                }
            }
        }
    }
    return 0;
}
