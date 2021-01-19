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

int N, M, mainQID;

void Aukcija(int myRBR)
{
    // povezivanje na red za aukciju
    key_t key = ftok("./organizator.c", PROJID + myRBR);
    int qid = msgget(key, IPC_CREAT | 0666);

    int i;
    _MSG snd, rcv;

    for(i = 0; i < M; i++) {
        msgrcv(qid, &rcv, MSGSZ, MSGTY_AU, 0);
    }

    snd.type = MSGTY_UC;
    for(i = 0; i < M; i++) {
        msgsnd(qid, &snd, MSGSZ, 0);
    }

    int k = 0, mxRBR = -1, mxCena = -1;
    while (k < 3)
    {
        // dobijam ponude svih ucesnika ove aukcije, i odredjujem najbolju ponudu
        for(i = 0; i < M; i++) {
            msgrcv(qid, &rcv, MSGSZ, MSGTY_AU, 0);
            if(rcv.cena > mxCena) {
                mxCena = rcv.cena;
                mxRBR = rcv.rbr;
            }
        }

        // obavestavanje ucesnika o najboljoj ponudi
        snd.type = MSGTY_UC;
        snd.cena = mxCena;
        snd.rbr = mxRBR;
        for(i = 0; i < M; i++)
            msgsnd(qid, &snd, MSGSZ, 0);
        
        k++;
    }

    snd.type = MSGTY_ORG;
    snd.cena = mxCena;
    snd.rbr = mxRBR;
    snd.N = myRBR;
    msgsnd(mainQID, &snd, MSGSZ, 0);

}

void OrgHandler(int sig)
{
    _MSG rcv;

    int i;
    for(i = 0; i < N; i++) {
        msgrcv(mainQID, &rcv, MSGSZ, MSGTY_ORG, 0);
        printf("Knjiga br. %d je prodata ucesniku br. %d za cenu od %d dinara\n", rcv.N, rcv.rbr, rcv.cena);
    }

    exit(3);
}

int main()
{
    signal(SIGINT, OrgHandler);

    int i;
    printf("Unesi N i M: ");
    scanf("%d%d", &N, &M);

    // kreiranje glavnog reda (pult)
    key_t mainKey = ftok("./organizator.c", PROJID);
    mainQID = msgget(mainKey, IPC_CREAT | 0666);

    _MSG snd, rcv;

    // ocekujem prijave ucesnika
    for(i = 0; i < N*M; i++)
    {
        // prijem poruke
        msgrcv(mainQID, &rcv, MSGSZ, MSGTY_ORG, 0);
        printf("Stigla prijava\n");

        // slanje poruke
        snd.type = MSGTY_UC;
        snd.rbr = i+1;
        snd.N = N;
        msgsnd(mainQID, &snd, MSGSZ, 0);
        printf("Poslat RBR %d\n", i+1);
    }

    for(i = 0; i < N; i++)
    {
        int chPID = fork();
        if(chPID == 0)
        {
            // Aukcija
            signal(SIGINT, SIG_IGN);
            Aukcija(i+1);
            exit(0);
        }
        else if(chPID > 0)
        {
            /////parent
        }
        else exit(0); // GRESKA NEKA
    }

    while(1) sleep(4);
}
