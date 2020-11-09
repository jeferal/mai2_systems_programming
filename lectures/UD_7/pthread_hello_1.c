#include <stdio.h>
#include <pthread.h>
#include <string.h>
 
void *My_Print (void *ptr)
{char *message;

 message =(char *) ptr;
 sleep(5);
 write(1,message,strlen(message));
 
}

int main()
{ 
  pthread_t pthread1, pthread2;
  pthread_attr_t attr;
  
  //fprintf(stderr, "Main pthread --> creating thread\n");
  pthread_attr_init(&attr);
  pthread_create(&pthread1, &attr, My_Print,"Hello ");
  pthread_create(&pthread2, &attr,My_Print,"World \n");
  sleep(10);

   return(0); 

}
