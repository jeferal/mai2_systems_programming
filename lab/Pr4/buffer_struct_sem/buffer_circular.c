#include <stdio.h>
#include "buffer_circular.h"

int get_item(int *data, buff *Buffer_Circ){
    /*
    Función para extraer un dato del vector
    */

    sem_wait(&Buffer_Circ->items);
    sem_wait(&Buffer_Circ->mutex);

    /** SECCIÓN CRÍTICA **/
    //dato igual al de la posición de salida e incremento posición de salida y decremento contador
    *data = Buffer_Circ->vector_circular[Buffer_Circ->buf_out];
    Buffer_Circ->buf_out = (Buffer_Circ->buf_out + 1) % BUF_SIZE;    
    Buffer_Circ->contador--;
    /** SECCIÓN CRÍTICA **/

    sem_post(&Buffer_Circ->mutex);
    sem_post(&Buffer_Circ->huecos);
    return 0;
}


int put_item(int data, buff *Buffer_Circ){
    /*
    Función para introducir un dato en la estructura
    */
    
    sem_wait(&Buffer_Circ->huecos);
    sem_wait(&Buffer_Circ->mutex);

    /** SECCIÓN CRÍTICA **/
    //Buffer en la posición de entrada igual al dato e incremento posición de entrada y contador
    Buffer_Circ->vector_circular[Buffer_Circ->buf_in] = data;
    Buffer_Circ->buf_in = (Buffer_Circ->buf_in + 1) % BUF_SIZE;    
    Buffer_Circ->contador++;
    /** SECCIÓN CRÍTICA **/

    sem_post(&Buffer_Circ->mutex);
    sem_post(&Buffer_Circ->items);

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
    if(is_empty(Buffer_Circ))
        return -1;
    else 
    {
        for(int i=Buffer_Circ->buf_out;  i< Buffer_Circ->buf_out + get_counter(Buffer_Circ); i++)
        {
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
    //Inicialización semáforo
    sem_init(&Buffer_Circ->mutex, 0, 1);
    sem_init(&Buffer_Circ->huecos, 0, BUF_SIZE);
    sem_init(&Buffer_Circ->items, 0, 0);
    printf("Buffer inicializado\n");
}