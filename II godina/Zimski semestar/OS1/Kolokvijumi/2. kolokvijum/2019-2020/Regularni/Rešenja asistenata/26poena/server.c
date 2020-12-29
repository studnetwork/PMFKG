#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>
#include <errno.h>

int msgid;

typedef struct msg
{
    long type;
    int partija;
    long broj;
} Msg;

void signal_handler(int id)
{
    printf("Deleting queue\n");
    msgctl(msgid, IPC_RMID, NULL);
    exit(0);
}

int main()
{
    signal(SIGINT, signal_handler);
    key_t key = ftok("server.c", 0);
    int msgid = msgget(key, IPC_CREAT|0666);
    printf("Server starting\n");
    Msg msg1, msg2, msg3, msg4;
    pid_t pid;

    int partija=0;
    
    while(1)
    {
        msgrcv(msgid, &msg1, sizeof(msg1), 1, 0);
        printf("Player 1 registered : %ld\n", msg1.broj);
        msgrcv(msgid, &msg2, sizeof(msg2), 1, 0);
        printf("Player 2 registered : %ld\n", msg2.broj);
        msgrcv(msgid, &msg3, sizeof(msg3), 1, 0);
        printf("Player 3 registered : %ld\n", msg3.broj);
        msgrcv(msgid, &msg4, sizeof(msg4), 1, 0);
        printf("Player 4 registered : %ld\n", msg4.broj);
        printf("-----\nStarting the game\n-----\n");
        partija++;
        pid = fork();
        if(pid==0) // Server
        {
            msg1.type = 2;
            msg1.partija = partija;
            msg1.broj = 0;
            msgsnd(msgid, &msg1, sizeof(msg1), 0);
            msg1.broj = 1;
            msgsnd(msgid, &msg1, sizeof(msg1), 0);
            msg1.broj = 2;
            msgsnd(msgid, &msg1, sizeof(msg1), 0);
            msg1.broj = 3;
            msgsnd(msgid, &msg1, sizeof(msg1), 0);
            exit(0);
        }
    }

    return 0;
}