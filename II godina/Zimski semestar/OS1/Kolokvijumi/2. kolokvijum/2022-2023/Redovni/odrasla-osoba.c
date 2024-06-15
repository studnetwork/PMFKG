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

#define BROJ_KUTIJA 10
#define CENA_KOKICA 100

typedef union {
    int val;
    struct semid_ds *buf;
    ushort *array;
} Semun;

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

    printf("ODRASLA_OSOBA: Cekam ispred prodavnice\n");
    P.sem_num = 0;
    P.sem_op = -2;
    semop(semid, &P, 1);
    printf("ODRASLA_OSOBA: Usao sam u prodavnicu\n");
    P.sem_num = 1;
    P.sem_op = -1;
    semop(semid, &P, 1);
    printf("ODRASLA_OSOBA: Ima kokica na pultu, cekam da se oslobodi pult\n");
    P.sem_num = 3;
    P.sem_op = -1;
    semop(semid, &P, 1);
    printf("ODRASLA_OSOBA: Prisao sam pultu, uzimam kokice\n");
    sleep(5);
    printf("ODRASLA_OSOBA: Uzeo sam kokice\n");
    V.sem_num = 3;
    V.sem_op = 1;
    semop(semid, &V, 1);
    printf("ODRASLA_OSOBA: Proveravam da li imam novca za kokice\n");
    if(rand()%4!=0) {
        printf("ODRASLA_OSOBA: Imam dovljno novca i cekam u redu na kasi\n");
        P.sem_num = 4;
        P.sem_op = -1;
        semop(semid, &P, 1);
        printf("ODRASLA_OSOBA: Placam kupljene kokice\n");
        sleep(5);
        int *pazar = shmat(shmid, NULL, 0);
        *pazar += CENA_KOKICA;
        shmdt(pazar);
        V.sem_num = 4;
        V.sem_op = 1;
        semop(semid, &V, 1);
        V.sem_num = 2;
        V.sem_op = 1;
        semop(semid, &V, 1);
    } else {
        printf("ODRASLA_OSOBA: Nemam dovljno novca i cekam da se oslobodi pult\n");
        P.sem_num = 3;
        P.sem_op = -1;
        semop(semid, &P, 1);
        printf("ODRASLA_OSOBA: Prisao sam pultu i vracam neplacene kokice\n");
        sleep(5);
        V.sem_num = 1;
        V.sem_op = 1;
        semop(semid, &V, 1);
        V.sem_num = 3;
        V.sem_op = 1;
        semop(semid, &V, 1);
    }
    printf("ODRASLA_OSOBA: Izlazim iz prodavnice\n");
    sleep(2);
    V.sem_num = 0;
    V.sem_op = 2;
    semop(semid, &V, 1);
    printf("ODRASLA_OSOBA: Otisao sam iz prodavnice\n");
}