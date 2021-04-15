#include <sys/ipc.h>//msgget
#include <sys/types.h>//msgget
#include <sys/msg.h>//msgget
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>//ftok

struct msgbuf{
  long mtype;
  int mtext;
} msg;

int main (int argc, char* argv[]){
    

    int id_cola = 0;
    id_cola = atoi(argv[1]);
    msg.mtype = 1;
    msg.mtext = 6;
    // Restamos el tamaño del mtype:
    int longitud = sizeof(msg) -  sizeof(long);
    int envio = msgsnd(id_cola, &msg, longitud, 0);

    if(envio == -1){

      printf("Error al enviar el mensaje\n");
      exit(-1);

    } else {

      printf("Mensaje enviado");

    }
  }
