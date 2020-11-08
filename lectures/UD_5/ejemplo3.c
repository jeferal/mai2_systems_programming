#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#define BUFSIZE 256

int main(int argc, char *argv[]){ 
    mode_t fifo_mode = S_IRUSR | S_IWUSR;
    int fd, status;
    char buf[BUFSIZE];
    unsigned strsize;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s fifoname\n", argv[0]);
        exit(1); 
    }

    if ((mkfifo(argv[1], fifo_mode) == -1) && (errno != EEXIST)){
        fprintf(stderr, "Could not create a named pipe: %s\n", argv[1]);
        exit(1); 
    }

    switch (fork()) {
        case -1:
            fprintf(stderr, "Could not fork\n"); exit(1);
            break;

        case 0:/* CODIGO DEL HIJO */
            fprintf(stderr, "Child[%ld] about to open fifo: %s\n", (long) getpid(), argv[1]);

            if ((fd = open(argv[1], O_WRONLY)) == -1){
                fprintf(stderr, "Child could not open fifo: %s \n", argv[1]); exit(1); 
            }
            
            sprintf(buf,"THISWAS WRITTEN BY THE CHILD[%ld]", (long) getpid());
            strsize=strlen(buf)+1;
            
            if (write(fd, buf, strsize) != strsize){
                fprintf(stderr, "Child write to fifo failed\n"); exit(1); 
            }
            fprintf(stderr, "Child[%ld] is done\n", (long) getpid());

            break;

        default: /* CODIGO DEL PADRE */
            fprintf(stderr, "Parent[%ld] about to open fifo: %s\n", (long) getpid(), argv[1]);

            if ((fd = open(argv[1], O_RDONLY | O_NONBLOCK)) == -1){
                fprintf(stderr, "Parent could not open fifo: %s\n", argv[1]);
                exit(1);
            }

            fprintf(stderr, "Parent[%ld] about to read fifo: %s\n", (long) getpid(), argv[1]);

            while((wait(&status)== -1) && (errno == EINTR));

            if (read(fd, buf, BUFSIZE) <= 0){
                fprintf(stderr, "Parent read from fifo failed\n");
                exit(1);
            }
            
            fprintf(stderr, "Parent[%ld] got: %s\n", (long) getpid(), buf);
    }/**switch**/

    exit(0);
    
}