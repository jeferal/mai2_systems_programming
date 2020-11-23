#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>

#include "buffer_struct/buffer_circular.h"

#define NITER 30

sem_t mutex, items, huecos;
buff alm;

void *Productor(void *ptr){
    for(int i=0; i<NITER; i++){
        sem_wait(&huecos);
        sem_wait(&mutex);
        //Sección crítica
        put_item(i, ptr);
        printf("Se ha insertado el dato: %d\n", i);
        //Sección crítica
        sem_post(&mutex);
        sem_post(&items);
        usleep(2000000);
    }
    //return NULL;
}

void *Consumidor(void *ptr){
    int dato;
    for(int i=0; i<NITER; i++){
        sem_wait(&items);
        sem_wait(&mutex);
        //Sección crítica
        get_item(&dato, ptr);
        printf("Se ha cogido el dato: %d\n", i);
        //Sección crítica
        sem_wait(&mutex);
        sem_wait(&huecos);
        usleep(4000000);
    }
    //return NULL;
}


int main(){

    printf("Comenzando programa");

    sem_init(&mutex, 0, 1);
    sem_init(&huecos, 0, BUF_SIZE);
    sem_init(&items, 0, 0);

    pthread_t hilo_productor;
    pthread_t hilo_consumidor;
    pthread_attr_t atrib;

    pthread_attr_init(&atrib);

    printf("Creando hilos");
    int i=0;

    pthread_create( &hilo_productor, &atrib, Productor, &alm);
    pthread_create( &hilo_consumidor, &atrib, Consumidor, &alm);

    pthread_join(hilo_productor, NULL);
    pthread_join(hilo_consumidor, NULL);

    sem_destroy(&mutex);
    sem_destroy(&huecos);
    sem_destroy(&items);

    return 0;
    
}