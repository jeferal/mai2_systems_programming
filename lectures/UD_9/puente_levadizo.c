#include <pthread.h>
#include <semaphore.h>

#define NUM_COCHES 5
#define NUM_BARCOS 5

void bajar_puente (void) { }
void pasar (void) { }
void levantar_puente (void) { }

sem_t turno; /*Necesario para dar prioridad a barcos*/
sem_t mutex1; /*Exclusión mutua entre coches*/
sem_t mutex2; /*Exclusión mutua entre barcos*/
sem_t libre; /*Indica puente libre*/
int barcos=0; /*contabiliza los barcos que desean pasar*/
int coches=0; /*contabiliza los coches que desean pasar*/

void *hilo_coches(void *arg)
{
sem_wait(&turno);
sem_post(&turno)
sem_wait(&mutex1);
coches++;
if (coches==1 )
{sem_wait(&libre);
bajar_puente();}
sem_post(&mutex1);
pasar_puente();
sem_wait(&mutex1);
coches- -;
if(coches==0 )
sem_post(&libre);
sem_post(&mutex1);
}

void *hilo_barcos(void *arg)
{
    sem_wait(&mutex2);
    barcos++;
    if barcos==1 {
        sem_wait(&turno);
        sem_wait(&libre);
        levantar_puente();
    }
    sem_post(&mutex2);
    pasar_puente();
    sem_wait(&mutex2);
    barcos - -;
    if (barcos==0) {
        sem_post(&turno);
        sem_post(&libre);
    }
    sem_post(&mutex2);
}


int main (void){ 
    pthread_t id_barcos[NUM_BARCOS], id_coches[NUM_COCHES];
    pthread_attr_t attr;
    int i, j;

    pthread_attr_init(&attr);
    sem_init (&turno,0,1); sem_init (&mutex1,0,1);
    sem_init (&mutex2,0,1); sem_init (&libre,0,1);
    i=NUM_BARCOS; j =NUM_COCHES;
    while (i>=0 || j>=0) {
        if (i>=0) {
            pthread_create(&id_barcos[i],&attr,hilo_barco,NULL);
            i--; 
        }
        if (j>=0) {
            pthread_create(&id_coches[j],&attr,hilo_coche,NULL);
            j--; 
        }
    }
    for (i=0;i<NUM_BARCOS;i++) pthread_join(id_barcos[i],NULL);
    for (j=0;j<NUM_COCHES;j++) pthread_join(id_coches[j],NULL);
    return(0);
}