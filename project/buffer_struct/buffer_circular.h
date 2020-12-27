#ifndef _BUFFER_H_
#define _BUFFER_H_

/*
Estructura de buffer circular con sincronización con mutex
*/

#include <stdbool.h>
#include <pthread.h>

#include "../printer/printer.h"

#define BUF_SIZE 10

typedef struct buff{
    //Hacer array de punteros void?? Para más generalidad de buffer
    WorkInfo data_array[BUF_SIZE];
    int buf_in;
    int buf_out;
    int contador;
    pthread_mutex_t buffer_lock;
    pthread_cond_t lleno, vacio;
} buff;

int get_item(WorkInfo *data, buff *Buffer_Circ);

int put_item(WorkInfo data, buff *Buffer_Circ);

int show_content(const buff *Buffer_Circ);

bool is_empty(const buff *Buffer_Circ);

bool is_full(const buff *Buffer_Circ);

int get_counter(const buff *Buffer_Circ);

void inicializar_buffer(buff *Buffer_Circ);

#endif