#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int pid_Carvajal, pid_Ramos, pid_Pique, pid_JordiAlba, pid_Busquets, pid_Thiago = 0;
int CarvajalOK, RamosOK, PiqueOK, JordiAlbaOK, BusquetsOK, ThiagoOK = 0;

int pid_defensa = 0;
int pid_mediocentro = 0;
int i = 0;
int aux, aux2 = 0;
int control = 1;

int main(int argc, char* argv[]){

    printf("Alineación de la Selección Española de Fútbol 2021:\n");
    printf("ALINEACIÓN ESPERADA:\n");
    printf("De Gea Ramos Carvajal Piqué Jordi-Alba Busquets Isco Thiago Aspas Silva Morata\n");
    printf("De Gea ");
    //fflush(stdout);

    switch(pid_Ramos=fork()){
        case 0:
            printf("Ramos ");
            exit(0);
        
        case -1:
            printf("Error en Ramos\n");
            exit(-1);
    }

    switch(pid_Carvajal=fork()){
        case 0:
            printf("Carvajal ");
            exit(0);

        case -1:
            printf("Error en Carvajal\n");
            exit(-1);
    }

    switch(pid_Pique=fork()){
        case 0:
            printf("Piqué ");
            exit(0);
        
        case -1:
            printf("Error en Pique\n");
            exit(-1);
    }

    /*
    switch(pid_JordiAlba=fork()){
        case 0:
            printf("Jordi-Alba ");
            exit(0);

        case -1:
            printf("Error en Jordi Alba\n");
            exit(-1);
    }
    */

    printf("Jordi-Alba ");

    //Mientras no mueran Carvajal Ramos y Pique no puedo imprimir BUSQUETS

    while(aux!=3){
        pid_defensa = wait(0);
        if(pid_defensa==pid_Carvajal){
             CarvajalOK=1;
             aux++;
        }
        if(pid_defensa==pid_Ramos){
            RamosOK=1;
            aux++;
        }
        if(pid_defensa==pid_Pique){
            PiqueOK=1;
            aux++;
        }
        /*
        if(pid_defensa==pid_JordiAlba){
            JordiAlbaOK=1;
            aux++;
        }
        */

    }

    //fflush(stdout);
    if(CarvajalOK==1 && RamosOK==1 && PiqueOK==1) printf("Busquets ");
    //fflush(stdout);

    switch(pid_Thiago=fork()){
	    case 0:  
            printf("Thiago ");
            printf("Silva ");
			exit(0);

        case -1: 
            printf("Error en Thiago y Silva\n");
	        exit(-1);
	}

    while(aux2<1){
        pid_mediocentro = wait(0);
        if(pid_mediocentro==pid_Thiago){
             ThiagoOK=1;
             aux2++;
        }
    }

    printf("Isco ");
    printf("Aspas ");


    if(ThiagoOK != 1) wait(0);
    printf("Morata\n");

    printf("\n");
    return 0;
}