#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "buffer_struct/buffer_circular.h"

#define NITER 30

void *productor(void *almacen){
    for(int i=0; i<NITER; i++){
        //Sección crítica
        put_item(i, almacen);
        //Sección crítica
        printf("Se ha insertado el dato: %d", i);
        usleep(2000000);
    }
}

void *consumidor(void *almacen){
    int dato;
    for(int i=0; i<NITER; i++){
        //Sección crítica
        get_item(&dato, almacen);
        //Sección crítica
        printf("Se ha insertado el dato: %d", i);
        usleep(4000000);
    }
}


int main(){

    buff *almacen;

    pthread_attr_t atrib;
    pthread_t hilo_productor, hilo_consumidor;

    pthread_attr_init(&atrib);

    pthread_create( &hilo_productor, &atrib, productor, almacen);
    pthread_create( &hilo_consumidor, &atrib, consumidor, almacen);

    pthread_join(hilo_productor, NULL);
    pthread_join(hilo_consumidor, NULL);

    return 0;
}