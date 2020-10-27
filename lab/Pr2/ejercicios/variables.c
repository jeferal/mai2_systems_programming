#include <stdio.h> 


// Esta función incrementa el valor de la variable global a en 1
int inc_a(int a) {
    a++;
}
// Esta función devuelve el valor anterior 
// y guarda el Nuevo valor v

int valor_anterior(int v) {
    int temp;
    static int s;
    temp = s;
    s = v;
    return temp;
}


void main(){
    int a = 3;
    int b = 2; /* variable local */
    
    a = inc_a(a);
    valor_anterior(b);
    
    printf("a= %d, b= %d\n", a, b);
    a++;
    b++;
    
    a = inc_a(a);
    
    b = valor_anterior(b);
    printf("a= %d, b= %d\n", a, b);

}
