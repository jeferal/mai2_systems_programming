#include <stdio.h>
#include "buffer_circular.h"

int get_item(int *data, buff *Buffer_Circ){
    
    //Si está vacío
    if(is_empty(*Buffer_Circ)){
        printf("El buffer está vacío\n");
        return -1;
    } else {
    //Si no está vacío
        //dato igual al de la posición de salida e incremento posición de salida y decremento contador
        *data = Buffer_Circ->vector_circular[Buffer_Circ->buf_out];
        if(Buffer_Circ->buf_out == BUF_SIZE-1)
            Buffer_Circ->buf_out = 0;
        else
            Buffer_Circ->buf_out++;
        
        Buffer_Circ->contador--;
    
        return 0;
    }
}


int put_item(int data, buff *Buffer_Circ){
    
    //Si está lleno
    if(is_full(*Buffer_Circ)){
        printf("El buffer está lleno");
        return -1;
    } else {
    //Si no está lleno
        //Buffer en la posición de entrada igual al dato e incremento posición de entrada y contador
        Buffer_Circ->vector_circular[Buffer_Circ->buf_in] = data;
        
        if(Buffer_Circ->buf_in == BUF_SIZE-1)
            Buffer_Circ->buf_in = 0;
        else
            Buffer_Circ->buf_in++;
        
        Buffer_Circ->contador++;
        
        return 0;
        
    }
}

int get_counter(const buff Buffer_Circ){
    return Buffer_Circ.contador;
}


int mostrar_contenido(buff *Buffer_Circ){

    int pos=Buffer_Circ->buf_out;
    if(is_empty(*Buffer_Circ)){
        printf("El buffer está vacío\n");
        return -1;
    } else {
        for(int i=Buffer_Circ->buf_out;  i<get_counter(*Buffer_Circ)+Buffer_Circ->buf_out; i++){
            pos = (i>= BUF_SIZE ? i-BUF_SIZE : i);
            printf("Posición %d: dato %d\n", pos, Buffer_Circ->vector_circular[pos]);
        }
        return 1;
    }
}

bool is_empty(const buff Buffer_Circ){
    if(Buffer_Circ.contador == 0){
        printf("El buffer está vacío\n");
        return true;
    }
    else{
        return false;
    }
}

bool is_full(const buff Buffer_Circ){
    if(Buffer_Circ.contador == BUF_SIZE){
        printf("El buffer está lleno\n");
        return true;
    }
    else{
        return false;
    }
}