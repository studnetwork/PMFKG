#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <string.h>

typedef struct poruka
{
    long tip;
    int pid;
}poruka;

int id_reda;
int rbr;

typedef struct tekst
{
    long tip;
    char por[20];
}tekst;

void signal_handler(int sig)
{
    tekst t;
    t.tip = rbr;
    strcpy(t.por, "KRAJ");
    msgsnd(id_reda, &t, sizeof(t), 0); 

    exit(0);
}

void izmeni(char* por)
{
    int randomKarakter=rand()%strlen(por);
 
    por[randomKarakter] = por[rand()%strlen(por)];

}

int main()
{
    key_t kljuc = ftok("./server.c", 34); //kreiralikljuc

    id_reda = msgget(kljuc, IPC_CREAT|0666);

    poruka moja_poruka;
    
    moja_poruka.tip = 1;
    moja_poruka.pid = getpid();
    
    
    msgsnd(id_reda, &moja_poruka, sizeof(moja_poruka), 0); //prijava poslata


    msgrcv(id_reda, &moja_poruka, sizeof(moja_poruka), getpid(), 0); //pid je za rbr

    printf("PRIJAVLJEN %d\n", moja_poruka.pid);




    rbr = moja_poruka.pid;
    tekst t;

    srand(getpid());
    signal(SIGINT, signal_handler);

    while(1)
    {
        msgrcv(id_reda, &t, sizeof(t), rbr, 0);
        t.tip = rbr+1; 


        printf("Primljena poruka: %s\n", t.por);
        if(strcmp(t.por, "KRAJ")==0)
        {
              msgsnd(id_reda, &t, sizeof(t), 0);
              break;
        }
        else
        {
            izmeni(t.por);
			printf("Izmenjena poruka: %s\n", t.por);
            msgsnd(id_reda, &t, sizeof(t), 0);
        }
        
    }

}
