#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct{
  int numero;
  char* cadena;
} parametros;

//Definimos aquí la función thread
void* thread(parametros * argumentos);

int main(int argc, char* argv[]){
    int error;
    int i = 0;
    pthread_t hilo[argc];
    parametros structHilos[argc-1];

    for(i=1;i<=(argc-1);i++){
        structHilos[i].numero=i;
        structHilos[i].cadena=argv[i];
        error=pthread_create(&(hilo[i]),NULL,(void*)thread,(void*)&structHilos[i]);
          if(error!=0){
            perror("Error en pthread_create. No se ha creado el hilo.\n");
            exit(-1);
          }else continue;
    }

    //Matamos el hilo:
    pthread_exit(NULL);
    return 0;

}


void* thread(parametros * argumentos){
  printf("Posición: %i, Texto: %s.\n",argumentos->numero,argumentos->cadena);
  pthread_exit(NULL);
  return 0;
}

