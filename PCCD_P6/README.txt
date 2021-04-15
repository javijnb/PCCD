The  msgget() system call returns the System V message queue identifier
associated with the value of the key argument.  A new message queue  is
created  if  key has the value IPC_PRIVATE or key isn't IPC_PRIVATE, no
message queue with the given key key exists, and IPC_CREAT is specified
in msgflg

int msgctl(int msqid, int cmd, struct msqid_ds *buf);
msgctl()  performs  the  control  operation specified by cmd on the System V message queue with
identifier msqid.

int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);

ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);

The msgsnd() and msgrcv() system calls are used, respectively, to send messages to, and receive
messages from, a System V message queue.  The calling process must have write permission on the
message queue in order to send a message, and read permission to receive a message.

The msgp argument is a pointer to a caller-defined structure of the following general form:

        struct msgbuf {
            long mtype;       /* message type, must be > 0
            char mtext[1];    /* message data
        };