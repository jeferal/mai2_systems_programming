#include <stdio.h>
#include "buffer_circular.h"

int get_item(int *data, buff *Buffer_Circ){
    /*
    Función para extraer un dato del vector
    */
    pthread_mutex_lock(&Buffer_Circ->buffer_lock);
    while(get_counter(Buffer_Circ)==0)
        pthread_cond_wait(&Buffer_Circ->vacio, &Buffer_Circ->buffer_lock);

    //dato igual al de la posición de salida e incremento posición de salida y decremento contador
    //SECCIÓN CRÍTICA
    *data = Buffer_Circ->vector_circular[Buffer_Circ->buf_out]; 
    Buffer_Circ->buf_out = (Buffer_Circ->buf_out + 1) % BUF_SIZE;     
    Buffer_Circ->contador--;
    //SECCIÓN CRÍTICA

    pthread_cond_broadcast(&Buffer_Circ->lleno);
    pthread_mutex_unlock(&Buffer_Circ->buffer_lock);
    return 0;
}


int put_item(int data, buff *Buffer_Circ){
    /*
    Función para introducir un dato en la estructura
    */
    pthread_mutex_lock(&Buffer_Circ->buffer_lock);

    while(get_counter(Buffer_Circ)==BUF_SIZE)
        pthread_cond_wait(&Buffer_Circ->lleno, &Buffer_Circ->buffer_lock);

    //Buffer en la posición de entrada igual al dato e incremento posición de entrada y contador
    //SECCIÓN CRÍTICA
    Buffer_Circ->vector_circular[Buffer_Circ->buf_in] = data;
    Buffer_Circ->buf_in = (Buffer_Circ->buf_in + 1) % BUF_SIZE;
    Buffer_Circ->contador++;
     //SECCIÓN CRÍTICA

    pthread_cond_broadcast(&Buffer_Circ->vacio);
    pthread_mutex_unlock(&Buffer_Circ->buffer_lock);
    return 0;
}

int get_counter(const buff *Buffer_Circ){
    /*
    Función que devuelve el número de elementos de la estructura
    */
    return Buffer_Circ->contador;
}


int show_content(const buff *Buffer_Circ){
    /*
    Función que muestra el contenido de la estructura
    */

    //Se comprueba si está vacío
    if(is_empty(Buffer_Circ)){
        return -1;
    } else {
        for(int i=Buffer_Circ->buf_out;  i<get_counter(Buffer_Circ)+Buffer_Circ->buf_out; i++){
            int pos = (i>= BUF_SIZE ? i-BUF_SIZE : i);
            printf("Vector circular[%d] = %d\n", pos, Buffer_Circ->vector_circular[pos]);
        }
        return 1;
    }
}

bool is_empty(const buff *Buffer_Circ){
    /*
    Función que comprueba si está vacío el buffer
    */
    if(Buffer_Circ->contador == 0)
        return true;
    else
        return false;
}

bool is_full(const buff *Buffer_Circ){
    /*
    Función que comprueba si está lleno el buffer
    */
    if(Buffer_Circ->contador == BUF_SIZE)
        return true;
    else
        return false;
}

void inicializar_buffer(buff *Buffer_Circ){
    Buffer_Circ->buf_in=0;
    Buffer_Circ->buf_out=0;
    Buffer_Circ->contador=0;
    //Inicialización mutex
    pthread_mutex_init(&Buffer_Circ->buffer_lock, NULL);
    pthread_cond_init(&Buffer_Circ->lleno, NULL);
    pthread_cond_init(&Buffer_Circ->vacio, NULL);
}