Man pthread_create:
    int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);

PARAMETROS:
    The attr argument points to a pthread_attr_t structure whose contents are used at thread creation time to determine attributes for the new thread; 
    this structure is initialized using pthread_attr_init(3) and related functions.  
    If attr is NULL, then the thread is created with default attributes.

    Before returning, a successful call to pthread_create() stores the ID of the new thread in the buffer pointed to by thread; 
    this identifier is used to refer to the thread in  subsequent  calls  to  other pthreads functions.

VALOR DE RETORNO:
    On success, pthread_create() returns 0. On error returns a code number.






CODIGO DE EJEMPLO DE CREACION DE N HILOS CON HELLO WORLD CADA VEZ QUE SON CREADOS:

#define NUM_THREADS 5

void *PrintHello(void *threadid)
 {
    long tid;
    tid = (long)threadid;
    printf("Hello World! It's me, thread #%ld!\n", tid);
    pthread_exit(NULL);
 }

 int main (int argc, char *argv[])
 {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    for(t=0; t<NUM_THREADS; t++){
       printf("In main: creating thread %ld\n", t);
       rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
       if (rc){
          printf("ERROR; return code from pthread_create() is %d\n", rc);
          exit(-1);
       }
    }

    /* Last thing that main() should do */
    pthread_exit(NULL);
 }


 SALIDA DEL PROGRAMA:

In main: creating thread 0
In main: creating thread 1
Hello World! It's me, thread #0!
In main: creating thread 2
Hello World! It's me, thread #1!
Hello World! It's me, thread #2!
In main: creating thread 3
In main: creating thread 4
Hello World! It's me, thread #3!
Hello World! It's me, thread #4!







 APUNTES DE CLASE:
 Threads = Procesos ? La diferencia es que con fork se copiaba codigo del padre pero espacios de memoria diferentes.
                      Los hilos cuelgan de un nodo padre y comparten la memoria del proceso que los creó
 Threads = Procesos ligeros ! Nos evitan hacer cambios de espacio de memoria entre estados de ejecución y minimizan el uso de memoria
 Desventaja de los hilos? Gestionar su concurrencia, el acceso a la memoria compartida

 EJERCICIO: solo un escritor puede estar escribiendo en memoria, no puede haber otro escritor ni tampoco otra persona leyendo mientras se escribe
            básicamente porque las operaciones no son atómicas, de este modo el lector no puede ser concurrente con el escritor. La práctica
            anterior simulaba operaciones atomicas (cambiar el valor de quiero_x o leer/escribir el turno eran operaciones "atomicas").
            Con los lectores puedo ser concurrente pero con los escritores, en exclusión mutua con cualquier otro proceso
            Si no establezco un limite de lectores cada x tiempo, se puede dar el caso que siempre haya lectores accediendo y no haya
            hueco para escritores que quieran entrar.