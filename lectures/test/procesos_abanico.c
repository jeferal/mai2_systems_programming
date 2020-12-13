#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/wait.h"

int main(int argc, char *argv[])
{
    int status;
    pid_t pid;

    for(int i=0; i<4; i++)
    {
        if(fork()==0)
        {
            sleep(3);
            //exit(0);
            break;
        }
    }

    while((pid=wait(&status))>0)
        printf("Soy el proceso con pid %ld, mi hijo con pid %ld ha terminado\n", (long)getpid(), (long)pid);
    //Los hijos hacen la llamada wait, pero al no tener hijos, no se quedan en el bucle y terminan
    //antes que el padre
    exit(0);
}
