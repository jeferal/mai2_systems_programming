#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>



void main(void)
{
     pid_t pidhijo;
     int status, x;
     long i,j;
     
     if ( (pidhijo = fork()) == -1){
         
        perror("fork ha fallado y por tanto no hay hijo");
        exit(1);
     } 
     else if (pidhijo==0){ /* CODIGO HIJO */

        if (execl ("/bin/ls","ls","-1",NULL)<0){ 
            
            printf("Falla la ejecucion del ls");
            exit (1);} 
     }
     
     else if ( (x=wait(&status)) != pidhijo){ 
         fprintf(stderr, "Soy el PADRE: una senyal (capturada) me ha interrumpido la espera\n");}
     
     exit(0);
}
