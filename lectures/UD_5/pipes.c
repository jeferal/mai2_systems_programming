#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(){
    int fd[2];
    int val_fork;

    pipe(fd);

    if( val_fork=fork() == 0){
        //Código que hace el hijo
        //Pipe de salida
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);

        //La salida de ls -l va al pipe
        execl("/bin/ls", "ls", "-l", NULL);
        printf("Ha fallado la ejecucion del ls");

    } else {
        //Código del padre
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execl("/usr/bin/sort", "sort", "-n", NULL);
        printf("Ha fallado la ejecución del sort");
    }

    exit(0);
    
}