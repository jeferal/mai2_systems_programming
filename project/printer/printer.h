#ifndef _PRINTER_H_
#define _PRINTER_H_

#include <stdlib.h>
#include <pthread.h>
#include "../buffer_struct/buffer_circular.h"

#define PAGES_PRINTER 500

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

typedef struct Printer {
    sheet_t color;
    int sheets_available;
    buff queue;
} Printer;

void init_printer(Printer *printer_machine, const sheet_t color);

void *bn_tasks(void *ptr);
void *rgb_tasks(void *ptr);
void *ind_tasks(void *ptr);
WorkInfo produce_task(const sheet_t color);
void show_task(const WorkInfo *task);

void *bn_printer(void *ptr);
void *rgb_printer(void *ptr);
void print_task(const sheet_t color, const int pages);

#endif