p1: proceso que recibe por parámetro el numero inicial a partir de cual empezamos a contar
p2: proceso que unicamente lee el valor de la zona de memoria compartida con p2
p3: ha de llamarse cuando queremos liberar la zona de memoria compartida por los procesos p1 y p2

int shmctl(int shmid, int cmd, struct shmid_ds *buf);

shmctl() performs the control operation specified by cmd on the System V shared memory segment whose identifier is given in shmid.
    The buf argument is a pointer to a shmid_ds structure
    The ipc_perm structure is defined as follows (the highlighted fields are settable using IPC_SET):
    Suitable values for int cmd:
        IPC_RMID  Mark  the  segment  to  be  destroyed.   The segment will actually be destroyed only after the last process detaches it (i.e., when the shm_nattch member of the associated structure shmid_ds is
        zero).  The caller must be the owner or creator of the segment, or be privileged.