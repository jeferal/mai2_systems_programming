#define BUF_SIZE 10

typedef struct{
    int vector_circular[BUF_SIZE];
    int buf_in;
    int buf_out;
    int contador;
} buff;

int get_item(int *data, buff *Buffer_Circ);

int put_item(int data, buff *Buffer_Circ);

int get_size( buff *Buffer_Circ);

int mostrar_contenido(buff *Buffer_Circ);
