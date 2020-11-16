#include <stdio.h>
#include <pthread.h>


int Globalvariable=0;

void *Addition(void *ptr)
{ int i, aux_variable;
  int *iter=(int *)ptr;
 
     for(i=0; i<*iter; i++)
       {aux_variable=Globalvariable;
        aux_variable++;
        Globalvariable= aux_variable;
         }
 
  pthread_exit(0); //opcional
 }




int main ()
{ long iterations = 20000000;
  pthread_t t1,t2;
  pthread_attr_t attr;

  pthread_attr_init(&attr);
  pthread_create(&t1,NULL,Addition, &iterations);
  pthread_create(&t2, NULL,Addition, &iterations);

  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  
 
 fprintf(stderr, "Globalvariable = %d\n",Globalvariable);
 return(0);

}
