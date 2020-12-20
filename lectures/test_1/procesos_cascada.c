#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/wait.h"
#define NPROCESOS 4

int main(void)
{ 
   pid_t pid;
   int i,status;

   for(i=0; i<NPROCESOS; i++) {

      pid=fork();
      if(pid>0)  
         break;
   }

   sleep(5);

   printf("BYE %ld  %ld\n", (long)getpid(), (long)getppid());
   //El último proceso no tiene hijos, entonces no espera!!
   //Por tanto es el primero en acabar
   while (wait(&status)>0){
      printf("Status: %d\n", WEXITSTATUS(status));
   }

   printf("I finished: %ld\n", (long)getpid());

   exit(i);
}