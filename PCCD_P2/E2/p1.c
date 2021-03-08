#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

// WAIT
#include <sys/types.h>
#include <sys/wait.h>

// EXIT
#include <stdlib.h>

int hijos   = 3;
int contaje = 0;
int loop    = 0;
int pidhijo = 0;

int estado  = 0;


int main(void){

    pid_t pidpadre = getpid();
    printf("Comienzo del proceso PADRE  - PID %d \n", pidpadre);


    // Primero generamos los 3 hijos
    for(loop=0; loop<hijos; loop++){

        // Creamos un nuevo proceso hijo y tras dormir un gap de tiempo, lo matamos con exit
        switch(fork()){

            case 0: printf("Comienzo del proceso HIJO %d - PID %d\n", loop+1, getpid());

                    sleep(2+loop); 
                    exit(10+loop+1);
                    //return 0;
                
            case -1: printf("Error creando el hijo %d\n", loop+1);
                    return 0;

        }
    }

    // Para cada hijo esperamos su muerte e imprimimos su PID y STATUS
    for(loop=0; loop<hijos; loop++){

        pidhijo = wait(&estado);

        if(WIFEXITED(estado)){
            printf("El proceso HIJO %d con PID %d ha finalizado con código %d\n", loop+1, pidhijo, WEXITSTATUS(estado));
        }

    }

    return 0;
}

