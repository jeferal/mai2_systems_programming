#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "printer.h"
#include "../buffer_struct/buffer_circular.h"

long getCurrentMicroseconds()
{
    struct timespec currentTime;
    clock_gettime(CLOCK_MONOTONIC, &currentTime);
    return (currentTime.tv_sec)*1000000 + (currentTime.tv_nsec) / 1000;
}

WorkInfo produce_task(const sheet_t color)
{
    WorkInfo task;
    task.id = rand() % (ID_MAX - ID_MIN + 1) + ID_MIN;
    task.pages = rand() % (PG_MAX - PG_MIN + 1) + PG_MIN;
    task.color = color;
    
    return task;
}

void print_task(const sheet_t color, const int pages)
{
    int time;

    if (color == BN)
        time = 1;  // 1 pg/sec
    else
        time = 4;  // 1/4 pg/sec

    sleep(time*pages);
}

void show_task(const WorkInfo *task)
{
    printf("--- TASK --\n");
    printf("ID number: %03d\n", task->id);
    switch (task->color)
    {
        case BN:
            printf("Color type: BN\n");
            break;

        case RGB:
            printf("Color type: RGB\n");
            break;
        
        default:
            printf("Color type: IND\n");
            break;
    }
    printf("Number of pages: %d\n\n", task->pages);
}


void *bn_tasks(void *ptr)
{
    //Casting
    buff *task_buffer = (buff *)ptr;

    for(int i=0; i<N1; i++)
    {
        //Produce task
        WorkInfo print_sheets = produce_task(BN);

        //Put the task in the buffer
        put_item(print_sheets, task_buffer);

        //Introduce task in the buffer
        show_task(&print_sheets);

    }
    
    pthread_exit(NULL);
}

void *rgb_tasks(void *ptr)
{
    //Casting
    buff *task_buffer = (buff *)ptr;

    for(int i=0; i<N2; i++)
    {
        //Produce task
        WorkInfo print_sheets = produce_task(RGB);

        //Put the task in the buffer
        put_item(print_sheets, task_buffer);

        //Introduce task in the buffer
        show_task(&print_sheets);

    }
    
    pthread_exit(NULL);
}


//TODO
void *ind_tasks(void *ptr)
{
    //Casting   TODO
    buff buffer_array[2] = (buff (*)[2]) ptr;

    for(int i=0; i<N3; i++)
    {
        //Produce task
        WorkInfo print_sheets = produce_task(IND);

        //Get queue time of both
        int time_bn = 1*get_pages_queue(buffer_array[0]);
        int time_rgb = 4*get_pages_queue(buffer_array[1]);
        printf("[IND] Time BN: %d (s)\nTime RGB: %d (s)\n", time_bn, time_rgb);

        //Introduce task in the buffer
        show_task(&print_sheets);

    }
    
    pthread_exit(NULL);
}


//Consumers (PRINTERS)
void *bn_printer(void *ptr)
{
    //Casting
    buff *task_buffer = (buff *)ptr;

    //Cambiar while(true)!!!
    while(true)
    {
        WorkInfo data;
        get_item(&data, task_buffer);

        printf("\n[BN] Printing task with ID [%03d] collected\n Number waiting: %d\n\n", data.id, get_counter(task_buffer));

        long t0 = getCurrentMicroseconds();
        print_task(BN, data.pages);
        long printing_time = getCurrentMicroseconds() - t0;
        printf("\n[BN] Finished printing task with ID [%03d], time taken: %ld us", data.id, printing_time);
    }

    pthread_exit(NULL);
}

void *rgb_printer(void *ptr)
{
    //Casting
    buff *task_buffer = (buff *)ptr;

    //Cambiar while(true)!!!
    while(true)
    {
        WorkInfo data;
        get_item(&data, task_buffer);

        printf("\n[RGB] Printing task with ID [%03d] collected\n Number waiting: %d\n\n", data.id, get_counter(task_buffer));

        long t0 = getCurrentMicroseconds();
        print_task(RGB, data.pages);
        long printing_time = getCurrentMicroseconds() - t0;

        printf("\n[RGB] Finished printing task with ID [%03d], time taken: %ld us", data.id, printing_time);
    }

    pthread_exit(NULL);
}
