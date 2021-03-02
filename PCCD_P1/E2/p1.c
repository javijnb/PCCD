#include <stdio.h>
#include <unistd.h>
#include <signal.h>

 int main(){
     printf("PRACTICA 1 - EJERCICIO 2\n");
     printf("PROCESO 1 INICIADO\n");
     int aux = 0;
     printf("El proceso será pausado / dormido");
     aux = pause();
     printf("El proceso ha sido despertado");
     return 0;
 }
