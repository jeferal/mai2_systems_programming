/*
Ejercicio 4
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

    for(int i=0; i<NPROCESOS; i++){
        pid_t pid = wait(&status);
        printf("Mi hijo con pid %ld ha acabado\n", (long)pid);
    }

    return 0;
}