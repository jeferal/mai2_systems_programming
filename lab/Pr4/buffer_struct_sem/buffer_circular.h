/*
Estructura de buffer circular con sincronización con mutex
*/

#include <stdbool.h>
#include <semaphore.h>

#define BUF_SIZE 10

typedef struct{
    int vector_circular[BUF_SIZE];
    int buf_in;
    int buf_out;
    int contador;
    //Protección con semáforos
    sem_t mutex, items, huecos;
} buff;

int get_item(int *data, buff *Buffer_Circ);

int put_item(int data, buff *Buffer_Circ);

int show_content(const buff *Buffer_Circ);

bool is_empty(const buff *Buffer_Circ);

bool is_full(const buff *Buffer_Circ);

int get_counter(const buff *Buffer_Circ);

void inicializar_buffer(buff *Buffer_Circ);