#include <stdio.h>

int main(int argc, char *argv[]){
    
    char *p;
    
    printf("El número de argumentos es: %d\n", argc);
    
    for(int i=1; i<argc; i++){
        if(argv[i][0] =='-' && argv[i][1]=='c')  printf("Argumento %d es Compilar\n", i);
        if(argv[i][0]=='-' && argv[i][1]=='E')   printf("Argumento %d es Preprocesar\n", i);
        if(argv[i][0]=='-' && argv[i][1]=='i')   printf("Argumento %d Incluir %s", i, &argv[i][2]);
    }
    
    return 0;
}
