#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int salida = 1;

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
            printf("Dentro del pasillo\n");
            getchar();
            
            //Una vez dentro tenemos que conmutar la puerta del pasillo del otro
            if(turno==1) mem_zona -> quiere_q = 0;
            else mem_zona -> quiere_q = 0;

            printf("He accionado el pulsador a la entrada de la sección crítica\n");//Ahora el otro no puede entrar en la SC
            getchar();

            while(salida){
            printf("Intentando acceder a la Sección Crítica...\n");
            
            //Comprobamos si ahora tenemos acceso a la SC:
            //Podemos acceder cuando:
                // Es nuestro turno y tenemos la variable de acceso a la SC (quiere_x) a nuestro favor
                // Entramos si (turno=1 y queremos_p=1 y el otro es 0) ó si somos el otro (turno=0 queremos_q=1 y el otro a 0)
            if((turno == 1 && mem_zona -> quiere_p == 1  && mem_zona -> quiere_q == 0) || (turno == 0 && mem_zona -> quiere_q == 1  && mem_zona -> quiere_p == 0) ){
                
                //Una vez dentro nos aseguramos de que se refleja en la variable de control hasta que nos la active el otro proceso (no podremos entrar dos veces seguidas)
                if(turno==1) mem_zona->quiere_q=0;
                else mem_zona->quiere_p=0;
                printf("Dentro de mi sección crítica\n");
				getchar();
        		printf("He salido de mi sección crítica\n");
        		getchar();

                //Ahora que salimos reactivamos la variable de control:
                if(turno==1) mem_zona->quiere_q=1;
                else mem_zona->quiere_p=1;
                salida=0;
                printf("He accionado el pulsador al salir\n"); //ahora el otro puede entrar a la SC
                getchar();
                continue;

            }else{
                printf("Puerta de la sección crítica cerrada\n");
                continue;
            }
        }//while salida
        }
    }


    fin = shmdt(mem_zona);
    if(fin == -1){
        printf("Error al desenlazar el segmento\n");
        return -1;
    }

    return 0;


}