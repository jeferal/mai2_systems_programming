#include <stdio.h>
#include "buffer_circular.h"

int main(){
    buff my_vector;
    my_vector.contador=0;
    my_vector.buf_out=0;
    my_vector.buf_in=0;
    
    int data;
    //5 Inserciones
    for(int i=0; i<5; i++){
        put_item(i+4, &my_vector);
    }
    
    printf("El contador es: %d\n", my_vector.contador);
    printf("Posición out es %d e in %d\n", my_vector.buf_out, my_vector.buf_in);
    mostrar_contenido(&my_vector);

    
    for(int i=0; i<5; i++){
        get_item(&data, &my_vector);
    }
    
    printf("El contador es: %d\n", my_vector.contador);
    
    for(int i=0; i<5; i++){
        put_item(i+3, &my_vector);
    }
    
    printf("El contador es: %d\n", my_vector.contador);
    printf("Posición out es %d e in %d\n", my_vector.buf_out, my_vector.buf_in);
    
    for(int i=0; i<2; i++){
        get_item(&data, &my_vector);
    }
    
    printf("El contador es: %d\n", my_vector.contador);
    printf("Posición out es %d e in %d\n", my_vector.buf_out, my_vector.buf_in);
    
    mostrar_contenido(&my_vector);
    
    return 0;
}
