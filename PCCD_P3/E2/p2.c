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
    int shmid, fin = 0;

    // ftok - convert a pathname and a project identifier to a System V IPC key
    // On failure -1 is returned
    //printf("1\n");
    miclave = ftok("/home/javi/Escritorio/PCCD/PCCD_P3", 2);
    if(miclave == -1){
        printf("Error generando la clave\n");
        return -1;
    }

    // Creamos el segmento:
    //printf("2\n");
    shmid = shmget(miclave, sizeof(int), IPC_CREAT | 0666);
    if(shmid<0){
        printf("Error creando el segmento de memoria compartida\n");
        return -1;
    }

    // Asignamos el segmento a nuestro espacio de datos:
    // void *shmat(int shmid, const void *shmaddr, int shmflg);
    // If shmaddr is NULL, the system chooses a suitable (unused) page-aligned address
    //printf("3\n");
    mem_zona = shmat(shmid, NULL, 0);
    if(mem_zona == (-1)){
        printf("Error al asignar el segmento\n");
    }else{
        printf("El numero de la zona de memoria es: %d\n", *mem_zona);
    }

    //printf("4\n");
    fin = shmdt(mem_zona);
    if(fin == -1){
        printf("Error al desenlazar el segmento\n");
        return -1;
    }

    return 0;
}