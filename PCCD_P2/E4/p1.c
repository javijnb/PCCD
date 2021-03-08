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
int pidhijos[3] = {};

int estado  = 0;


int main(int argc, char* args[]){

    pid_t pidpadre = getpid();
    printf("Comienzo del proceso PADRE  - PID %d \n", pidpadre);
    printf("Argumentos recibidos:\n");

    for(int i=0;i<argc-1;i++){
        printf("%d) %s\n", i+1, args[i+1]);
    }


    // Primero generamos los 3 hijos
    for(loop=0; loop<hijos; loop++){

        // Creamos un nuevo proceso hijo y tras dormir un gap de tiempo, lo matamos con exit
        switch(pidhijos[loop]=fork()){

            case 0: printf("Comienzo del proceso HIJO %d - PID %d\n", loop+1, getpid());
                    execl("p2", args[loop+1], (char *) NULL);
                    /*
                    sleep(2+loop); 
                    exit(10+loop+1);
                    return 0;
                    */
                
            case -1: printf("Error creando el hijo %d\n", loop+1);
                    return 0;

        }
    }

    // Para cada hijo esperamos su muerte e imprimimos su PID y STATUS
    for(loop=0; loop<hijos; loop++){

        // pidhijo = wait(&estado);
        pidhijo = waitpid(pidhijos[loop], &estado, 0);

        if(WIFEXITED(estado)){
            printf("El proceso HIJO %d con PID %d ha finalizado con código %d\n", loop+1, pidhijo, WEXITSTATUS(estado));
        }

    }

    return 0;
}

