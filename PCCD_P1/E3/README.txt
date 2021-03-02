gcc -Wall p1.c -o p1
./p1 para ejecutar el proceso pausado que incluye los handlers de procesado de cualquier señal
Cualquier señal es detectada mediante un bucle sigaction de 0 a 64 y tras recibir SIGTERM, finaliza mostrando del vector de bits
            [numero_de_señal] "valor de señal recibida"
            Siendo 1 en el valor si en algún momento se recibió esa señal durante la ejecución
