#include <stdio.h>
#include "buffer_circular.h"


int get_item(WorkInfo *data, buff *Buffer_Circ){
    /*
    Función para extraer un dato del vector
    */
    pthread_mutex_lock(&Buffer_Circ->buffer_lock);
    while(is_empty(Buffer_Circ))
        pthread_cond_wait(&Buffer_Circ->vacio, &Buffer_Circ->buffer_lock);

    //dato igual al de la posición de salida e incremento posición de salida y decremento contador
    *data = Buffer_Circ->data_array[Buffer_Circ->buf_out]; 
    Buffer_Circ->buf_out = (Buffer_Circ->buf_out + 1) % BUF_SIZE;     
    Buffer_Circ->contador--;

    pthread_cond_broadcast(&Buffer_Circ->lleno);
    pthread_mutex_unlock(&Buffer_Circ->buffer_lock);
    
    return 0;
}


int put_item(WorkInfo data, buff *Buffer_Circ){
    /*
    Función para introducir un dato en la estructura
    */
    pthread_mutex_lock(&Buffer_Circ->buffer_lock);

    while(is_full(Buffer_Circ))
        pthread_cond_wait(&Buffer_Circ->lleno, &Buffer_Circ->buffer_lock);

    //Buffer en la posición de entrada igual al dato e incremento posición de entrada y contador
    Buffer_Circ->data_array[Buffer_Circ->buf_in] = data;
    Buffer_Circ->buf_in = (Buffer_Circ->buf_in + 1) % BUF_SIZE;
    Buffer_Circ->contador++;

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


int show_content(const buff *Buffer_Circ) {
    /*
    Función que muestra el contenido de la estructura
    */

    // Se comprueba si está vacío
    if (is_empty(Buffer_Circ)) {
        return -1;
    }

    for (int i=Buffer_Circ->buf_out;  i<get_counter(Buffer_Circ)+Buffer_Circ->buf_out; i++) {
        int pos = (i>= BUF_SIZE ? i-BUF_SIZE : i);
        printf("Vector circular[%d] = %d\n", pos, Buffer_Circ->data_array[pos].id);
    }

    return 1;
}

bool is_empty(const buff *Buffer_Circ) {
    /*
    Función que comprueba si está vacío el buffer
    */
    return Buffer_Circ->contador == 0;
}

bool is_full(const buff *Buffer_Circ) {
    /*
    Función que comprueba si está lleno el buffer
    */
    return Buffer_Circ->contador == BUF_SIZE;
}

void inicializar_buffer(buff *Buffer_Circ) {
    Buffer_Circ->buf_in=0;
    Buffer_Circ->buf_out=0;
    Buffer_Circ->contador=0;
    //Inicialización mutex
    pthread_mutex_init(&Buffer_Circ->buffer_lock, NULL);
    pthread_cond_init(&Buffer_Circ->lleno, NULL);
    pthread_cond_init(&Buffer_Circ->vacio, NULL);
}

long getCurrentMicroseconds()
{
    struct timespec currentTime;
    clock_gettime(CLOCK_MONOTONIC, &currentTime);
    return (currentTime.tv_sec)*1000000 + (currentTime.tv_nsec) / 1000;
}

int get_pages_queue(buff *Buffer_Circ)
{
    int n_pages_queue = 0;

    for (int i=Buffer_Circ->buf_out;  i<get_counter(Buffer_Circ)+Buffer_Circ->buf_out; i++) {
        int pos = (i>= BUF_SIZE ? i-BUF_SIZE : i);
        n_pages_queue = n_pages_queue + Buffer_Circ->data_array->pages;
    }

    return n_pages_queue;
}

int put_item_ind(WorkInfo data, buff *Buffer_circ_bn, buff *Buffer_circ_rgb)
{
    //Get queue time
    int time_bn = 1*get_pages_queue(Buffer_circ_bn);
    int time_rgb = 4*get_pages_queue(Buffer_circ_rgb);

    buff *shortest_queue, *longest_queue;
    char *shortest_name;

    //Select shortest queue
    if(time_bn < time_rgb)
    {
        shortest_queue = Buffer_circ_bn;
        longest_queue = Buffer_circ_rgb;
        shortest_name = "Blanco/Negro";
    }
    else
    {
        shortest_queue = Buffer_circ_rgb;
        longest_queue = Buffer_circ_bn;
        shortest_name = "RGB";
    }
        
    if (!is_full(shortest_queue))
    {
        printf("[IND] Buffer de menor cola: %s - Disponible, poniendo dato\n", shortest_name);
        put_item(data, shortest_queue);
    }
    else
    {
        printf("[IND] Buffer de menor cola: %s - Lleno, poniendo dato en el otro\n", shortest_name);
        put_item(data, longest_queue);
    }
    
    return 0;
}


int put_item_bn(WorkInfo data, buff *Buffer_circ_bn, buff *Buffer_circ_rgb)
{
    if(is_empty(Buffer_circ_rgb))
    {
        printf("[BN] Buffer RGB vacío, introduciendo dato en RBG\n");
        put_item(data, Buffer_circ_rgb);
    }
    else
    {
        put_item(data, Buffer_circ_bn);
    }
    
    return 0;
}