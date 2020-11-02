#include <stdio.h>
#include "buffer_circular.h"


int get_size( buff *Buffer_Circ){
    return (sizeof(Buffer_Circ->vector_circular)/sizeof(Buffer_Circ->vector_circular[0]));
}

int get_item(int *data, buff *Buffer_Circ){
    
    //Si está vacío
    if(Buffer_Circ->contador == 0){
        
        printf("El buffer está vacío\n");
        return -1;
        
    } else {
    //Si no está vacío
        //dato igual al de la posición de salida e incremento posición de salida y decremento contador
        *data = Buffer_Circ->vector_circular[Buffer_Circ->buf_out];
        Buffer_Circ->buf_out = get_size(Buffer_Circ)-get_size(Buffer_Circ) % (Buffer_Circ->buf_out+1);
        Buffer_Circ->contador--;
    
        return 0;
    }
}


int put_item(int data, buff *Buffer_Circ){
    
    //Si está lleno
    if(Buffer_Circ->contador == get_size(Buffer_Circ)){
        
        printf("El buffer está lleno");
        return -1;
        
    } else {
    //Si no está lleno
        //Buffer en la posición de entrada igual al dato e incremento posición de entrada y contador
        Buffer_Circ->vector_circular[Buffer_Circ->buf_in] = data;
        printf("Buffer in es: %d", Buffer_Circ->buf_in);
        Buffer_Circ->buf_in = get_size(Buffer_Circ)-get_size(Buffer_Circ) % (Buffer_Circ->buf_in+1);
        Buffer_Circ->contador++;
        return 0;
        
    }
}


int mostrar_contenido(buff *Buffer_Circ){
    if(Buffer_Circ->contador == 0){
        printf("El buffer está vacío\n");
        return -1;
    } else {
        for(int i=Buffer_Circ->buf_out; i<Buffer_Circ->buf_in; i++){
            printf("Posición %d dato: %d\n", i, Buffer_Circ->vector_circular[i]);
        }
        return 0;
    }
}
