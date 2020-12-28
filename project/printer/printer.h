#ifndef _PRINTER_H_
#define _PRINTER_H_

#include <stdlib.h>
#include <pthread.h>
#include "../buffer_struct/buffer_circular.h"

#define PAGES_PRINTER 100

#define N1 20   //Tareas_BN
#define N2 20   //Tareas_RGB
#define N3 20   //Tareas_IND

#define PG_MIN 20
#define PG_MAX 100

#define ID_MIN 0
#define ID_MAX 1000

#define HIST_SIZE 100


typedef struct Printer{
    sheet_t type;
    int pages_available;
    buff queue;
    WorkInfo history[HIST_SIZE];
    int n_history_saved;
    int n_paper_boxes;
} Printer;

typedef struct PrinterSystem{
    Printer bn_printer_machine;
    Printer rgb_printer_machine;
} PrinterSystem;

void init_printer_machine(Printer *printer_machine, sheet_t color_type);

void *bn_tasks(void *ptr);
void *rgb_tasks(void *ptr);
void *ind_tasks(void *ptr);
WorkInfo produce_task(const sheet_t color);
void show_task(const WorkInfo *task);

void *bn_printer(void *ptr);
void *rgb_printer(void *ptr);
void print_task(const sheet_t color, const int pages, int *pages_available,  Printer *printer);

#endif