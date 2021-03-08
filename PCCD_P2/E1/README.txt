 gcc -Wall p1.c -o p1
 Por pantalla se visualizará la creación de cada proceso hijo y su muerte precedida del PID

 Se emplea SA_NODEFER para stackear en el handler mismas varias señales y atenderlas en caso
 de estar ocupado atendiendo otra
 
 kill(PID actual(padre), señal de muerte del hijo);