/*
Ejercicio 5
*/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#define NPROCESOS 4

int main(){
    pid_t pid[NPROCESOS];
    int status, i;

    for(i=0; i<NPROCESOS; i++){
        pid[i] = fork();
        
        if(pid[i]!=0){
            //Solo ejecutado por los padres
            printf("Soy el padre con valor de i(%d) con PID(%ld) y he creado a mi hijo con PID(%ld)\n", i, (long)getpid(), (long)pid[i]);
            break;
        }
    }
    if(i<NPROCESOS){
        //Esperan todos menos el último
        pid_t pid = wait(&status);
        printf("Soy el padre con PID(%ld) y el valor de retorno de mi hijo con pid(%ld) es %d\n", (long)getpid(), (long)pid, WEXITSTATUS(status));
    }
    sleep(10);
    exit(i);
}