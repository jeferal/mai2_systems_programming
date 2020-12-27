/*
gcc -o build/project main_2.c buffer_struct/buffer_circular.c printer/printer.c -lpthread
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#include "buffer_struct/buffer_circular.h"

#define N1 20   //Tareas_BN
#define N2 20   //Tareas_RGB
#define N3 20   //Tareas_IND

#define MIN_PG 20
#define MAX_PG 100

int main()
{
    //srand initialization
    srand(time(NULL));

    for(int i=0; i<120; i++)
    {
        int r = rand() % (MAX_PG - MIN_PG + 1) + MIN_PG;
        printf("Número de páginas: %d\n", r);
    }
    return 0;
}