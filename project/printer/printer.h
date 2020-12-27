#ifndef _PRINTER_H_
#define _PRINTER_H_

#include <stdlib.h>
#include <pthread.h>

#define N1 20   //Tareas_BN
#define N2 20   //Tareas_RGB
#define N3 20   //Tareas_IND

#define PG_MIN 20
#define PG_MAX 100

#define ID_MIN 0
#define ID_MAX 1000

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
WorkInfo produce_task(sheet_t color);
void show_task(WorkInfo *task);

void *bn_printer(void *ptr);
void *rgb_printer(void *ptr);
void consume_task(WorkInfo *work_sheet);

#endif