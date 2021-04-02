#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

//Semaforos de acceso
sem_t sem_general;
sem_t sem_bloq_esc;
sem_t sem_lectura;
sem_t sem_escritura;

//Semaforos para cada lector o escritor
sem_t sem_lec[10];
sem_t sem_lec_sal[10];
sem_t sem_esc[10];
sem_t sem_esc_sal[10];

void* thread_lector(int*);
void* thread_escritor(int*);

int N1, N2, N3, escritura, lectura = 0;

// Invocación: lectores-escritores N1 N2 N3
// N1: numero total de lectores
// N2: numero total de lectores simultáneos en el papel
// N3: numero total de escritores

int main(int argc,char* argv[]){

  N1=atoi(argv[1]);
  N2=atoi(argv[2]);
  N3=atoi(argv[3]);

  pthread_t p_lector[N1], p_escritor[N3];
  
  int i, error, opcion, lector, escritor = 0;
  int idlector[N1], idescritor[N3];

  // Creamos los N1 hilos de lectores
  for (i = 0; i < N1; i++) {

    error=pthread_create(&p_lector[i], NULL, (void*)thread_lector, (void*) i+1);

    if(error!=0){

      printf("No ha sido posible crear el hilo de lectores");
      return 0;

    }else{

      sem_init(&sem_lec[i],0,1);
      sem_init(&sem_lec_sal[i],0,1);
      sem_wait(&sem_lec_sal[i]);
      sem_wait(&sem_lec[i]);

    }
  }

  // Creamos los N3 hilos de escritores
  for (i = 0; i < N3; i++) {

    error=pthread_create(&p_escritor[i], NULL, (void*)thread_escritor, (void*) i+1);
    
    if(error!=0){

      printf("No ha sido posible crear el hilo de escritores");
      return 0;

    }else{

      sem_init(&sem_esc[i],0,1);
      sem_init(&sem_esc_sal[i],0,1);
      sem_wait(&sem_esc_sal[i]);
      sem_wait(&sem_esc[i]);

    }
  }

  sem_init(&sem_escritura,0,1);
  sem_init(&sem_lectura,  0,N2);
  sem_init(&sem_general,  0,1);
  sem_init(&sem_bloq_esc, 0,1);


  while(1){

    sleep(2);
    printf("\n1.Intentar leer");
    printf("\n2.Finalizar leer");
    printf("\n3.Intentar escribir");
    printf("\n4.Finalizar escribir");
    printf("\n0.Salir\n");
    scanf("%i",&opcion);

    switch(opcion){

      case 1:
      printf("Introduzca el numero del lector (del 1 al %i)\n",N1);
      scanf("%i",&lector);
      sem_post(&sem_lec[lector]);
      break;

      case 2:
      printf("Introduzca el numero del lector (del 1 al %i)\n",N1);
      scanf("%i",&lector);
      sem_post(&sem_lec_sal[lector]);
      break;

      case 3:
      printf("Introduzca el número del escritor (del 1 al %i)\n",N3);
      scanf("%i",&escritor);
      sem_post(&sem_esc[escritor]);
      break;

      case 4:
      printf("Introduzca el número del escritor (del 1 al %i)\n",N3);
      scanf("%i",&escritor);
      sem_post(&sem_esc_sal[escritor]);
      break;

      case 0:
      return 0;
    }
  }
  return 0;
}

void* thread_lector(int* parametro){

  while(1){

    printf("\n[Lector %i] -> Esperando a intentar leer...\n",(int)parametro);
    sem_wait(&sem_lec[(int)parametro]);

  	printf("\n[Lector %i] -> Intentando leer...\n",(int)parametro);
  	sem_wait(&sem_general);

    lectura++;

    if(lectura==1){

      if(escritura!=0){

        sem_wait(&sem_general);

      }else{

        sem_wait(&sem_escritura);
        sem_wait(&sem_bloq_esc);
        sem_post(&sem_general);

      }

    } else {

        sem_post(&sem_general);
  	    printf("\n[Lector %i] -> Leyendo...\n", (int)parametro);
  	    sem_wait(&sem_lec_sal[(int)parametro]);
  	    printf("\n[Lector %i] -> Fin lectura\n", (int)parametro);
        sem_post(&sem_lectura);
  	    sem_wait(&sem_general);
        lectura--;

        if(lectura==0){
            sem_post(&sem_bloq_esc);
            sem_post(&sem_escritura);
            sem_post(&sem_general);
        } else {
            sem_post(&sem_general);
        }
    }
 }
}



void* thread_escritor(int* parametro){

  while(1){

    printf("\n[Escritor %i] -> Esperando a intentar escribir...\n",(int)parametro);
    sem_wait(&sem_esc[(int)parametro]);

    printf("\n[Escritor %i] -> Intentando escribir...\n",(int)parametro);
    sem_wait(&sem_bloq_esc);

    escritura++;

    sem_post(&sem_bloq_esc);
    sem_wait(&sem_lectura);
    sem_wait(&sem_escritura);

    printf("\n[Escritor %i] -> Escribiendo...\n",(int)parametro);
    sem_wait(&sem_esc_sal[(int)parametro]);

    printf("\n[Escritor %i] -> Fin escritura\n",(int)parametro);
    sem_wait(&sem_bloq_esc);

    escritura--;
    sem_post(&sem_bloq_esc);

    if(escritura == 0){

        sem_post(&sem_lectura);
        sem_post(&sem_escritura);
        sem_post(&sem_general);

    }else{

        sem_post(&sem_escritura);

    }
  }
}
