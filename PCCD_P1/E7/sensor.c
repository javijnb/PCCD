#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int PID = 0;
int piso = 0;

int morir = 0;
int activar = 0;

void usr1_handler(int signal){
    morir = 1;
}

void chld_handler(int signal){
    activar = 1;
}

int main(int num, char *args[]){

    PID=atoi(args[1]);
    piso = atoi(args[2]);

    pid_t PID_ASCENSOR = (pid_t) PID;
    
    struct sigaction act_usr1, act_chld;
    act_usr1.sa_handler = usr1_handler;
    act_chld.sa_handler = chld_handler;
    act_chld.sa_flags = SA_RESTART;
    
    sigaction(SIGCHLD, &act_chld, NULL);
    sigaction(SIGUSR1, &act_usr1, NULL);

    printf("Inicio\n");
    printf("PISO: %d - PID: %d\n", piso, PID_ASCENSOR);

    while(morir == 0){

        //Si ha recibido la orden de activarse
        if(activar == 1){
            activar = 0;
            sleep(2);
            printf("Sensor del piso %d: ACTIVADO\n", piso);
            //Mandamos señal al ascensor (SIGALARM) que indique que ha llegado a su piso
            kill(PID_ASCENSOR, SIGALRM);

        //En espera a la señal de activarse
        }else{
            pause();
        }
    }

    printf("Recibida la señal de muerte por parte del ascensor\n");
    return 0;
    
}
