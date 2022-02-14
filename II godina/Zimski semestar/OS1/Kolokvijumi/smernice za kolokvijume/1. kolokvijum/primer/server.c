#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h> //ucitati ovu biblioteku ako javlja warning za wait(), mada ce raditi i bez nje

int n = 2;
int m = 2;
int msgid;

//neka klijent i server razmene 3 poruke
//klijent ce slati broj za jedan veci od broja koji je primio a server ce slati broj za 10 veci od broja koji je primio
//u ovom primeru nije fokus na obradi podataka koji se salju nego na komunikaciji i tipovima (bitno je da svi tipovi budu razliciti)
//koriseci drugu varijantu odredjivanja tipova
typedef struct
{
    long type;
    int tip_servera;
    int rbr;
    int pid; //kada se klijent prijavljuje na server salje svoj tip
    //nakon prijave se koriste tipovi kreirani na osnovu varijante 1 ili 2
} LOGIN;

#define LOGIN_SIZE sizeof(LOGIN) - sizeof(long)

typedef struct
{
    long type;
    int broj;
    int poslao;
} PORUKA;

#define PORUKA_SIZE sizeof(PORUKA) - sizeof(long)

void signal_handler(int a)
{
    int b, i;
    for (i = 0; i < n; i++)
        wait(&b);
    printf("RODITELJ:Sva deca su zavrsila. Zavrsavam i ja.\n");
    msgctl(msgid, IPC_RMID, NULL); //uklanjam red za poruke
    exit(0);
}

#define BROJ_PORUKA 3
int main()
{
    int i, j;
    key_t kljuc = ftok("./server.c", 10);
    msgid = msgget(kljuc, IPC_CREAT | 0666);
    for (i = 0; i < n; i++)
    {
        if (fork() == 0)
        {
            signal(SIGINT, SIG_IGN);
            int rbr = i + 1;
            int tip = n + i * (m + 1); // ili tip=n+(i+1)*(m+1)
            LOGIN prijava;
            PORUKA poruka;
            for (i = 0; i < m; i++) //sacekaj da se svi korisnici prijave
            {
                msgrcv(msgid, &prijava, LOGIN_SIZE, 1, 0); //primi poruku tipa 1 za login
                prijava.type = prijava.pid;
                prijava.tip_servera = tip;
                prijava.rbr = i + 1;
                msgsnd(msgid, &prijava, LOGIN_SIZE, 0);
            }
            printf("DETE %d:Moj tip je %d\n", rbr, tip);
            for (j = 1; j <= m; j++)
            {
                poruka.type = tip + j;
                poruka.broj = 0;
                msgsnd(msgid, &poruka, PORUKA_SIZE, 0);
            }
            for (i = 0; i < BROJ_PORUKA; i++)
            {
                for (j = 1; j <= m; j++)
                {
                    msgrcv(msgid, &poruka, PORUKA_SIZE, tip, 0);
                    poruka.type = tip + poruka.poslao;
                    poruka.broj += 10;
                    msgsnd(msgid, &poruka, PORUKA_SIZE, 0);
                }
            }
            exit(0);
        }
    }
    signal(SIGINT, signal_handler);
    while (1);
    return 0;
}