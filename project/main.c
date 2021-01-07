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
#include <sys/types.h>

#include "printer/printer.h"


//Global variable
PrinterSystem printer_machines;

void finish_process (int signal)
{
    sleep(2);
    
    printf("\n\n--------Finishing process--------\n\n");
    printf("These tasks where launched { BN: %d, IND: %d, RGB: %d and %d prints each task }\n\n", N1, N2, N3, N_PRINTS);
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
    printf("\nBN has consumed %d paper boxes\n", printer_machines.bn_printer_machine.n_paper_boxes);
    
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
    printf("\nRGB has consumed %d paper boxes\n", printer_machines.rgb_printer_machine.n_paper_boxes);

    printf("\n--------Process finished--------\n\n");

    exit(1);
}


int main(int argc, char *argv[])
{   
    //Check arg inputs
    if (argc != 2){
        printf("Wrong input.\nUsage: ./build/project SPEED\n");
        exit(1);
    }

    int speed = atoi(argv[1]);

    if (speed < 1 || speed > 1000000){
        printf("Wrong SPEED, it must be [1 - 1000000]\n");
        exit(1);
    }

    printer_machines.speed = speed;

    //Start program

    printf("[MAIN] Process started with Pid: [%ld]\n", (long)getpid());
    printf("\n[MAIN] Launching BN: %d, IND: %d, RGB: %d and %d prints each task\n", N1, N2, N3, N_PRINTS);

    signal(SIGINT, finish_process);

    //Init printers (and its buffers inside)
    init_printer_machine(&printer_machines.bn_printer_machine, BN);
    init_printer_machine(&printer_machines.rgb_printer_machine, RGB);

    //Create threads
    pthread_t bn_producer[N1], rgb_producer[N2], ind_producer[N3], bn_printer_machine, rgb_printer_machine;
    pthread_attr_t attrib;

    pthread_attr_init(&attrib);

    printf("\n[MAIN] Starting threads\n\n");

    //Producers
    for(int i=0; i<N1; i++)
        pthread_create(&bn_producer[i], &attrib, bn_tasks, &printer_machines);

    for(int i=0; i<N2; i++)
        pthread_create(&rgb_producer[i], &attrib, rgb_tasks, &printer_machines.rgb_printer_machine);

    for(int i=0; i<N3; i++)
        pthread_create(&ind_producer[i], &attrib, ind_tasks, &printer_machines);

    //Consumers
    pthread_create(&bn_printer_machine, &attrib, bn_printer, &printer_machines);
    pthread_create(&rgb_printer_machine, &attrib, rgb_printer, &printer_machines);


    //Wait producers
    for(int i=0; i<N1; i++)
        pthread_join(bn_producer[i], NULL);

    for(int i=0; i<N2; i++)
        pthread_join(rgb_producer[i], NULL);

    for(int i=0; i<N3; i++)
        pthread_join(ind_producer[i], NULL);

    //Wait consumers
    while ((printer_machines.bn_printer_machine.n_history_saved + printer_machines.rgb_printer_machine.n_history_saved < N1 + N2 + N3)
            && get_counter(&printer_machines.bn_printer_machine.queue) > 0 && get_counter(&printer_machines.rgb_printer_machine.queue) > 0);

    finish_process(0);

    exit(0);
}