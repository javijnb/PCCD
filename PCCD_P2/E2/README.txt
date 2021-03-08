gcc -Wall p1.c -o p1
./p1

 El status de finalización de cada proceso hijo será su número de hijo + 10
 En este caso los status recibidos serán {11,12,13}

 WIFEXITED(status): devuelve un numero positivo si el hijo terminó correctamente
 WEXITSTATUS(status): devuelve los 8 bits menos significativos del codigo de retorno del hijo que terminó

OUTPUT:
Comienzo del proceso PADRE  - PID 85955 
Comienzo del proceso HIJO 1 - PID 85956
Comienzo del proceso HIJO 2 - PID 85957
Comienzo del proceso HIJO 3 - PID 85958
El proceso HIJO 1 con PID 85956 ha finalizado con código 11
El proceso HIJO 2 con PID 85957 ha finalizado con código 12
El proceso HIJO 3 con PID 85958 ha finalizado con código 13