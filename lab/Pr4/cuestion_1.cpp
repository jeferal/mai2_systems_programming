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


void *Productor(void *ptr){
    //Cast
    buff *almacen;
    almacen = (buff *)ptr;
    for(int i=0; i<NITER; i++){
        while(get_counter(almacen)==BUF_SIZE);
        //Sección crítica
        put_item(i, almacen);
        printf("Se ha insertado el dato: %d\n", i);
        //Sección crítica
        usleep(2000000);
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
        printf("Se ha cogido el dato: %d\n", i);
        //Sección crítica
        usleep(4000000);
    }
    return NULL;
}


int main(){

    buff alm;

    inicializar_buffer(&alm);

    pthread_t hilo_productor;
    pthread_t hilo_consumidor;
    pthread_attr_t atrib;

    pthread_attr_init(&atrib);

    int i=0;

    printf("Creando hilos\n");
    pthread_create( &hilo_productor, &atrib, Productor, &alm);
    pthread_create( &hilo_consumidor, &atrib, Consumidor, &alm);

    pthread_join(hilo_productor, NULL);
    pthread_join(hilo_consumidor, NULL);

    show_content(&alm);

    return 0;    
}