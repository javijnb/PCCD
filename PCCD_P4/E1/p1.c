#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Leer README para notas ajenas a comentarios de código
char input;
int contador = 0;
int control = 0;

//Definimos aquí la función thread
void* thread(void*);

int main(int argc, char* argv[]){
    int error;
    pthread_t hilo;

    //Creamoso el hilo:
    error = pthread_create(&hilo, NULL, thread, NULL);
    if(error != 0){
        perror("Error en pthread_create. No se ha creado el hilo.\n");
        exit(-1);
    }else{
        while(control==0){
            sleep(1);
            printf("Se han leído %d caracteres en el teclado\n", contador-1);
        }
    }

    //Matamos el hilo:
    pthread_exit(NULL);
    return 0;
}


void* thread(void* parametro){
  printf("Bienvenido al contador de caracteres. Pulse 'q' para salir.\n");
  while(input!= 'q'){
    input=getchar();
    getchar();//Bug
    contador++;
  }
  control = 1;
  pthread_exit(NULL);
  return 0;
}