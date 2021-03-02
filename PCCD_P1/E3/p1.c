#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int Array[63] = {0};

void sig_handler(int signal){

        printf("Se ha capturado la señal con ID - %d\n", signal);
        Array[signal]=1;
        int loop=0;
        fflush(stdout);
        

        if(signal==15){
                printf("Se ha recibido una señal SIGTERM\n");

                for(loop = 0; loop<63; loop++){
                        printf("[%d]%d ", loop, Array[loop]);
                }

                exit(0);
        }
}


int main(void){
 
       printf("LISTA DE SEÑALES: \n");
       printf("SIGHUP           1\n");
       printf("SIGINT           2\n");
       printf("SIGQUIT          3\n");
       printf("SIGILL           4\n");
       printf("SIGTRAP          5\n");
       printf("SIGABRT          6\n");
       printf("SIGIOT           6\n");
       printf("SIGBUS           7\n");
       printf("SIGFPE           8\n");
       printf("SIGKILL          9\n");
       printf("SIGUSR1         10\n");
       printf("SIGSEGV         11\n");
       printf("SIGUSR2         12\n");
       printf("SIGPIPE         13\n");
       printf("SIGALRM         14\n");
       printf("SIGTERM         15\n");
       printf("SIGSTKFLT       16\n");
       printf("SIGCHLD         17\n");
       printf("SIGCONT         18\n");
       printf("SIGSTOP         19\n");
       printf("SIGTSTP         20\n");
       printf("SIGTTIN         21\n");
       printf("SIGTTOU         22\n");
       printf("SIGURG          23\n");
       printf("SIGXCPU         24\n");
       printf("SIGXFSZ         25\n");
       printf("SIGVTALRM       26\n");
       printf("SIGPROF         27\n");
       printf("SIGWINCH        28\n");
       printf("SIGIO           29\n");
       printf("SIGPWR          30\n");
       printf("SIGSYS          31\n");
       printf("SIGUNUSED       31\n");

        
        struct sigaction sigact;
        sigact.sa_handler = sig_handler;
        sigact.sa_flags=SA_RESTART;
        int loop = 0;
        for(loop = 0; loop<63; loop++){
                sigaction(loop, &sigact, NULL);
        }
        

        printf("Proceso main pausado\n");

        do{
                pause();
        }while(1);

        return 0;
} 
