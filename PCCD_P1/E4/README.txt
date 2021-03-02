gcc -Wall p1.c -o p1
gcc -Wall p2.c -o p2
./p1
./p2

DESDE OTRA TERMINAL:
pidof p1 (o pidof p2)
kill -USR1 <pid> - así mandamos las señales

P1 --> Contiene la modificación que usa SA_RESTART (hace que varias señales no formen una interrupcion en el proceso y lo mate)
P2 --> Contiene la modificacion que usa SA_RESETHAND (una vez enviada una señal con nuestro handler hace que las siguientes señales sean atendidas con el handler por defecto y no con el nuestro)

SA_RESTART:
This flag affects the behaviour of interruptible functions; that is, those specified to fail with errno set to [EINTR]. If set, and a function specified as interruptible is interrupted by this signal, the function will restart and will not fail with [EINTR] unless otherwise specified. If the flag is not set, interruptible functions interrupted by this signal will fail with errno set to [EINTR]. - De esta manera evitamos que varias señales interrumpan el proceso siendo manejadas por otro handler y generando una interrupcion, ignoramos el posible error si sucede otra INT durante la ejecución


SA_RESETHAND:
If set, the disposition of the signal will be reset to SIG_DFL and the SA_SIGINFO flag will be cleared on entry to the signal handler.
In addition, if this flag is set, sigaction() behaves as if the SA_NODEFER flag were also set.
Da la posibilidad de atender dicha señal una sola vez con un handler concreto o para siempre (la siguiente)

