gcc -Wall ascensor.c -o ascensor
gcc -Wall pulsador.c -o pulsador
./ascensor en una terminal
./pulsador en otra terminal

Invocamos primero ASCENSOR y obtenemos su PID viendolo en pantalla
Invocamos ahora PULSADOR e introducimos el PID del ascensor por terminal para que sepa a qué proceso enviar las señales
Ahora comenzamos a introducir las opciones en PULSADOR:
    1) SUBIR
    2) BAJAR
    3) SALIR, y muestra por pantalla el número de operaciones introducidas
