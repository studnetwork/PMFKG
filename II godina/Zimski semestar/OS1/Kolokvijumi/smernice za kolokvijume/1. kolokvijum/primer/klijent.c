#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>

typedef struct
{
    long type;
    int tip_servera;
    int rbr;
    int pid;
} LOGIN;

#define LOGIN_SIZE sizeof(LOGIN) - sizeof(long)

typedef struct
{
    long type;
    int broj;
    int poslao;
} PORUKA;

#define PORUKA_SIZE sizeof(PORUKA) - sizeof(long)

#define BROJ_PORUKA 3

int main()
{
    int i;
    key_t kljuc = ftok("./server.c", 10);
    int msgid = msgget(kljuc, IPC_CREAT | 0666);
    LOGIN prijava;
    PORUKA poruka;
    prijava.type = 1;
    prijava.pid = getpid();
    msgsnd(msgid, &prijava, LOGIN_SIZE, 0);
    msgrcv(msgid, &prijava, LOGIN_SIZE, getpid(), 0);
    int tip = prijava.tip_servera + prijava.rbr;
    int tip_servera = prijava.tip_servera;
    int rbr = prijava.rbr;
    printf("KLIJENT %d: Moj tip je %d\n", rbr, tip);
    for (i = 0; i < BROJ_PORUKA; i++)
    {

        msgrcv(msgid, &poruka, PORUKA_SIZE, tip, 0);
        printf("%d\n", poruka.broj);
        poruka.type = tip_servera;
        poruka.broj += 1;
        poruka.poslao = rbr;
        msgsnd(msgid, &poruka, PORUKA_SIZE, 0);
    }
    return 0;
}