#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct{
  int entero;
} zona;

int main(int argc, char* argv[]){
  key_t miclave;
  zona *mem_zona;
  int shmid = 0;

	miclave = ftok("/home/javi/Escritorio/PCCD/PCCD_P3", 2);
	if(miclave == -1){
		printf("Error generando la clave\n");
		return -1;
	}

	shmid = shmget(miclave, sizeof(int), IPC_CREAT | 0666);
	if(shmid < 0){
        printf("Error creando el segmento de memoria compartida\n");
		return -1;
	}

	printf("Zona de memoria: %d\n", shmid);
    if(shmctl(shmid, IPC_RMID, NULL) == -1){
  		printf("No se ha podido liberar el segmento de memoria.\n");
  	} else {
  	}

    printf("Zona de memoria liberada con éxito\n");
  	return 0;
  }
