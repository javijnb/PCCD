#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

// Recibe como parámetros numero de señal a enviar y PID del proceso victima

int piso_actual = 0;
int PISO_MAX=2;
int PISO_MIN=0;

int main(int argc, char *argv[]){
     printf("Bienvenido al proceso PULSADOR\n");
     printf("PISO ACTUAL: %d\n", piso_actual);
     int opcion;
     int PID_INT;
     int signal_USR1=10;
     int signal_USR2=12;
     int signal_QUIT=3;
     
     printf("Introduzca el PID del ASCENSOR: ");
     scanf("%d", &PID_INT);

     pid_t PID_ASCENSOR = (pid_t) PID_INT;

     while(1){
        printf("Por favor seleccione una opción: \n");
        printf("\t1) SUBIR\n");
        printf("\t2) BAJAR\n");
        printf("\t3) SALIR\n");
        scanf("%d", &opcion);
        
        switch(opcion){

            case 1:
                if(piso_actual==PISO_MAX){
                    printf("El ascensor se encuentra en el piso más alto (%d), imposible subir\nPor favor introduzca otra operación\n", PISO_MAX);
                    break;
                }else{
                    printf("Ha seleccionado 1: SUBIR\n");
                    kill(PID_ASCENSOR, signal_USR1);
                    piso_actual++;
                    printf("\n");
                    break;
                }

            case 2:
                 if(piso_actual==PISO_MIN){
                    printf("El ascensor se encuentra en el piso más bajo (%d), imposible subir\nPor favor introduzca otra operación\n", PISO_MIN);
                    break;
                 }else{
                    printf("Ha seleccionado 2: BAJAR\n");
                    kill(PID_ASCENSOR, signal_USR2);
                    piso_actual--;
                    printf("\n");
                    break;
                 }
                

            case 3:
                printf("Ha seleccionado 3: SALIR\n");
                kill(PID_ASCENSOR, signal_QUIT);
                printf("\n");
                printf("Cerrando proceso PULSADOR...\n");
                exit(0);
                break;
                
            default:
                printf("No ha introducido una opción válida, por favor introduzca 1, 2 ó 3\n");
                break;

        }
     }

 }



