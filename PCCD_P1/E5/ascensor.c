#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int Array[63] = {0};
int piso=0;
int PISO_MAX=5;
int PISO_MIN=0;
int cont_up=0;
int cont_down=0;
int cont_term = 0;

void sig_handler(int signal){

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
                piso++;
                cont_up++;
                // HACER QUE ESTO LLEVE T_PISO segundos
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
                piso--;
                cont_down++;
                // HACER QUE ESTO LLEVE T_PISO segundos
                printf("Piso actual: %d\n", piso);
            }
        }
}


int main(void){
 
        printf("Bienvenido al proceso ASCENSOR\n");
        printf("Mande una señal USR1 para ASCENDER 1 PISO\nMande una señal USR2 para DESCENDER 1 PISO\n");
        printf("Mande una señal QUIT para finalizar el proceso\n");
        
        struct sigaction sigact;
        sigact.sa_handler = sig_handler;
        //sigact.sa_flags=SA_RESTART;

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
 
