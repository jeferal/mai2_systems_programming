/*
    CÓDIGO PROGRAMA MAYÚSCULAS
*/

#include <stdio.h>
#include <ctype.h>
#define TAM_CADENA 200

int main(){

    //Puntero a caracter para copiar las cadenas
    char *p1, *p2;
    char cadena[TAM_CADENA], cadena2[TAM_CADENA];
    
    printf("Introduzca una cadena: ");
    gets(cadena);

    p1 = cadena;
    p2 = cadena2;
        
    int i = 0;
    while(*p1 != '\0'){
        //Copiar p1 a p2 restando 32
        if(isupper(*p1)){
            *p2 = *p1;
        }
        else if (*p1==' '){
            *p2 = ' ';
        }
        else{
             *p2 = *p1-32;
        }    
        *p1++;
        *p2++;
        i++;
    }
    
    *p2 = '\0';
    printf("%s\n", cadena2);

    return 0;
}
