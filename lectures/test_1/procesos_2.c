#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main  (int argc, char *argv[]){
int val_fork;
int i=0,N=0;

   for (i=0;i<3; i++)
   { val_fork=fork();
       
       if (val_fork==0)
       {
         N++;
         break;
       }
   }
    
    printf("A\n");
    
    if (N>1) printf("B \n");
    else  printf("C\n");
   
    exit (0);
}