#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/msg.h>

#define MSGSZ (sizeof(_MSG)-sizeof(long))
#define PROJID 33

// ko je primalac poruke
#define MSGTY_ORG 1
#define MSGTY_UC 2
#define MSGTY_AU 3

typedef struct _msg {
    long type;
    int rbr;
    int N;
    int cena;
} _MSG;

int main()
{
    int myRBR, N;

    // kreiranje glavnog reda (pult)
    key_t mainKey = ftok("./organizator.c", PROJID);
    int mainQID = msgget(mainKey, IPC_CREAT | 0666);

    _MSG snd, rcv;

    // slanje prijave
    snd.type = MSGTY_ORG;
    msgsnd(mainQID, &snd, MSGSZ, 0);
    printf("Poslata prijava\n");

    // prijem RBR-a
    msgrcv(mainQID, &rcv, MSGSZ, MSGTY_UC, 0);
    myRBR = rcv.rbr;
    N = rcv.N;
    printf("Stigao RBR: %d\n", myRBR);


    // AUKCIJA
    int auRBR;

    printf("Prijavljujem se na aukciju br: ");
    scanf("%d", &auRBR);

    key_t key = ftok("./organizator.c", PROJID + auRBR);
    int qid = msgget(key, IPC_CREAT | 0666);

    snd.type = MSGTY_AU;
    msgsnd(qid, &snd, MSGSZ, 0);

    msgrcv(qid, &rcv, MSGSZ, MSGTY_UC, 0);

    int k = 0;
    while (k < 3)
    {
        // saljem ponudu
        printf("Unesi cenu ponude: ");
        snd.type = MSGTY_AU;
        snd.rbr = myRBR;
        scanf("%d", &(snd.cena));
        msgsnd(qid, &snd, MSGSZ, 0);

        // rukovodilac mi javlja koji ucesnik ima najbolju ponudu
        msgrcv(qid, &rcv, MSGSZ, MSGTY_UC, 0);
        if(rcv.rbr == myRBR)
            printf("Ja sam pobednik nakon kruga %d, sa iznosom od %d dinara\n", k+1, rcv.cena);
        else
            printf("Pobednik nakon kruga %d, je ucesnik br. %d, sa iznosom od %d dinara\n", k+1, rcv.rbr, rcv.cena);
    
        k++;
    }

    if(rcv.rbr == myRBR)
        printf("Ja sam pobednik na aukciji za knjigu %d, sa iznosom od %d dinara\n", auRBR, rcv.cena);
    else
        printf("Pobednik na aukciji za knjigu %d, je ucesnik br. %d, sa iznosom od %d dinara\n", auRBR, rcv.rbr, rcv.cena);

}