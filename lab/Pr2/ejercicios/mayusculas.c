#include <stdio.h>
#define TAM_CADENA 200

void main(){

    //Puntero a caracter para copiar las cadenas
    char *p1, *p2;
    char cadena[TAM_CADENA], cadena2[TAM_CADENA];
    
    printf("Introduzca una cadena: ");
    scanf("%s", cadena);

    p1 = cadena;
    p2 = cadena2;
        
    while(*p1 != '\0'){
        //Copiar p1 a p2 restando 32
        if(isalpha(*p1))    *p2 = *p1;
        
        else    *p2 = *p1-32;
        
        *p1++;
        *p2++;
    }
    
    *p2 = '\0';
    printf("%s", cadena2);
}
