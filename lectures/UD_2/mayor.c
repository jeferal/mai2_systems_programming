#include <stdio.h>

int mayor(int x, int y);

void main(){
    int num;
    num = mayor(10,2);
    printf("El número mayor de (10,2) = %d \n", num);
}

int mayor(int x, int y){
    int temp=-1;
    if (x>y) temp = x;
    if (y>x) temp = y;
    return temp;
}
