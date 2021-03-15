Mismo contexto de turnos e invocación que el apartado anterior.
Comentarios:
    1) Una perfecta ejecución en paralelo de lso procesos (ambos ejecutandose paso a paso en el mismo estado), da lugar a la ejecución de ambos procesos
    en ciertos momentos estando ambos en la SC.
    2) Si un proceso se encuentra en la SC y no sale, el proceso en espera quedará en inanición hasta que este habilite su turno al salir (conmute)
    3) No hay escenario posible en el que ambos procesos se pisen y no puedan avanzar (interbloqueo)