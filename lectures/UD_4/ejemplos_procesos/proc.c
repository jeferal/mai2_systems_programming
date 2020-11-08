#include <stdio.h>
#include <unistd.h>

main ()
{int x,y;
 x=0;
 sleep(10);
 printf("Valor de x antes del fork %d\n",x);
 y= fork();
 sleep(10);
 x=1;
 printf("Valor de x despues del fork %d\n",x);
}
