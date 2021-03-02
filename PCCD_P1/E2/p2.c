#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

// Recibe como parámetros numero de señal a enviar y PID del proceso victima

int main(int argc, char *argv[]){
     printf("PRACTICA 1 - EJERCICIO 2\n");
     printf("PROCESO 2 INICIADO\n");
     printf("Llamaremos a la función kill() para matar al proceso P1\n");
     printf("\tNumero de señal a enviar: %s\n", argv[1]);
     printf("\tNumero de proceso a matar: %s\n", argv[2]);

     pid_t PID_P1 = (pid_t) atoi(argv[2]);
     int signal = atoi(argv[1]);

     kill(PID_P1, signal);
     printf("Se ha enviado la señal %s al proceso con PID %s\n", argv[1], argv[2]);
     return 0;
 }




