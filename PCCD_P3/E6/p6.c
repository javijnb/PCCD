#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct{
  int quiere_q;
  int quiere_p;
} zona;

int main(int argc, char* argv[]){
    key_t miclave;
    zona *mem_zona;
    int shmid, fin = 0;

    // El turno del proceso vendrá indicado por parámetro
    int turno = atoi(argv[1]);
    printf("Turno introducido: %d\n", turno);

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

        // SI estamos en el turno prioritario, conmutamos (o no) los pulsadores al final de la SC
        if(turno==1) mem_zona->quiere_p=1;
        else         mem_zona->quiere_q=1;

        while(1){
            printf("Caminando por la habitación.\n");
            getchar();
            printf("Intentando acceder al pasillo de entrada a la Sección Crítica…\n");
            
            //Si es su turno y tienen la posibilidad de entrar en la SC, se le da
            if((turno==1 && mem_zona->quiere_p==1) || (turno==0 && mem_zona->quiere_q==1)){
                printf("Dentro del pasillo\n");
                getchar();

                //Una vez dentro tenemos que conmutar la puerta del pasillo del otro
                if(turno==1) mem_zona -> quiere_q = 0;
                else mem_zona -> quiere_q = 0;

                printf("He accionado el pulsador a la entrada de la sección crítica\n");
                printf("Dentro de mi sección crítica\n");
                getchar();
                printf("He salido de mi sección crítica\n");
                getchar();

                //Reactivamos la conmutación de las puertas del otro proceso deshaciendo el último paso de activación:
                if(turno==1) mem_zona-> quiere_q=1;
                else mem_zona-> quiere_p=1;

                printf("He accionado el pulsador a la salida de la sección crítica\n");
                continue;

            }else{
                printf("Puerta del pasillo cerrada\n");
                continue;
            }
        }
    }


    fin = shmdt(mem_zona);
    if(fin == -1){
        printf("Error al desenlazar el segmento\n");
        return -1;
    }

    return 0;


}