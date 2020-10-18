#include <stdio.h>

void main() {   
  int x; /*variable entera*/
  int y;/*variable entera*/
  int *px; /* puntero a entero*/
  x=7;
  px=&x;/*px=direccion de x*/
  y=*px;/* y contiene el dato apuntado por px*/
 
  printf("x=%d\n",x);
  printf("y=%d\n",y);
  printf("*px=%d\n",*px);   
  printf("px = %p\n", px); 
  printf("Dirección de X = %p\n", &x);  

}
