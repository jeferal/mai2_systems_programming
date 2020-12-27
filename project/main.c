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

    for(int i=0; i<120; i++)
    {
        int r = rand() % (MAX_PG - MIN_PG + 1) + MIN_PG;
        printf("Número de páginas: %d\n", r);
    }
    return 0;
}