#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

int hijos = 3;
int contaje = 0;
int loop;

// Cada vez que se reciba una señal de la muerte de un hijo, +1 a la cuenta
void child_handler(int signal){
    contaje++;
}


int main(void){

    pid_t pid = getpid();
    printf("Comienzo del proceso PADRE (%d) \n", pid);

    struct sigaction act_child;
    act_child.sa_handler = child_handler;
    act_child.sa_flags = SA_RESTART;
    act_child.sa_flags = SA_NODEFER; 
    // Permite capturar la misma señal que está siendo manejada en caso de ser recibida

    sigaction(SIGCHLD, &act_child, NULL);

    for(loop=0; loop<hijos; loop++){

        // Creamos un nuevo proceso hijo (3 veces)
        switch(fork()){

            case 0: printf("Se ha generado un hijo (%d)\n", loop+1);

                    // Creamos un gap entre muertes añadiendo el orden del hijo
                    sleep(2+loop); 
                    printf("%d\n", getpid());

                    // Mandamos la señal de muerte del hijo
                    kill(getpid(), SIGCHLD); 
                    printf("El hijo %d ha finalizado su ejecución\n", loop+1);
                    return 0;
                
            case -1: printf("Error creando el hijo %d\n", loop+1);
                    return 0;

        }
    }

    printf("Contaje: %d\n", contaje);

    while(contaje<3){
        pause();
    }

    printf("Contaje: %d\n", contaje);

    return 0;
}
