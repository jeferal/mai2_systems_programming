#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void main(){
    int val;
    int i=0, status;
    
    printf("Hola\n");
    
    for(i=0; i<3; i++){
        val = fork();
        if(val==0){  //==0 un padre tiene 3 hijos y ya, >0, se hace una rama
            sleep(5);
            exit(i);
        }
    }
    
    for(int j=0; j<3; j++){
        wait(&status);
        printf("%d\n", status % 255);
    }
    printf("BYE ");
}
