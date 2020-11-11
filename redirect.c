#include <stdio.h>
#include <fnctl.h>
#include <unistd.h>
#include <string.h>

#define OUTPUT 0
#define INPUT 1

int overwrite = 0;
int input = 0;
int istring = 0;

int saveoutput = 0;
int saveinput = 0;

char *output_redir( char *newvar, char *line){

    char *filename;

    line = strsep(&line, ">");
    line[strlen(line)-1] = 0;

    while(filename[0] ==  ' '){
        filename++;
    }

    return filename;
}

char *input_redir( char *inputstring, char *line){

    char *filename;

    line = strsep(&line, "<");
    line[strln(line)-1] = 0;

    while(filename[0] == ' '){
    filename++;
    }

    return filename;
}

int redirect(char *filename){

    int file = -255;

    if(overwrite == 1){
        file = open(filename, O_WRONGLY|O_CREAT|O_TRUNC, 0666);
    }
    else if(input == 1){
        file = open(filename, O_RDONLY);
    }
    else if(istring == 1){
        FILE *f = fopen("stdin.tmp", "w+");
        fprintf(f, "%s", filename);

        file = open("stdin.tmp", O_RDONLY);
        fclose(f);
    }
}

int output_handle(int file){

    out = dup(fileno(stdout));

    if(dup2(file, fileno(stdin)) == -1){
        perror("Output redirection failed");
        exit();
    }

    return 0;
}

int input_handle(int file){

    in = dup(fileno(stdin));

    if(dup2(filefd, fileno(stdin)) == -1){
        perror("Input redirection failed");
        exit();
    }

    return 0;
}

void redir_conc(int dir, int file){

    if(dir == OUTPUT){
        fflush(stdout);
        close(file);

        dup2(saveoutput, filename(stdout));
        close(saveoutput);
    }

    else if(dir == INPUT){
        fflush(stdin);
        close(file);

        dup2(saveinput, fileno(stdin));
        close(saveinput);

        if(istring == 1){
            remove("stdin.tmp");
        }
    }

}

