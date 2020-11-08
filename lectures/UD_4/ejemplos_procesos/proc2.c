#include <stdio.h>
#include <unistd.h>
#include <errno.h>

main ()
{int pidhijo;
 
 printf("Soy el proceso %d y voy a crear un hijo\n",getpid());
 
 if((pidhijo= fork())==0)
  { fprintf(stderr,"Soy el hijo mi PID es %d\n", getpid());
    
  //Codigo del hijo va aqui
  }else if (pidhijo>0)

 { fprintf(stderr,"Soy el padre  mi PID es %d\n", getpid());
    //Codigo del padre va aqui
 }
 sleep(10);
 printf("SOY YO %d\n",getpid());
}
