#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int PID = 0;
int piso = 0;

int main(int num, char *args[]){

    PID=atoi(args[1]);
    piso = atoi(args[2]);

    pid_t PID_ASCENSOR = (pid_t) PID;
    printf("PISO: %d\nPID: %d\n", piso, PID_ASCENSOR);
    if(piso==1){
        kill(PID_ASCENSOR, SIGUSR1);
    }
    if(piso==2){
        kill(PID_ASCENSOR, SIGUSR2);
    }
    
    printf("Señal enviada\n");

    return 0;
}
