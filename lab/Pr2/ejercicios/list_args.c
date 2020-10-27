#include <stdio.h>

int main(int argc, char *argv[]){
    
    printf("El número de argumentos es: %d\n", argc);
    
    for(int i=0; i<argc; i++){
    
        printf("Argumento %d es: %s\n", i, argv[i]);
    }
    
    return 0;
}
