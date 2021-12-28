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
typedef union
{
    int val;
    struct semid_ds *buf;
    ushort *array;
} semun;
int main()
{
    key_t kljuc = ftok("./igrac.c", 2);
    int korpa = semget(kljuc, 3, IPC_CREAT | 0666 | IPC_EXCL);
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
    struct sembuf P, V;
    P.sem_op = -1;
    P.sem_flg = 0;

    V.sem_op = 1;
    V.sem_flg = 0;
    while (1)
    {
        P.sem_num = 2;
        semop(korpa, &P, 1); //skidam van korpe
        printf("Redar je uzeo loptu i krece ka korpi\n");
        P.sem_num = 1;
        semop(korpa, &P, 1); //skidam binarni
        printf("Redar dobio pristup korpi\n");
        sleep(2);
        V.sem_num = 0;
        semop(korpa, &V, 1); //vracam u korpu
        V.sem_num = 1;
        semop(korpa, &V, 1); //vracam binarni
        printf("Redar je vratio loptu u korpu\n");
    }
}