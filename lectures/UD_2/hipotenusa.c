#include <stdio.h>
#include <math.h>


void hipotenusa(float a, float b, float *h){
    *h = sqrt(pow(a,2) + pow(b, 2));
}

void leer (float *a, float *b) {
    printf("Dame valores a y b:\n");
    scanf("%f %f", a, b);
    //scanf("%f %f", *&a, *&b);
}


void main() {
    float a, b, h;
    leer (&a,&b);
    hipotenusa(a,b,&h);
    printf("La hipotenusa es %f\n", h);
}
