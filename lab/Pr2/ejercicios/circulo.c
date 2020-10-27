#include <stdio.h>

#define PI 3.1416

void main(){
    float area, radio;
    radio = 10;
    area = PI*radio*radio;
    printf("Area del círculo de radio %f es %f\n", radio, area);
}
