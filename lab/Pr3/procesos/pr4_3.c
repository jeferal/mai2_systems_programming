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
            exit(0);
        }
    }

    //Ahora a esperar al tercer hijo
    //if (waitpid(pid[2],&status,0)==pid[2])
    //printf("Mi tercer hijo ya ha terminado\n");
    sleep(25);

    return 0;
}