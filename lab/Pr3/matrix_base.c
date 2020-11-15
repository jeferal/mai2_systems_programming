#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define COLUMNAS 80
#define FILAS 25

char m[FILAS][COLUMNAS];
long retardo[COLUMNAS];
int fila_b[COLUMNAS];

pthread_attr_t atrib;
pthread_t  hilo_dibujador[COLUMNAS];
pthread_t  hilo_borrador[COLUMNAS];
pthread_t  hilo_refrescador;

void *Borrador(void *ptr)
{
  int fila, col=(int)(long)ptr;
  for(fila=0;fila<FILAS;fila++){
    m[fila][col]= ' '; //Escribir un espacio
    usleep(retardo[col]); //Esperar antes del siguiente borrado
  }
}

void *Dibujador(void *ptr)
{
  int fila, col=(int)(long)ptr;
  retardo[col]= 50000+rand()%450000; //Retardo aleatorio de carácter, de 0,05s a 0,5s
  if (rand()%10>4) //A veces, no dibujar la columna
    usleep(retardo[col]*FILAS); //Esperar sin dibujar
  else{
    for(fila=0;fila<FILAS;fila++){
      m[fila_b[col]=fila][col]= 32+rand()%94; //Escribir nuevo carácter aleatorio
      usleep(retardo[col]); //Esperar antes del siguiente carácter
    }
  }
}

void *RefrescadorDePantalla(void *ptr)
{
  int fila, col;
  char orden[20];
  while(1){
    write(1,"\033[1;1f\033[1;40;32m",16); //Volver a esquina superior izquierda, texto verde
    for(fila=0;fila<FILAS;fila++){
      write(1,m[fila],COLUMNAS); write(1,"\n",1); //Refrescar fila
    }
    write(1,"\033[1;37m",7); //Texto blanco
    for(col=0;col<COLUMNAS;col++){
      sprintf(orden,"\033[%d;%df%c",fila_b[col]+1,col+1,m[fila_b[col]][col]); 
      if(fila_b[col]<FILAS-1) write(1,orden,strlen(orden)); //Reescribir en blanco el último carácter de la columna
    }
    usleep(100000); //Esperar 0,1s antes de volver a refrescar
  }
}

int main()
{
  int col;
  memset (m,' ',FILAS*COLUMNAS); //Borrar la matriz m
  write(1,"\033[2J\033[?25l",10); //Borrar pantalla, ocultar cursor 
  
  pthread_attr_init(&atrib);
  
  //Crear un hilo dibujador para cada columna

  //Crear un hilo refrescador de pantalla

  //Esperar la finalización de los hilos dibujadores
  
  write(1,"\033[0m\033[?25h\r",11); //Restaurar texto normal, restaurar cursor
}



