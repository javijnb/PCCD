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
void* thread_ThiagoSilva (void* );


int main(int argc,char* argv[]){

	pthread_t Carvajal,Ramos,Pique,ThiagoSilva;

	printf("De Gea ");

    pthread_create(&Carvajal, NULL, thread_Carvajal, NULL);
	pthread_create(&Ramos, NULL, thread_Ramos, NULL);
	pthread_create(&Pique, NULL, thread_Pique, NULL);

	printf("Jordi-Alba ");

    pthread_create(&ThiagoSilva, NULL, thread_ThiagoSilva, NULL);
    
    //Esperamos por los defensas para sacar la rama de grafo: Busquets Isco Aspas
	pthread_join(Carvajal, NULL);
	pthread_join(Ramos, NULL);
	pthread_join(Pique, NULL);
	printf("Busquets ");
    printf("Isco ");
	printf("Aspas ");

    //Cuando muera la otra rama del grafo sacamos el delantero central: Morata
	pthread_join(ThiagoSilva, NULL);
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
