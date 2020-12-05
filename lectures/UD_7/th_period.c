#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//Función del hilo
void *func_period(void *arg)
{
   int period;
   period = *((int *)arg);
   for(int i=0; i<10; i++)
   {
      printf("Pthread(period %d):", period);
      printf(" %ld\n", (long) pthread_self());
      sleep(period);
   }
   pthread_exit(NULL);
}

int main()
{
   pthread_t t1, t2;
   pthread_attr_t attr;
   int period1=1, period2=2;

   if(pthread_attr_init(&attr) != 0)
   {
      printf("Error: atributtes\n");
      exit(1);
   }

   if(pthread_create(&t1, &attr, func_period, &period1) != 0)
   {
      printf("Error: creating first pthread\n");
      exit(1);
   }

   if(pthread_create(&t2, &attr, func_period, &period2) != 0)
   {
      printf("Error: creating second pthread\n");
      exit(1);
   }

   pthread_join(t1, NULL);
   pthread_join(t2, NULL);

   printf("Both threads finished\n");

   return 0;
}