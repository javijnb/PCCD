gcc -Wall p1.c -o p1 
./p1

WAIT(&estado)                   -> Suspende la ejecución del proceso padre hasta que uno de sus hijos finaliza
WAITPID(pid, &estado, opciones) -> Suspende la ejecución del proceso padre hasta que uno de sus hijos referenciados
                                   por el parámetro PID haya cambiado de estado

Ambos devuelven el PID del proceso hijo
wait(&estado) <==> waitpid(-1, &estado, 0)