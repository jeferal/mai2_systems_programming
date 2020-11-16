/**
* Programa de ejemplo "Hola mundo" con pthreads.
* Para compilar teclea: gcc hola.c -lpthread -o hola
**/

// gcc –o build/hola threads/hola.c –lpthread

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void *Imprime( void *ptr ){
    char *men;
    men=(char*)ptr;
    //EJERCICIO1.b
    usleep(2000000);    //Para que tarde más y no dé tiempo
    write(1,men,strlen(men));
}

int main(){
    pthread_attr_t atrib;
    pthread_t hilo1, hilo2;
    pthread_attr_init( &atrib );
    pthread_create( &hilo1, &atrib, Imprime, "Hola \n");
    pthread_create( &hilo2, &atrib, Imprime, "mundo \n");

    //EJERCICIO1.a  Comentar líneas para ver comporamiento
    //usleep(1000000);    //Espera de tiempo
    pthread_exit(0);
    //pthread_join( hilo1, NULL);
    //pthread_join( hilo2, NULL);
} 