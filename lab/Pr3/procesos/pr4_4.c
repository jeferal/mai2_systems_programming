/*
Modifica	el	programa	pr4-2	 (llámalo	pr4-4.c)	para	que	el	proceso	padre	espere	a	sus	hijos	antes	de	que	estos	
terminen	y	no	se	generen	procesos	zombies.	Compruébalo	ejecutando	el	programa	en	background	y	con	la	orden	
ps	como	en	el	ejercicio	2.
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

    if(waitpid(pid[NPROCESOS-1], &status, 0) == pid[NPROCESOS-1])
        printf("Mi último hijo ya ha terminado");

    return 0;
}