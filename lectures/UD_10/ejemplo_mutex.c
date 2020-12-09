#include "pthread.h"
#include <stdio.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
int V = 100;

void *fhilo1(void *p)
{
    int c;
    for(c=0; c<1000; c++) 
    {
        pthread_mutex_lock(&m);
        V = V + 1;
        pthread_mutex_unlock(&m);
    }
    pthread_exit(0);
}

void *fhilo2(void *p)
{
    int c;
    for(c=0; c<1000; c++) {
        pthread_mutex_lock(&m);
        V = V - 1;
        pthread_mutex_unlock(&m);
    }
    pthread_exit(0);
} 

int main ( ) {

    pthread_t hilo1, hilo2;
    pthread_attr_t atributos;
    pthread_attr_init(&atributos);

    pthread_create(&hilo1, &atributos, fhilo1, NULL);
    pthread_create(&hilo2, &atributos, fhilo2, NULL);

    pthread_join(hilo1,NULL);
    pthread_join(hilo2,NULL);

    printf("Value of V: %d\n", V);
} 