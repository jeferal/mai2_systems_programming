#include <stdio.h>

#include "printer.h"
#include "../buffer_struct/buffer_circular.h"

WorkInfo produce_task(sheet_t color)
{
    WorkInfo task;
    task.id = rand() % (ID_MAX - ID_MIN + 1) + ID_MIN;
    task.pages = rand() % (PG_MAX - PG_MIN + 1) + PG_MIN;
    task.color = color;
    
    return task;
}

void show_task(WorkInfo *task)
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

        //Introduce task in the buffer
        show_task(&print_sheets);

    }
    
    pthread_exit(NULL);
}
