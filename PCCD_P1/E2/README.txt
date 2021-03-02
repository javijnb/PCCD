gcc p2.c -o p2 (cliente-handler)
gcc p1.c -o p1 (proceso victima que duerme esperando la señal)

./p1 (comienza el proceso victima9
./p2 nºseñal PID
    PARA SABER EL PID, en terminal:         pidof p1
    PARA SABER EL Nº DE SEÑAL, en terminal: kill -l
    
./p2 15 PID (manda la señal SIGTERM y finaliza su ejecución)
