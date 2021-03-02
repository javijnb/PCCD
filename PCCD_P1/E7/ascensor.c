#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>

int piso=0;
int PISO_MAX=5;
int PISO_MIN=0;
int cont_up=0;
int cont_down=0;
int T_PISO=3;
int aux=0;

void sensor_handler(int signal){
    aux=1;
}

void sig_handler(int signal){

        struct sigaction act;
        act.sa_handler=sensor_handler;
        act.sa_flags=SA_RESTART;


        printf("Se ha capturado la señal con ID - %d\n", signal);
        fflush(stdout);
        
        // SIGQUIT - EXIT
        if(signal==3){
                printf("Se ha recibido una señal SIGQUIT -- FINALIZAR\n");
                printf("\tSeñales USR1 - SUBIDAS: %d\n", cont_up);
                printf("\tSeñales USR2 - BAJADAS: %d\n", cont_down);
                printf("---CERRANDO PROCESO ASCENSOR---\n\n");
                exit(0);
        }

        // SIGUSR1 - SUBIR
        if(signal==10){
            printf("Se ha recibido una señal SIGUSR1 -- SUBIR\n");
            if(piso==PISO_MAX){
                printf("El ascensor se encuentra en el piso más alto (%d), imposible subir\nPor favor introduzca otra operación\n", PISO_MAX);
            }else{
                printf("Subiendo 1 PISO...\n");
                printf("%i\n", aux);

                // ESPERAMOS LA SEÑAL DEL SENSOR
                sigaction(SIGUSR2, &act, NULL);
                while(aux==0){
                    pause();
                }

                aux=0;
                piso++;
                cont_up++;
                printf("Piso actual: %d\n", piso);
            }
        }
        
        // SIGUSR2 - BAJAR
        if(signal==12){
            printf("Se ha recibido una señal SIGUSR2 -- BAJAR\n");
            if(piso==PISO_MIN){
                printf("El ascensor se encuentra en el piso más bajo (%d), imposible bajar\nPor favor introduzca otra operación\n", PISO_MIN);
            }else{
                printf("Bajando 1 PISO...\n");
                printf("%i\n", aux);

                 // ESPERAMOS LA SEÑAL DEL SENSOR
                sigaction(SIGUSR1, &act, NULL);
                while(aux==0){
                    pause();
                }

                aux=0;
                piso--;
                cont_down++;
                printf("Piso actual: %d\n", piso);
            }
        }
}




int main(void){
 
        printf("Bienvenido al proceso ASCENSOR\n");
        printf("Piso actual: %d\n\n", piso);

        pid_t pid = getpid();
        printf("PID ASCENSOR: %d\n", pid);
        
        struct sigaction sigact;
        sigact.sa_handler = sig_handler;
        sigact.sa_flags=SA_RESTART; //Fuerza a que si se reciben varias señales, se queden en espera y no interrumpan las que están en ejecución

        // clock_t begin = clock();
        // here, do your time-consuming job
        // clock_t end = clock();
        // double time_spent = (double)(end - begin);
        // printf("TIEMPO: %f", time_spent);


        sigaction(SIGUSR1, &sigact, NULL);
        sigaction(SIGUSR2, &sigact, NULL);
        sigaction(SIGQUIT, &sigact, NULL);

        

        printf("Proceso ascensor pausado\n");

        do{
            pause();
        }while(1);

        return 0;
} 
 
