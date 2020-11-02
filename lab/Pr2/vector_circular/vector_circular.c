#include <stdio.h>

#define BUF_SIZE 20

int main(){
    int vector_circular[BUF_SIZE];
    
    for(int i=0; i<BUF_SIZE; i++){
        if(i==BUF_SIZE-1)
            vector_circular[i] = 0;
        else
            vector_circular[i] = i+1;
    }
    
    for(int i=0; i<BUF_SIZE; i++){
        printf("La posición %d es: %d\n", i, vector_circular[i]);
    }
    
    return 0;
}
