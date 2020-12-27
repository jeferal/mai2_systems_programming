/*
gcc -o build/project main.c buffer_struct/buffer_circular.c printer/printer.c -lpthread
*/
//Create make file!!

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#include "buffer_struct/buffer_circular.h"
#include "printer/printer.h"

int main()
{
    //srand initialization
    srand(time(NULL));

    buff buffer_1;

    inicializar_buffer(&buffer_1);

    pthread_t bn_producer;
    pthread_attr_t attrib;

    pthread_attr_init(&attrib);

    pthread_create(&bn_producer, &attrib, bn_tasks, &buffer_1);

    pthread_join(bn_producer, NULL);

    printf("All threads have finished\n");

    return 0;
}