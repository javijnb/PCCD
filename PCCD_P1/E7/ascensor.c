#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>

int piso_actual=0;
int PISO_MAX=2;
int PISO_MIN=0;
int cont_up=0;
int cont_down=0;
int T_PISO=3;

int aux=0;
int i=0;

int salir=0;
int subir=0;
int bajar=0;
int moviendose=0;

int pid_sensor[10] = {};


void usr1_handler(int signal){
    subir=1;
}

void usr2_handler(int signal){
    bajar=1;
}

void quit_handler(int signal){
    salir=1;
}

void sensor_handler(int signal){
    moviendose=0;
}



int main(void){
 
        printf("Bienvenido al proceso ASCENSOR\n");

        pid_t pid = getpid();
        printf("PID ASCENSOR: %d\n", pid);

        for (i=0; i<=PISO_MAX; i++){
		    printf("Introduzca el PID del sensor del piso %i: ", i);
		    scanf("%i", &pid_sensor[i]);
            printf("\n");
	    }


        struct sigaction act_usr1, act_usr2, act_quit, act_sensor;

	    act_usr1.sa_handler = usr1_handler;	
	    act_usr2.sa_handler = usr2_handler;
	    act_quit.sa_handler = quit_handler;	
	    act_sensor.sa_handler = sensor_handler;
        
        //Fuerza a que si se reciben varias señales, se queden en espera y no interrumpan las que están en ejecución
        act_usr1.sa_flags   =SA_RESTART; 
        act_usr2.sa_flags   =SA_RESTART; 
        act_sensor.sa_flags =SA_RESTART; 
        act_quit.sa_flags   =SA_RESTART; 

        sigaction(SIGUSR1, &act_usr1, NULL);
        sigaction(SIGUSR2, &act_usr2, NULL);
        sigaction(SIGQUIT, &act_quit, NULL);
        sigaction(SIGALRM, &act_sensor, NULL);

        printf("INICIO DEL PROGRAMA\n");
        printf("Piso actual: %d\n", piso_actual);
        while(salir==0){

            //Si está moviéndose y con variables de dirección activas
            if((moviendose==1 && subir==1) || (moviendose==1 && bajar==1)){
                subir=0;
                bajar=0;
                printf("Ascensor moviéndose...\n");
            }else{

                //Si sube
                if(subir==1){
                    subir=0;
                    if(piso_actual < PISO_MAX){
                        piso_actual++;
                        cont_up++;
                        moviendose=1;
                        //Mandamos señal (alarma) al sensor del piso que queremos llegar
                        kill(pid_sensor[piso_actual], SIGCHLD);
                        printf("EL ascensor está subiendo al piso %d\n", piso_actual);
                    }else{
                        printf("El ascensor se encuentra en el piso más alto (%d), imposible subir\nPor favor introduzca otra operación\n", PISO_MAX);
                    }
                }

                //Si baja
                if(bajar==1){
                    bajar=0;
                    if(piso_actual > PISO_MIN){
                        piso_actual--;
                        cont_down++;
                        moviendose=1;
                        //Mandamos señal (alarma) al sensor del piso que queremos llegar
                        kill(pid_sensor[piso_actual], SIGCHLD);
                        printf("El ascensor está bajando al piso %d\n", piso_actual);
                    }else{
                        printf("El ascensor se encuentra en el piso más bajo (%d), imposible bajar\nPor favor introduzca otra operación\n", PISO_MIN);
                    }
                }

                //Si no se encuentra realizando otra acción, en espera
                if(moviendose==0){
                    pause();
                }

            }

        }

        //Fin de ejecución
        printf("Se ha recibido una señal SIGQUIT -- FINALIZAR\n");
        printf("\tSeñales USR1 - SUBIDAS: %d\n", cont_up);
        printf("\tSeñales USR2 - BAJADAS: %d\n", cont_down);
        printf("---CERRANDO PROCESO ASCENSOR---\n\n");
        int k = 0;
        for (k=0; k<=PISO_MAX; k++){
			kill(pid_sensor[k], 10);
		}
        return 0;
} 
 
