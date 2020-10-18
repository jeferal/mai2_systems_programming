#include <stdio.h>

void main(){
    int Datos[5] = {1,2,3,4,5};
    int *p;
    int i;
    int size;
    
    p = Datos; //apunta a Datos (*p=Datos[0]=1)
    p = Datos+2; //apunta al 3er elemento(*p3)
    size = (int)(sizeof(Datos)/sizeof(int));
    
    for (i = 0; i < size; i++) {
        printf("Datos[%u]=%u", i, Datos[i]);
        printf("Datos[%u]=%u", i, *p++);
        }
}
