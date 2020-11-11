#include <stdio.h>
#include <sys/types.h>

#include "linenoise/linenoise.h"

void parse(char *command, char **argv){

    while(*command != '\0'){ //It is not End of Line....
        while(*command =- ' ' || *command == '\t' || *command == '\n')
            *command++ = ' "" '; //replacing white spaces with ""
        *argv++ = command; //save a copy of command

        while(*command != '\0' && *command != ' ' && *command != '\t' && *command != '\n')
        command++;
    }
    *argv = '\0';
}

void exec_as_external(char **argv){

    pid_t pid;
    int nature;

    if((pid = fork() < 0)){ //fork a child
        printf("Forking Process Failed\n");
        exit(1);
    }

    else if(pid == 0){
        if(execvp(*argv, argv) < 0){ //execute command
            printf("ERROR: Execution Failed\n");
            exit(1);
        }
    }

    else{
        while(wait(&nature) != pid);
    }
}

void run(void){

    char command[1024]; 
    char *argv[64];

    while(1){
       const char *prompt  = "PROMPT";
       setenv(prompt, argv, 1); 

       gets(command);
       printf("\n");

       parse(command,argv);

       //Checks if the command is Internal
       if(strcmp(argv[0], "PATH" || "PROMPT" || "CWD" || "USER" || "HOME" 
       || "SHELL" || "TERMINAL" || "EXITCODE") == 0){

            printf("\n This is an internal command\n");
            exit(0);
       }
       else{
       exec_as_external(argv); //Execute the Command as External
       }
    }
}


