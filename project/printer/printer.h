#ifndef _PRINTER_H_
#define _PRINTER_H_

/*
Estructuras que modelan la impresora y el sistema
*/


#include <stdlib.h>
#include <pthread.h>
#include "../buffer_struct/circular_buffer.h"

#define PAGES_PRINTER 500

#define N1 100   //Tasks BN (Threads)
#define N2 20   //Tasks RGB (Threads)
#define N3 45   //Tasks IND (Threads)
#define N_PRINTS 20

#define PG_MIN 20
#define PG_MAX 100

#define ID_MIN 0
#define ID_MAX 1000

#define HIST_SIZE 10000

#define SPEED 1000000


typedef struct Printer{
    sheet_t type;
    int pages_available;
    buff queue;
    WorkInfo history[(N1+N2+N3)*N_PRINTS];
    int n_history_saved;
    int n_paper_boxes;
} Printer;

typedef struct PrinterSystem{
    Printer bn_printer_machine;
    Printer rgb_printer_machine;
    int speed;
} PrinterSystem;

void init_printer_machine(Printer *printer_machine, sheet_t color_type);

void *bn_tasks(void *ptr);
void *rgb_tasks(void *ptr);
void *ind_tasks(void *ptr);
WorkInfo produce_task(const sheet_t color);
void show_task(const WorkInfo *task);

void *bn_printer(void *ptr);
void *rgb_printer(void *ptr);
long print_task(const sheet_t color, const int pages, int *pages_available,  Printer *printer, const int speed);

#endif