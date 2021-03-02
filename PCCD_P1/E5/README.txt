gcc -Wall ascensor.c -o ascensor
./ascensor

DESDE OTRA TERMINAL:
pidof ascensor
kill -USR1 "PID"  --> Mandar subir 1 piso
kill -USR2 "PID"  --> Mandar bajar 1 piso
kill -QUIT "PID"  --> Mandar finalizar la ejecución

DETALLES:
Piso más bajo: 0  -- imposible bajar estando en el piso 0
Piso más alto: 5  -- imposible subir estando en el piso 5
Se muestra por pantalla el piso actual cada vez que finaliza una orden exitosa
Al finalizar la ejecución se muestra por pantalla el número de ejecuciones exitosas (subidas y bajadas)
