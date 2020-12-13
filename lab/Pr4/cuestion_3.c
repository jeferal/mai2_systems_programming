/*
Práctica 4 C
Compilación:
    gcc -o build/cuestion_3 cuestion_3.c buffer_struct_sem/buffer_circular.c -lpthread
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>

#include "buffer_struct_sem/buffer_circular.h"

#define NITER_PROD 35
#define NITER_CONS 15


void *Productor(void *ptr){
    //Cast
    buff *almacen;
    almacen = (buff *)ptr;
    int dato;

    for(int i=0; i<NITER_PROD; i++)
    {
        dato = i;
        put_item(dato, almacen);
        printf("Se ha insertado el dato: %d\n", dato);
        usleep(200);
    }
    pthread_exit(NULL);
}

void *Consumidor(void *ptr){
    //Cast
    buff *almacen;
    almacen = (buff *)ptr;
    int dato;
    int data_collected[NITER_CONS];

    for(int i=0; i<NITER_CONS; i++)
    {
        get_item(&dato, almacen);
        printf("Se ha cogido el dato: %d\n", dato);
        data_collected[i] = dato;
        usleep(400);
    }

    //Show all data collected
    for(int i=0; i<NITER_CONS; i++)
        printf("Dato: %d\n", data_collected[i]);
    pthread_exit(NULL);
}


int main(){

    buff alm;

    inicializar_buffer(&alm);

    if(show_content(&alm)==-1)
        printf("El buffer está vacío\n");

    pthread_t productor_1;
    pthread_t consumidor_1, consumidor_2;
    pthread_attr_t atrib;

    pthread_attr_init(&atrib);

    printf("Creando hilos\n");
    pthread_create( &productor_1, &atrib, Productor, &alm);
    pthread_create( &consumidor_1, &atrib, Consumidor, &alm);
    pthread_create( &consumidor_2, &atrib, Consumidor, &alm);

    pthread_join(productor_1, NULL);
    pthread_join(consumidor_2, NULL);
    pthread_join(consumidor_1, NULL);

    printf("Los hilos han terminado\n");

    show_content(&alm);

    return 0;    
}