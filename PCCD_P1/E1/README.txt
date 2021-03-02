 gcc ej1.c -o ej1
 *** DESDE OTRA TERMINAL***
 kill -SIGKILL `pidof ej1`  (mata el proceso)
 kill -SIGCHLD `pidof ej1`  (no sucede nada - es una señal que indica que un proceso hijo ha muerto)
 kill -SIGINT  `pidof ej1`  (cierra el proceso usando una interrupcion, similar a CTRL-C)
 
