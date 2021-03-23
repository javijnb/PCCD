#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
 
// DE GEA
// Carvajal Ramos Piqué JordiAlba
// Busquets
// Isco Thiago
// Aspas Silva
// Morata

void* thread_Carvajal (void* );
void* thread_Ramos (void* );
void* thread_Pique (void* );
void* thread_JordiAlba (void* );
void* thread_ThiagoSilva (void* );
void* thread_IscoAspas (void* );


int main(int argc,char* argv[]){

	pthread_t Carvajal,Ramos,Pique,ThiagoSilva, JordiAlba, IscoAspas;

	printf("De Gea ");

    pthread_create(&Carvajal, NULL, thread_Carvajal, NULL);
	pthread_create(&Ramos, NULL, thread_Ramos, NULL);
	pthread_create(&Pique, NULL, thread_Pique, NULL);
    pthread_create(&JordiAlba, NULL, thread_JordiAlba, NULL);
    
    //Esperamos por los defensas para sacar al central Busquets
	pthread_join(Carvajal, NULL);
	pthread_join(Ramos, NULL);
	pthread_join(Pique, NULL);
    pthread_join(JordiAlba, NULL);

	printf("Busquets ");

    //Ejecutamos en paralelo las dos ramas de centrocampistas
	pthread_create(&IscoAspas, NULL, thread_IscoAspas, NULL);
    pthread_create(&ThiagoSilva, NULL, thread_ThiagoSilva, NULL);

    pthread_join(IscoAspas, NULL);
    pthread_join(ThiagoSilva, NULL);

    //Cuando finalicen los centrocampistas, sacamos al delantero
	printf("Morata\n");
	pthread_exit(NULL);
	return 0;
}

void* thread_Carvajal (void* parametro){
  printf("Carvajal ");
  pthread_exit(NULL);
}

void* thread_Ramos (void* parametro){
	printf("Ramos ");
	pthread_exit(NULL);
}

void* thread_Pique (void* parametro){
  printf("Piqué ");
  pthread_exit(NULL);
}

void* thread_ThiagoSilva (void* parametro){
  printf("Thago ");
  printf("Silva ");
  pthread_exit(NULL);
}

void* thread_JordiAlba (void* parametro){
    printf("Jordi-Alba ");
    pthread_exit(NULL);
}

void* thread_IscoAspas (void* parametro){
    printf("Isco Aspas ");
    pthread_exit(NULL);
}
