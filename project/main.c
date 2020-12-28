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

#include "printer/printer.h"

int main()
{
    //srand initialization
    srand(time(NULL));

    PrinterSystem printer_machines;

    //Init printers (and its buffers inside)
    init_printer_machine(&printer_machines.bn_printer_machine, BN);
    init_printer_machine(&printer_machines.rgb_printer_machine, RGB);

    pthread_t bn_producer, rgb_producer, ind_producer, bn_printer_machine, rgb_printer_machine;
    pthread_attr_t attrib;

    pthread_attr_init(&attrib);

    printf("Starting threads\n");
    //Producers
    pthread_create(&bn_producer, &attrib, bn_tasks, &printer_machines.bn_printer_machine);
    pthread_create(&rgb_producer, &attrib, rgb_tasks, &printer_machines.rgb_printer_machine);
    pthread_create(&ind_producer, &attrib, ind_tasks, &printer_machines);

    //Consumers
    pthread_create(&bn_printer_machine, &attrib, bn_printer, &printer_machines.bn_printer_machine);
    pthread_create(&rgb_printer_machine, &attrib, rgb_printer, &printer_machines.rgb_printer_machine);

    pthread_join(bn_producer, NULL);
    pthread_join(rgb_producer, NULL);

    printf("Producers threads have finished\n");

    return 0;
}