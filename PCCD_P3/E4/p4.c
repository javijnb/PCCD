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
    if(miclave== -1){
        printf("Error generando la clave\n");
        return -1;
    }

    shmid = shmget(miclave, sizeof(int), IPC_CREAT | 0666);
    if(shmid < 0){
        printf("Error creando el segmento de memoria compartida\n");
        return -1;
    }

    mem_zona = shmat(shmid, NULL, 0);
    if(mem_zona == (-1)){
        printf("Error al asignar el segmento\n");
        return -1;
    }else{
        while(1){
            printf("Caminando por la habitación.\n");
            getchar();
            printf("Intentando entrar en mi sección crítica.\n");
            printf("Dentro de mi sección crítica.\n");
            getchar();
            printf("He salido de mi sección crítica.\n");
    }
    }






}