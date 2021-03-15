#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct{
  int quiere_p;
  int quiere_q;
} zona;

int main(int argc, char* argv[]){
  key_t miclave;
  zona *mem_zona;

    int turno = atoi(argv[1]);
    printf("Turno introducido: %d\n", turno);

    //Preparamos la memoria compartida
	miclave = ftok("/home/javi/Escritorio/PCCD/PCCD_P3", 2);
	if(miclave == -1){
		printf("Clave no generada.\n");
		return -1;
	}
	int zone = shmget(miclave, sizeof(int), IPC_CREAT|0666);
	if(zone == -1){
		printf("No se ha creado el segmento de mem_zone.\n");
		return -1;
	}
	printf("Zona de mem_zone: %d\n", zone);
	mem_zona = shmat(zone, NULL, 0);
	if(mem_zona == (-1)){
		printf("Segmento no enlazado.\n");
		return -1;
	} else {

        
        //Inicilizamos las variables de control en función del turno
        if(turno==1) mem_zona -> quiere_p = 1;
        else mem_zona -> quiere_q = 1;
        
		while(1){
			printf("Caminando por mi habitación.\n");
			getchar();
            printf("Dentro del pasillo\n");
            getchar();
            if(turno==1) mem_zona -> quiere_q = 0;
            else mem_zona -> quiere_p = 0;
            printf("He accionado el pulsador\n");
            getchar();
			printf("Intentando acceder a la Sección Crítica...\n");
			if((mem_zona -> quiere_p == 0 && mem_zona -> quiere_q == 1) || (mem_zona -> quiere_p == 1 && mem_zona -> quiere_q == 0) ){
				printf("Dentro de mi sección crítica\n");
				getchar();
                printf("He salido de mi sección crítica\n");
                getchar();
                if(turno == 1) mem_zona -> quiere_p = 1;
                mem_zona -> quiere_q = 1;
                printf("He accionado el pulsador\n");
                getchar();
      	        continue;
            }else{
				printf("Puerta cerrada. Saliendo del Pasillo...\n");
                getchar();
                if(turno == 1) {
                  mem_zona -> quiere_q = 1;
                  //mem_zone -> quiere_p =1;

                }else {
                  mem_zona -> quiere_p =1;
                  //mem_zone -> quiere_q =1;

                }
                printf("He accionado el pulsador\n");
                printf("He salido del pasillo\n");
		        continue;
			}
		}
  }
	if(shmdt(mem_zona) == -1){
		printf("Segmento no desenlazado.\n");
	}
	return 0;
}
