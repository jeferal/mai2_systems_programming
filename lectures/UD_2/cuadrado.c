#include <stdio.h>


int main(){
    int numero;
    int cuadrado;
    
    printf("Introduzca un número: ");
    scanf("%d", &numero);
    cuadrado = numero * numero;
    
    printf("El cuadrado de %d es %d\n", numero,cuadrado);
    //return cuadrado;
}
