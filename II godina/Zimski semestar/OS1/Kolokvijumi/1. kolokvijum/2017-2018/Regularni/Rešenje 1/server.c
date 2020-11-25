#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

typedef struct poruka
{
    long tip;
    int pid;
}poruka;

typedef struct tekst
{
    long tip;
    char por[20];
}tekst;

int id_reda;

void zavrsi()
{
    sleep(5);
    
    msgctl(id_reda, IPC_RMID, NULL);
    exit(0);
}

void signal_handler(int sig)
{

    tekst t;
    t.tip = 1;
    strcpy(t.por, "KRAJ");
    msgsnd(id_reda, &t, sizeof(t), 0); 

    zavrsi();
}

int main()
{
    key_t kljuc = ftok("./server.c", 34);

     id_reda = msgget(kljuc, IPC_CREAT|0666);

    poruka moja_poruka;
  
    int n;
    scanf("%d", &n);
    getc(stdin);
    int i;


    for ( i = 0; i < n; i++)
    {
        msgrcv(id_reda, &moja_poruka, sizeof(moja_poruka), 1, 0);
        moja_poruka.tip = moja_poruka.pid;
        moja_poruka.pid = i + 1;

        msgsnd(id_reda, &moja_poruka, sizeof(moja_poruka), 0);
    }

    tekst t;

    signal(SIGINT, signal_handler);
    while(1)
    {
        printf("Unesi novu poruku:\n");
        fgets(t.por, sizeof(t.por), stdin);
        t.por[strlen(t.por)-1] = '\0';
        t.tip = 1;

        msgsnd(id_reda, &t, sizeof(t), 0);


        msgrcv(id_reda, &t, sizeof(t), n+1, 0); //server cita poslednju poryku
        printf("Izmenjena poruka je: %s\n", t.por);

        if(strcmp(t.por, "KRAJ") == 0)
        {
            zavrsi();
        }
    }
    

}