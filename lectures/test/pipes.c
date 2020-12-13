#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/wait.h"
#include "sys/stat.h"
#include <fcntl.h>

int main()
{
    int tubo[2], fd, status;
    pid_t pid;

    pipe(tubo);
    printf("I am %ld process\n", (long)getpid());
    if(!(pid=fork()))
    {
        //Entra el hijo
        printf("I am %ld and I am going to write on the pipe\n", (long)getpid());
        //tubo[0] lectura
        //tubo[1] escritura
        dup2(tubo[1], STDOUT_FILENO);
        close(tubo[0]); close(tubo[1]);
        execlp("/bin/cat", "cat", "fich1", NULL);
    }

    printf("I am %ld process, I created my child %ld\n", (long)getpid(), (long)pid);

    if(!(pid=fork()))
    {
        //Entra el hijo
        printf("I am %ld and I am going to read from the pipe\n", (long)getpid());
        dup2(tubo[0], STDIN_FILENO);
        fd = open("fich2", O_WRONLY |O_CREAT|O_TRUNC,0666);
        dup2(fd,1);
        close(tubo[0]); close(tubo[1]);     
        close(fd);
        execlp("/usr/bin/wc", "wc", "-l",NULL);
    }

    printf("I am %ld process, I created my child %ld\n", (long)getpid(), (long)pid);
    
    close(tubo[0]);  close(tubo[1]);
    while(pid != wait(&status));
}