#ifndef _PRINTER_H_
#define _PRINTER_H_

#include <stdlib.h>

#define N1 20   //Tareas_BN
#define N2 20   //Tareas_RGB
#define N3 20   //Tareas_IND

#define MIN_PG 20
#define MAX_PG 100

typedef enum sheet_t{
    BN, RGB, IND
} sheet_t;

typedef struct WorkInfo{
    int pages;
    sheet_t color;
    int id;
} WorkInfo;

void *bn_tasks(void *ptr);
void *rgb_tasks(void *ptr);
void *ind_tasks(void *ptr);

void *bn_printer(void *ptr);
void *rgb_printer(void *ptr);

#endif