#include <stdio.h>
#include "area.h"
#define PI 3.1416

void main(){
    float area_cir, radio;
    radio = 10;
    area_cir = area(radio);
    printf("Area del círculo de radio %f es %f\n", radio, area_cir);
}
