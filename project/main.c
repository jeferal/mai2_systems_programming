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
#include <signal.h>

#include "printer/printer.h"

PrinterSystem printer_machines;

void finish_process (int signal)
{
    printf("\n\n--------Finishing process--------\n");
    printf("BN has printed %d tasks with these IDs:\n", printer_machines.bn_printer_machine.n_history_saved);
    //Show IDs BN
    for(int i=0; i<printer_machines.bn_printer_machine.n_history_saved; i++)
    {
        const char* type;
        if (printer_machines.bn_printer_machine.history[i].color == BN)
            type = "BN";
        else if(printer_machines.bn_printer_machine.history[i].color == RGB)
            type = "RGB";
        else
            type = "IND";
        
        printf("(%d - %s) ", printer_machines.bn_printer_machine.history[i].id, type);
    }
    printf("\n BN has consumed %d paper boxes\n", printer_machines.bn_printer_machine.n_paper_boxes);
    
    printf("\n\nRGB has printed %d tasks with these IDs:\n", printer_machines.rgb_printer_machine.n_history_saved);
    for(int i=0; i<printer_machines.rgb_printer_machine.n_history_saved; i++)
    {
        const char* type;
        if (printer_machines.rgb_printer_machine.history[i].color == BN)
            type = "BN";
        else if(printer_machines.rgb_printer_machine.history[i].color == RGB)
            type = "RGB";
        else
            type = "IND";
        printf("(%d - %s) ", printer_machines.rgb_printer_machine.history[i].id, type);
    }
    printf("\n RGB has consumed %d paper boxes\n", printer_machines.rgb_printer_machine.n_paper_boxes);

    printf("\n--------Process finished--------\n\n");

    exit(1);
}

int main()
{
    //srand initialization
    srand(time(NULL));

    signal(SIGINT, finish_process);

    //Init printers (and its buffers inside)
    init_printer_machine(&printer_machines.bn_printer_machine, BN);
    init_printer_machine(&printer_machines.rgb_printer_machine, RGB);

    pthread_t bn_producer, rgb_producer, ind_producer, bn_printer_machine, rgb_printer_machine;
    pthread_attr_t attrib;

    pthread_attr_init(&attrib);

    printf("Starting threads\n");
    //Producers
    pthread_create(&bn_producer, &attrib, bn_tasks, &printer_machines);
    pthread_create(&rgb_producer, &attrib, rgb_tasks, &printer_machines.rgb_printer_machine);
    pthread_create(&ind_producer, &attrib, ind_tasks, &printer_machines);

    //Consumers
    pthread_create(&bn_printer_machine, &attrib, bn_printer, &printer_machines.bn_printer_machine);
    pthread_create(&rgb_printer_machine, &attrib, rgb_printer, &printer_machines.rgb_printer_machine);

    pthread_join(bn_producer, NULL);
    pthread_join(rgb_producer, NULL);
    pthread_join(ind_producer, NULL);

    printf("Producers threads have finished\n");

    sleep(1);
    finish_process(0);

    return 0;
}