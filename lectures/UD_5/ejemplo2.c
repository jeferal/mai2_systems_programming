#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#define BUFSIZE 256

int main(int argc, char * argv[]){

    int fd[2], status;
    char buf[BUFSIZE];
    unsigned strsize;

    if(argc!=1){
        fprintf(stderr, "Usage: %s \n", argv[0]);
        exit(1);
    }

    pipe(fd);

    switch(fork()){
        case -1:
            fprintf(stderr, "Could not fork\n");
            exit(1);
            break;
        case 0:
            //Código del hijo
            dup2(fd[1], STDOUT_FILENO);
            //Introduzco la escritura del pipe en la salida de descriptores de archivo (1)
            close(fd[0]);
            close(fd[1]);
            fprintf(stderr, "Child[%ld] about to write in the pipe\n", (long) getpid());
            sprintf(buf,"THIS WAS WRITTEN BY THE CHILD[%ld]\n", (long) getpid());
            strsize=strlen(buf)+1;

            if (write(STDOUT_FILENO, buf, strsize) != strsize){
                fprintf(stderr, "Child write to fifo failed\n");
                exit(1); 
            }

            fprintf(stderr, "Child[%ld] is done\n", (long) getpid());

            break;

        default: /* CODIGO DEL PADRE */
            dup2(fd[0],STDIN_FILENO);
            close(fd[0]); close(fd[1]);
            fprintf(stderr, "Parent[%ld] about to read form the pipe\n", (long) getpid());

            while((wait(&status)== -1) && (errno == EINTR));
            if (read(STDIN_FILENO, buf, BUFSIZE) <= 0){
                fprintf(stderr, "Parent read from fifo failed\n");
                exit(1);
                }
            fprintf(stderr, "Parent[%ld] got: %s\n", (long) getpid(), buf);
    } /** switch**/
    
    exit(0);
}