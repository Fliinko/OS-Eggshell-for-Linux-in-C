#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>

void init_tiny_shell(char *argv[]){

    clear();
    //initializes the shell variables
    set_shell_vars(*argv[]);

    printf("-------------WELCOME TO EGGSHELL-----------------\n");
    printf("-------------Owen Agius 496701L------------------\n");

    char *user = getenv("USER");
    printf("\n User is: %s", user);
    sleep(1);
    clear();

}

int eggshell(int argc, char *argv[]) {

    char *line;
    const char *delimiter = " ";
    char *args[MAX_ARGS];
    char shell_name[MAX_NAME] = "eggshell> ";

    while((line = linenoise(shell_name)) != NULL) {
        // Tokenise
        char *token = strtok(line, delimiter);

        // Check if user wants to exit
        if (token != NULL && strcmp(token, "exit") == 0)
            return EXIT_SUCCESS;

        // Parse and copy tokens
        int i = 0;
        while(token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, delimiter);
        }

        // Argument arrays need to be null terminated
        args[i] = NULL;

        // Employ the fork+exec pattern here and update shell name
        if (i > 0 && fork_and_exec(args)) {
            int n = snprintf(shell_name, MAX_NAME, "%s> ", args[0]);
            if (n >= MAX_NAME)
                snprintf(shell_name + (MAX_NAME - 3), 3, "> ");
        }
        
        // Free the string allocated by linenoise
        linenoiseFree(line);
    }
    
    return EXIT_SUCCESS;
    // Set output_enabled if '-o' is passed as argument
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-o") == 0) {
            output_enabled = true;
            break;
        }
    }

    // Install handler for SIGTSTP
    if (signal(SIGTSTP, &stop_handler) == SIG_ERR) {
        perror("Cannot set handler for SIGTSTP");
        return EXIT_FAILURE;
    }

    // Loop until interrupt occurs
    while(true) {
        // Get the current date and time, and write them in time_str 
        char time_str[TIME_STRING_SIZE];
        if (!write_current_dt(time_str, sizeof(time_str)))
            return EXIT_FAILURE;

        // Print date and time to stdout
        if (output_enabled)
            printf("%s\n", time_str);

        // Save to environment variable DATE_TIME
        if (setenv("DATE_TIME", time_str, true) == -1) {
            perror("Cannot set environment variable DATE_TIME");
            return EXIT_FAILURE;
        }

        // Wait one second
        sleep(1);
    }

    return EXIT_SUCCESS;