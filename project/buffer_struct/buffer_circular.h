#ifndef _BUFFER_H_
#define _BUFFER_H_

/*
Estructura de buffer circular con sincronización con mutex
*/

#include <stdbool.h>
#include <pthread.h>
#include <time.h>

#define BUF_SIZE 10


typedef enum sheet_t{
    BN, RGB, IND
} sheet_t;

typedef struct WorkInfo{
    int pages;
    sheet_t color;
    int id;
} WorkInfo;

typedef struct buff{
    WorkInfo data_array[BUF_SIZE];
    int buf_in;
    int buf_out;
    int contador;
    pthread_mutex_t buffer_lock;
    pthread_cond_t lleno, vacio;
} buff;

int get_item(WorkInfo *data, buff *Buffer_Circ);

int put_item(WorkInfo data, buff *Buffer_Circ);

int put_item_ind(WorkInfo data, buff *Buffer_circ_1, buff *Buffer_circ_2);

int show_content(const buff *Buffer_Circ);

bool is_empty(const buff *Buffer_Circ);

bool is_full(const buff *Buffer_Circ);

int get_counter(const buff *Buffer_Circ);

void inicializar_buffer(buff *Buffer_Circ);

int get_pages_queue(buff *Buffer_Circ);

long getCurrentMicroseconds(void);

int put_item_bn(WorkInfo data, buff *Buffer_circ_bn, buff *Buffer_circ_rgb);

#endif