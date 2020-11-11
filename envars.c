#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>

#include "linenoise/linenoise.h";

bool set_shell_vars(char *argv[]){

    //Setting PATH
    const char *path = "PATH";
    char patharr[PATH_MAX];
    if(getenv(path, sizeof(path)) == NULL){
        return false;
    }
    setenv(path, patharr, 1);

    //Setting PROMPT
    const char *prompt  = "PROMPT";
     char promptarr[PATH_MAX];
    if(getenv(prompt, sizeof(prompt)) == NULL){
        return false;
    }
    setenv(prompt, promptarr, 1);

    //Setting CWD
    const char *cwd = "CWD";
    char cwdarr[PATH_MAX];
    if(getcwd(cwd, sizeof(cwd)) == NULL){
        return false;
    }

    setenv(cwdarr, cwd, 1);

    //Setting USER
    const char *user = "USER";
     char userarr[PATH_MAX];
    if(getenv(user, sizeof(user)) == NULL){
        return false;
    }
    setenv(user, userarr, 1);

    //Setting HOME
    const char *home = "HOME";
     char homearr[PATH_MAX];
    if(getenv(home, sizeof(home)) == NULL){
        return false;
    }
    setenv(home, homearr, 1);

    //Setting SHELL
    char *shellval = getenv("CWD");
    const char *shell = "SHELL";
    strcat(shellval, (argv[0]+1));

    setenv(shell, shellval, 1);

    //Setting TERMINAL
    const char *terminal = "TERMINAL";
    char terminalval[TTY_MAX];
    ttyname_r(fileno(stdin), terminalval, TTY_MAX);
    
    setenv(terminal, terminalval, 1);

    //Setting EXITCODE
    const char *exitcode = "EXITCODE";
     char exitarr[PATH_MAX];
    if(getenv(exit, sizeof(exit))) == NULL){
        return false;
    }
    setenv(exitcode, exitarr, 1);

    return false;
}

bool checkvar(char *input[]){

    if(strcmp(*input[], "PATH" || "PROMPT" || "CWD" || "USER" || "HOME" || "SHELL" || "TERMINAL" || "EXITCODE"));
    return true;
    
    else{
    return false;
    }

}





