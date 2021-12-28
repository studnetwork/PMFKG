//Resio: Ljubomir Matovic 58/2020
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
#define M 3
#define N 2
//brojevi igraca su 0,1, ... , M-1
typedef union
{
    int val;
    struct semid_ds *buf;
    ushort *array;
} semun;
typedef struct
{
    long type;
    int igrac;
} Poruka;
#define PORUKA_SIZE sizeof(Poruka) - sizeof(long)
int msgid, br;
void help(int s)
{
    Poruka p;
    int n;
    while ((n = rand() % M) == br); //jer moze da se desi da igrac odabere samog sebe, a to ne bi smelo da se desi
    p.type = n;
    p.igrac = br;
    printf("Dete igraca %d:Saljem poruku u pomoc igracu %d\n", br, n);
    msgsnd(msgid, &p, PORUKA_SIZE, 0);
}
int main(int argc, char *argv[])
{
    srand(time(NULL));
    br = atoi(argv[1]);
    key_t kljuc = ftok("./igrac.c", 1);
    msgid = msgget(kljuc, IPC_CREAT | 0666);
    int pid;
    kljuc = ftok("./igrac.c", 2);
    key_t kljuc1 = ftok("./igrac.c", 3);
    int korpa = semget(kljuc, 3, IPC_CREAT | 0666 | IPC_EXCL);
    int koseviSem = semget(kljuc1, M, IPC_CREAT | 0666 | IPC_EXCL);
    int kosevi = shmget(kljuc, M * sizeof(int), IPC_CREAT | 0666 | IPC_EXCL);
    if (kosevi != -1)
    {
        int *k = shmat(kosevi, NULL, 0);
        int i;
        for (i = 0; i < M; i++)
        {
            k[i] = 0;
        }
        shmdt(k);
    }
    else
    {
        kosevi = shmget(kljuc, M * sizeof(int), 0);
    }
    if (korpa != -1)
    {
        semun s;
        s.val = N;
        semctl(korpa, 0, SETVAL, s); //broj lopti u korpi
        s.val = 1;
        semctl(korpa, 1, SETVAL, s); //binarni semafor za pristup korpi
        s.val = 0;
        semctl(korpa, 2, SETVAL, s); //broj lopti koje treba da se vrate u korpu
    }
    else
    {
        korpa = semget(kljuc, 3, 0);
    }
    if (koseviSem != -1)
    {
        semun s;
        int i;
        s.val = 1;
        for (i = 0; i < M; i++)
        {
            semctl(koseviSem, i, SETVAL, s); //binarni semafor za pristup kosu
        }
    }
    else
    {
        koseviSem = semget(kljuc1, M, 0);
    }
    int *brojKoseva = shmat(kosevi, NULL, 0);
    struct sembuf P, V;
    P.sem_op = -1;
    P.sem_flg = 0;

    V.sem_op = 1;
    V.sem_flg = 0;

    pid = fork();
    int brojPromasenih = 0, izb;
    Poruka p;
    int bacanje, r;
    switch (pid)
    {
    case -1:
        printf("GRESKA\n");
        exit(1);
    case 0:
        signal(SIGINT, help);
        while (1)
        {
            sleep(10);
            P.sem_num = br;
            semop(koseviSem, &P, 1);
            printf("Dete igraca %d:Broj pogodjenih koseva je %d\n", br, brojKoseva[br]);
            V.sem_num = br;
            semop(koseviSem, &V, 1);
        }
        break;
    default:
        while (1)
        {
            printf("Igrac %d krece ka korpi\n", br);
            P.sem_num = 0;
            semop(korpa, &P, 1); //skidam broj lopti u korpi
            P.sem_num = 1;
            semop(korpa, &P, 1); //skidam binarni
            printf("Igrac %d je dobio pristup korpi i krece da uzima loptu\n", br);
            sleep(1);
            printf("Igrac %d je uzeo loptu i oslobodio pristup korpi\n", br);
            V.sem_num = 1;
            semop(korpa, &V, 1); //vracam binarni
            sleep(3);
            r = msgrcv(msgid, &p, PORUKA_SIZE, br, IPC_NOWAIT); //broj bajtova koje je procitao ili -1 ako je greska u pitanju; ako nema poruke onda vraca 0
            izb = br;
            if (r > 0)
            {
                printf("Igrac %d: Igrac %d je zatrazio pomoc\n", br, p.igrac);
                izb = p.igrac;
            }
            bacanje = rand() % 2; //gadjanje
            if (bacanje)          //izbacio sam prethodni if iz ovog kako bih izbegao code repetition
            {
                P.sem_num = izb;
                semop(koseviSem, &P, 1);
                brojKoseva[izb]++;
                V.sem_num = izb;
                semop(koseviSem, &V, 1);
                brojPromasenih = 0;
            }
            else
            {
                brojPromasenih++;
            }
            if (brojPromasenih >= 2)
            {
                brojPromasenih = 0;
                kill(pid, SIGINT);
            }
            V.sem_num = 2;
            semop(korpa, &V, 1); //povecavam broj lopti van korpe
        }
        break;
    }
    shmdt(brojKoseva);
}