/*
Ejercicio 2
*/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#define NPROCESOS 5


int main(){

    pid_t pid[NPROCESOS];
    int status;

    for(int i=0; i<NPROCESOS; i++){
        pid[i] = fork();
        if(pid[i]==0){
            printf("Soy el hijo número %ld con padre %ld\n",
            (long)getpid(), (long)getppid());
            sleep(20);
            exit(0);
        }
    }

    sleep(25);

    return 0;
}