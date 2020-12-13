/*
Práctica 4 C
Compilación:
    gcc -o build/cuestion_1 cuestion_1.c buffer_struct/buffer_circular.c -lpthread
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>

#include "buffer_struct/buffer_circular.h"

#define NITER 30
#define NITER_CONS 15


void *Productor(void *ptr){
    //Cast
    buff *almacen;
    almacen = (buff *)ptr;
    int dato;

    for(int i=0; i<NITER; i++){
        dato = i;
        while(get_counter(almacen)==BUF_SIZE);
        //Sección crítica
        put_item(dato, almacen);
        printf("Se ha insertado el dato: %d\n", dato);
        if(show_content(almacen)==-1)
            printf("El buffer está vacío\n");
        //Sección crítica
        usleep(200);
    }
    return NULL;
}

void *Consumidor(void *ptr){
    //Cast
    buff *almacen;
    almacen = (buff *)ptr;
    int dato;

    for(int i=0; i<NITER; i++){
        while(get_counter(almacen)==0);
        //Sección crítica
        get_item(&dato, almacen);
        printf("Se ha cogido el dato: %d\n", dato);
        //Sección crítica
        usleep(400);
    }
    return NULL;
}


int main(){

    buff alm;

    inicializar_buffer(&alm);

    pthread_t productor_1;
    pthread_t consumidor_1, consumidor_2;
    pthread_attr_t atrib;

    pthread_attr_init(&atrib);

    int i=0;

    printf("Creando hilos\n");
    pthread_create( &productor_1, &atrib, Productor, &alm);
    pthread_create( &consumidor_1, &atrib, Consumidor, &alm);
    pthread_create( &consumidor_2, &atrib, Consumidor, &alm);

    pthread_join(productor_1, NULL);
    pthread_join(consumidor_1, NULL);
    pthread_join(consumidor_2, NULL);

    show_content(&alm);

    return 0;    
}