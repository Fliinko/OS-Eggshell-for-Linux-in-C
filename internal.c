#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>

#include "linenoise/linenoise.h"

#define MAX_ARGS 255

pid_t suspended_processes[10];
pid_t current_pid;
int susp = -1;

void signals(int signum){
    pid_t func = current_pid;

    //catching SIGINT signals
    if(signum = SIGINT){
        int res = kill(func, SIGINT);
    }

    //catching SIGTSTP signals
    else if(signum == SIGTSTP){
        int res = kill(func, SIGTSTP);
        int resusp = 1;

        suspended_processes[susp+1] = func;
        susp ++;
    }

    else{
        printf("Not a valid signal number\n");
    }
}

int sighandle(void){
    struct action a;

    sigemptyset(&a.a_mask);
    a.a_flags = A_RESTART;

    if(action(SIGINT, &a, NULL)== -1)
        printf("SIGINT Not Caught - Interrupt Signal\n");
    if(action(SIGTSTP, &a, NULL)== -1)
        printf("SIGSTP Not Caught - Suspension Signal\n");

 return 0;
}


int resumeProcess(int nature, pid_t process){
    //nature stores the status of the process in question 

    newvar = 0;

    //Sends SIGCONT signal to process if suspended 
    int sendsignal = kill(process, SIGTSTP);

    //If SIGCONT failed - Abort
    if(sendsignal != 0){
        perror("Process resuming failed");
        return 1;
    }

    current_pid = process;

    if(nature == FOREGROUND){
        waitpid(current_pid, &nature, WUNTRACED);

        if(WIFEXITED(nature)){
            setenv("EXITCODE", "0", 1);
        }
        else if(WIFSIGNALED(nature)){
            printf("Process received Signal %d\n", WTERMSIG(nature));
        }
        }
    }

int print(char *input[]){

    //checks if input is a shell variable or not
    if(checkvar[input] == true){
        printf(input, "%s", getenv(input));   
    }
    //if the input is not a variable
    else if{
            printf("%s", input);
    }
    return 0;
}

bool internalcomms(char *argv[]){

    if(strcmp(argv,"exit") == 0){
        exit();
        setenv("EXITCODE", "0", 1);

        break;
    }
    
    if(strcmp(argv, "echo") == 0){

        const char *prompt  = "PROMPT";
        setenv(prompt, argv, 1); 

        printf("Enter your Input\n");
        scanf("%s", input);

        print(input);
        setenv("EXITCODE", "0", 1);

        break;
        
    }
    
    if(strcmp(argv,"cd") == 0){

        const char *prompt  = "PROMPT";
        setenv(prompt, argv, 1); 

        char *param[];
        
        printf("Please enter the directory you want to change to\n");
        scanf("%s", *param[]);

        int error = chdir(param[1]);
        if(error == 0){
            setenv("CWD", param[1], 1);
            setenv("EXITCODE", "0", 1);
        }
        else{
            printf("\nInvalid Path\n");
        }

        break;
    }

    if(strcmp(argv, "unset") == 0){

        const char *prompt  = "PROMPT";
        setenv(prompt, argv, 1); 

        printf("Insert the variable you want to unset\n");
        scanf("%s", input);
        //checks if the input is a valid variable
        checkvar(input);

        if(checkvar(input) == true){
        int ret = remove(input);

        if(ret == 0){
            printf("Variable unset successfully\n");
            setenv("EXITCODE", "0", 1);
            break;
        }
        else{
            printf("Error: Variable unable to be unset");
            break;
        }
        }
        else{
            printf("The input is not a valid variable");

        }

        break;
    }

    if(strcmp(argv, "showenv") == 0){
        
        char *vars[7];
        *vars[0] = "PATH";
        *vars[1] = "PROMPT";
        *vars[2] = "CWD";
        *vars[3] = "USER";
        *vars[4] = "HOME";
        *vars[5] = "SHELL";
        *vars[6] = "TERMINAL";
        *vars[7] = "EXITCODE";

        printf("\n ----------------- These are the Environment Variables--------------\n");

        for(int i = 0; i<sizeof(*vars); i++){
            printf("\n%s", vars[i]);
            printf("\n%s", getenv(vars[i]));
        }
         setenv("EXITCODE", "1", 1);
         break;
    }

    if(strcmp(argv,"source") == 0){
            break;
    }
    
    if(strcmp(argv,"bg") == 0){

        const char *prompt  = "PROMPT";
        setenv(prompt, argv, 1); 

        printf("What is the state of the current process\n");
        scanf("%s", status);

        setenv(prompt, argv, 1); 

        printf("Enter the Process Number\n");
        scanf("%d", processno);

        resumeProcess(status, processno);
        setenv("EXITCODE", "0", 1);

        break;

    }
    
    if(strcmp(argv,"listproc") == 0){
            break;
    }

    if(strcmp(argv, !("listproc" || "bg" || "source" || "echo" || "showenv" || "unset" || "cd" || "exit"))){
        printf("The input is not a valid internal function\n");
        exec_as_external(argv);
        break;
    }
    
    return true;

}

bool checkinternal(char *input[]){

    if(strcmp(*input[], "listproc" || "bg" || "source" || "echo" || "showenv" || "unset" || "cd" || "exit"));
    return true;
    
    else{
    return false;
    }

}

    
    
    

    
