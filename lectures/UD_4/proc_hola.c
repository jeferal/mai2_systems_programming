#include <stdio.h>
#include <unistd.h>

void main(){
    int val;
    int i=0;
    printf("Hola\n");
    
    for(i=0; i<3; i++){
        val = fork();
        if(val>0)  //==0 un padre tiene 3 hijos y ya, >0, se hace una rama
            break;
    }
    sleep(10);
    printf("BYE from %d\n", val);
}
