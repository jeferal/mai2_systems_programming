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
        printf("Soy el padre con valor de i: %d, PID: %ld y he creado el hijo %ld\n", i, (long)getpid(), (long)getppid());
        if(pid[i]!=0){
            //Solo ejecutado por los hijos
            break;
        }
    }
    waitpid(pid[i], &status, 0);
    printf("“Soy el padre con PID: %ld y el valor de retorno de mi hijo es:	%d\n", (long)getpid(), WEXITSTATUS(status));
    exit(0);
}