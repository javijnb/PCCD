#include <sys/ipc.h>//msgget
#include <sys/types.h>//msgget
#include <sys/msg.h>//msgget
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>//ftok

int main (int argc, char* argv[]){

  key_t key =  ftok("/home/javi/Escritorio/PCCD_B/PCCD_P6/E1",6);

  if(key == -1){

    printf("Error al generar la key\n");
    exit(-1);

  } else {

    int id_cola = msgget(key, IPC_CREAT | 0777);

    if(id_cola == -1){

      printf("Error al obtener el identificador de cola \n");
      exit(-1);

    } else {

      printf("ID cola de mensajes: %i\n",id_cola);

    }
  }



}
