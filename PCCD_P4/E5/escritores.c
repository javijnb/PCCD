#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

sem_t semaforo;
sem_t semaforo_escritura[10];
sem_t semaforo_salida[10];
void* thread(int*);

int main(int argc,char* argv[]){
    
    
    int N3 = 0;
    int error, opcion, escritor, i = 0;
    N3 = atoi(argv[1]);
    pthread_t hilos[N3];

    printf("Escritores totales posibles en el sistema: %d\n", N3);

    sem_init(&semaforo,0,1); //Solo puede haber uno escribiendo

    for (i = 0; i < N3; i++) {
      error=pthread_create(&hilos[i],NULL,(void*)thread,(void*)i+1);

      if(error!=0){
        printf("No ha sido posible crear el hilo %d\n", i);
        return 0;

      }else{
        sem_init(&semaforo_escritura[i],0,0);
        sem_init(&semaforo_salida[i],0,0);
      }
    }

    while(1){
    printf("1.Intentar escribir\n");
    printf("2.Finalizar escribir\n");
    printf("3.Salir\n");
    scanf("%i",&opcion);

    switch(opcion){

      case 1:
      printf("\tIntroduzca el número del escritor (del 1 al %i): ",N3);
      scanf("%i",&escritor);

      sem_post(&semaforo_escritura[escritor]);
      break;

      case 2:
      printf("\tIntroduzca el numero del escritor (del 1 al %i): ",N3);
      scanf("%i",&escritor);
      sem_post(&semaforo_salida[escritor]);
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
    printf("[Escritor %i] -> Esperando a intentar escribir...\n",(int)parametro);

  	sem_wait(&semaforo_escritura[(int)parametro]);

  	printf("[Escritor %i] -> Intentando escribir...\n",(int)parametro);

  	sem_wait(&semaforo);

  	printf("[Escritor %i] -> Escribiendo...\n",(int)parametro);

  	sem_wait(&semaforo_salida[(int)parametro]);

  	printf("[Escritor %i] -> Fin escritura\n",(int)parametro);

  	sem_post(&semaforo);
  }
  pthread_exit(NULL);
}