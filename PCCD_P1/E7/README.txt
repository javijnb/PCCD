gcc -Wall ascensor.c -o ascensor
gcc -Wall pulsador.c -o pulsador
gcc -Wall sensor.c -o sensor

./ascensor                            (en una terminal)
./pulsador                            (en otra terminal)
./sensor PID_ASCENSOR piso_del_sensor (en tantas temrminales como pisos)


PRE-PRÁCTICA:
Invocamos primero ASCENSOR y obtenemos su PID viendolo en pantalla
Invocamos ahora PULSADOR e introducimos el PID del ascensor por terminal para que sepa a qué proceso enviar las señales
Ahora comenzamos a introducir las opciones en PULSADOR:
    1) SUBIR
    2) BAJAR
    3) SALIR, y muestra por pantalla el número de operaciones introducidas
    
    
    
COMENTARIOS POSTPRÁCTICA:
Guardar el piso en el pulsador, de esa manera me evito mandar subir al ascensor en el caso de que no se pueda y gastar
tiempo y CPU despertando el proceso ASCENSOR de manera inutil. Desde pulsador contemplamos si se puede seguir subiendo y bajando. 
ASCENSOR solo sube y baja, no sabe donde está.



ORDEN DE INVOCACION DEL EJERCICIO:
1) Ejecutamos el proceso ASCENSOR, obtenemos por pantalla su PID
2) Abrimos una terminal por cada sensor y tras obtener su PID, vamos introduciendo por orden los PID de los sensores en el proceso ASCENSOR, para que sepa a quién mandar la señal de que va a ir                       hacia ese piso cuando proceda
3) Ejecutamos el proceso PULSADOR, pide luego por terminal el PID del ASCENSOR y ya podemos mandar las señales de subir y bajar



COMENTARIOS SOBRE LA IMPLEMENTACION FINAL:
Se ha dejado el estado del piso sobre el que se está en ambos procesos, ASCENSOR y PULSADOR, aunque la comunicación / sincronización entre procesos se realiza entre ASCENSOR y SENSOR:
Si en el código ponemos de acuerdo el número de pisos máximos del edificio en los procesos ASCENSOR y PULSADOR, PULSADOR informará de forma independiente (local) de si se encuentra en algún limite (PISO_MAX o PISO_MIN) y no despertará al proceso ASCENSOR
La opcion de SALIR en el proceso PULSADOR matará todos los procesos involucrados en el ejercicio
