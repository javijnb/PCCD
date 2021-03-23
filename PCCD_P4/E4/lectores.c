#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

sem_t semaforo;
sem_t semaforo_lectura[10];
sem_t semaforo_salida[10];
void* thread(int*);

int main(int argc,char* argv[]){
    
    
    int N1, N2 = 0;
    int error, opcion, lector, i = 0;
    N1 = atoi(argv[1]);
    N2 = atoi(argv[2]);
    pthread_t hilos[N1];

    printf("Lectores totales posibles en el sistema: %d\n", N1);
    printf("Lectores máximos simultáneos: %d\n", N2);

    sem_init(&semaforo,0,N2);

    for (i = 0; i < N1; i++) {
      error=pthread_create(&hilos[i],NULL,(void*)thread,(void*)i+1);

      if(error!=0){
        printf("No ha sido posible crear el hilo %d\n", i);
        return 0;

      }else{
        sem_init(&semaforo_lectura[i],0,0);
        sem_init(&semaforo_salida[i],0,0);
      }
    }

    while(1){
    printf("1.Intentar leer\n");
    printf("2.Finalizar leer\n");
    printf("3.Salir\n");
    scanf("%i",&opcion);

    switch(opcion){

      case 1:printf("\tIntroduzca el número del lector (del 1 al %i): ",N1);
      scanf("%i",&lector);

      //sem_post()  increments  (unlocks)  the  semaphore pointed to by sem.  If the semaphore's value consequently becomes greater than zero, then another
      //process or thread blocked in a sem_wait(3) call will be woken up and proceed to lock the semaphore.
      sem_post(&semaforo_lectura[lector]);
      break;

      case 2:printf("\tIntroduzca el numero del lector (del 1 al %i): ",N1);
      scanf("%i",&lector);
      sem_post(&semaforo_salida[lector]);
      break;

      case 3:
      pthread_exit(NULL);
      return 0;
    }
  }

    return 0;
}

void* thread(int* parametro){
    sleep(1);
  while(1){
    printf("[Lector %i] -> Esperando a intentar leer...\n",(int)parametro);

    /*sem_wait() decrements (locks) the semaphore pointed to by sem.  If the semaphore's value is greater than zero, then the decrement proceeds, and the
       function returns, immediately.  If the semaphore currently has the value zero, then the call blocks until either it becomes possible to perform the
       decrement (i.e., the semaphore value rises above zero), or a signal handler interrupts the call.*/
  	sem_wait(&semaforo_lectura[(int)parametro]);

  	printf("[Lector %i] -> Intentando leer...\n",(int)parametro);
  	sem_wait(&semaforo);

  	printf("[Lector %i] -> Leyendo...\n",(int)parametro);
  	sem_wait(&semaforo_salida[(int)parametro]);

  	printf("[Lector %i] -> Fin lectura\n",(int)parametro);
  	sem_post(&semaforo);
  }
  pthread_exit(NULL);
}