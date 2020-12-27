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

    buff buffer_printer_bn;
    buff buffer_printer_rgb;

    inicializar_buffer(&buffer_printer_bn);
    inicializar_buffer(&buffer_printer_rgb);

    pthread_t bn_producer, rgb_producer, ind_producer, bn_printer_machine, rgb_printer_machine;
    pthread_attr_t attrib;

    pthread_attr_init(&attrib);

    printf("Starting threads\n");
    //Producers
    pthread_create(&bn_producer, &attrib, bn_tasks, &buffer_printer_bn);
    pthread_create(&rgb_producer, &attrib, rgb_tasks, &buffer_printer_rgb);
    //pthread_create(&ind_producer, &attirb, ind_tasks, );

    //Consumers
    pthread_create(&bn_printer_machine, &attrib, bn_printer, &buffer_printer_bn);
    pthread_create(&rgb_printer_machine, &attrib, rgb_printer, &buffer_printer_rgb);
    //pthread_create(&ind_producer, &attrib, ind_tasks, &buffer_printer_bn);

    pthread_join(bn_producer, NULL);
    pthread_join(rgb_producer, NULL);

    printf("Producers threads have finished\n");

    return 0;
}