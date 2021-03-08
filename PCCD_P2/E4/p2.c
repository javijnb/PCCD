#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* args[]){
    int i = 0;
    
    for(i=0;i<argc-1;i++){
        printf("%d) %s\n", i+1, args[i+1]);
    }

    int aleat = 0;
    aleat = rand() % 3;
    sleep(2+aleat);

    return 0;
}