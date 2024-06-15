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

typedef union {
    int val;
    struct semid_ds *buf;
    ushort *array;
} Semun;

#define BROJ_KUTIJA 10
#define CENA_KOKICA 100

int main() {
    srand(time(NULL));

    int semid = semget(ftok("./prodavac.c", 'A'), 5, 0666 | IPC_CREAT | IPC_EXCL);

    if (semid != -1) {
        Semun arg;

        arg.val = 2;
        semctl(semid, 0, SETVAL, arg); // Lock prodavnice
        arg.val = BROJ_KUTIJA;
        semctl(semid, 1, SETVAL, arg); // Broj kutija na pultu
        arg.val = 0;
        semctl(semid, 2, SETVAL, arg); // Broj kutija van pulta
        arg.val = 1;
        semctl(semid, 3, SETVAL, arg); // Lock za pult
        arg.val = 1;
        semctl(semid, 4, SETVAL, arg); // Lock za kasu;
    } else 
        semid = semget(ftok("./prodavac.c", 'A'), 5, 0);
    
    int shmid = shmget(ftok("./prodavac.c", 'B'), sizeof(int), 0666 | IPC_CREAT | IPC_EXCL);

    if (shmid != -1) {
        int *pazar = shmat(shmid, NULL, 0);
        *pazar = 0;
        shmdt(pazar);
    } else 
        shmid = shmget(ftok("./prodavac.c", 'B'), sizeof(int), 0);

    struct sembuf P, V;

    P.sem_flg = 0;
    V.sem_flg = 0;

    while(1) {
        printf("PRODAVAC: Proveravam da li ima slobodnih mesta na pultu\n");
        P.sem_num = 2;
        P.sem_op = -1;
        semop(semid, &P, 1);
        printf("PRODAVAC: Ima slobodnih mesta, cekam da se pult oslobodi\n");
        P.sem_num = 3;
        P.sem_op = -1;
        semop(semid, &P, 1);
        printf("PRODAVAC: Dodajem jedno pakovanje kokica\n");
        sleep(5);
        V.sem_num = 1;
        V.sem_op = 1;
        semop(semid, &V, 1);
        printf("PRODAVAC: Dodato je jedno pakovanje na pult\n");
        V.sem_num = 3;
        V.sem_op = 1;
        semop(semid, &V, 1);
    }
}