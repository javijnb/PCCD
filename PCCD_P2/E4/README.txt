gcc -Wall p1.c -o p1
gcc -Wall p2.c -o p2
./p1 1 2 3 (p.e)

OUTPUT:
Comienzo del proceso PADRE  - PID 90782 
Argumentos recibidos:
1) 1
2) 2
3) 3
Comienzo del proceso HIJO 1 - PID 90783
Comienzo del proceso HIJO 2 - PID 90784
Comienzo del proceso HIJO 3 - PID 90785
El proceso HIJO 1 con PID 90783 ha finalizado con código 0
El proceso HIJO 2 con PID 90784 ha finalizado con código 0
El proceso HIJO 3 con PID 90785 ha finalizado con código 0

Invocación del execl:
> execl("p2", args[loop+1], (char *) NULL);
Ejecuta el proceso p2 pasandole un único parámetro, el de orden loop+1 introducido por comandos al principio
Si no se introduce NULL al final de la función obtenemos un error: "Missing sentinel in function call"
