No usar waitpid nunca
Waitpid permite al padre qeudarse suspendido hasta que muera el hijo con el PID esperado
Si se muere otro hijo, este hijo se quedará en estado zombie en el PCB

El wait no conlleva una suspensión del padre
Wait espera por cualquier muerte de un hijo (captura cualquier muerte de un hijo) y devuelve el PID del hijo muerto (mejor herramienta de sincronización)
    do{
        pid = wait()
    }while(pid!=pid_esperado);

Limitaciones básica del fork-wait: NO puedo sincronizarme con otros procesos que no sean hijos míos.
                                   NO puedo sincronizarme entre hijos, ni siquiera del mismo padre.
                                   NO puedo sincronizarme con el padre desde el hijo, solo topdown.
                                   Solo puedo establecer la sincronización cuando muere el proceso y que haya creado yo.

Cuando hacemos fork():
    Nueva entrada en el PCB con nuevo PID
    Código el del padre
    Espacio de memoria independiente al del padre
    Contador del programa: el la siguiente instrucción al fork
    Preparado para ejecución
    
El fork devuelve un 0 para el caso del hijo y en el caso del padre devuelve el PID del hijo que ha creado
Poner siempre al final del códgo del hijo un exit(0) para asegurarnos que vuelve al padre, siempre dentro de un bucle if-else

    -> padre                                                   

    if(fork()==0){
        Codigo hijo
        o un execl
    }else{
        Codigo padre concurrente con hijo
    }


    -> hijo

    if(fork()==0){
        Código hijo concurrente con padre
        EXIT(0);
    }else{
        Codigo padre
    }

IMAGEN DEL PROCESO: Archivo ejecutable que crea ese procesos (código y memoria, PID y PPID no son alterados).
EXECL: Reemplaza la imagen actual del proceso por la introducida por comandos. Es equivalente a cambiar el proceso por otro distinto, pero sigue conservando su PID y su padre (PPID)
       La siguiente instrucción del contador de programa con un execl será la del código del proceso introducido por comandos
       Es una facilidad para estructurar mejor el código

El grafo del ejercicio tiene relaciones redundantes de concurrencia, se puede resolver en cuatro procesos de forma teórica,
sin embargo, usndo fork-wait el númeró mínimo son 5 ya que en ramas bifurcadas no podemos reutilizar el propósito del proceso



CUESTIONES:
Por qué no aparecían zombies? Porque la concurrencia era demasiado rápida en su ejecución
fflush(stdout), limpia el buffer de salida, hacerse antes de hacer un hijo