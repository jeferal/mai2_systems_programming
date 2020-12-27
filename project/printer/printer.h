#define N1 20   //Tareas_BN
#define N2 20   //Tareas_RGB
#define N3 20   //Tareas_IND


typedef enum sheet_t{
    BN, RGB, IND
} sheet_t;

typedef struct WorkInfo{
    int pages;
    sheet_t color;
    int id;
} WorkInfo;

void *tasks(void *ptr);
void *printer(void *ptr);