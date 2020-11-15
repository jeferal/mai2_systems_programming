#include <stdio.h>
#include "buffer_struct/buffer_circular.h"

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
    printf("Meto 5 datos\n");
    printf("El contador es: %d\n", my_vector.contador);
    printf("Posición out es %d e in %d\n", my_vector.buf_out, my_vector.buf_in);
    
    mostrar_contenido(&my_vector);
    
    for(int i=0; i<5; i++){
        get_item(&data, &my_vector);
    }
    
    printf("Quito 5 datos\n");
    printf("El contador es: %d\n", my_vector.contador);
    printf("Posición out es %d e in %d\n", my_vector.buf_out, my_vector.buf_in);
    mostrar_contenido(&my_vector);
    
    for(int i=0; i<5; i++){
        put_item(i+3, &my_vector);
    }
    
    printf("Meto 5 datos\n");
    printf("El contador es: %d\n", my_vector.contador);
    printf("Posición out es %d e in %d\n", my_vector.buf_out, my_vector.buf_in);
    mostrar_contenido(&my_vector);
    
    for(int i=0; i<2; i++){
        get_item(&data, &my_vector);
    }
    
    printf("Quito 2 datos\n");
    printf("El contador es: %d\n", my_vector.contador);
    printf("Posición out es %d e in %d\n", my_vector.buf_out, my_vector.buf_in);
    
    mostrar_contenido(&my_vector);
    
    for(int i=0; i<3; i++){
        put_item(i+10, &my_vector);
    }
    
    printf("Meto 3 datos\n");
    printf("El contador es: %d\n", my_vector.contador);
    printf("Posición out es %d e in %d\n", my_vector.buf_out, my_vector.buf_in);
    
    mostrar_contenido(&my_vector);
    
    return 0;
}
