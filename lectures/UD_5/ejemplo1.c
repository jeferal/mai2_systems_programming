#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    int fd[2];

    if(argc < 2){
        printf(stderr, "Usage: %s command filter \n", argv[0]);
        exit(1);
    }

    pipe(fd);

        for(int i=0; i<2; i++){
            if(fork()==0){
                //HIJOS
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
                close(fd[1]);

                execl("/bin/ls", "ls", NULL);
                perror("The exec failed");
            }
        }

        //PADRE
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);

        execvp(argv[1], &argv[1]);
        fprintf(stderr,"The exec of %s failed", argv[1]);
        exit(1);
}