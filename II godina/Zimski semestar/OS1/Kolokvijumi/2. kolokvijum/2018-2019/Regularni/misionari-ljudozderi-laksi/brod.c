#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <errno.h>
#include <unistd.h>

typedef enum {
    MISIONARI = 0,
    LJUDOZDERI,
    MIX
} Kombinacija;

void validateReturnValue(int returnValue) {
    if (returnValue == -1) {
        perror("unexpected error");
        exit(1);
    }
}

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void izvrsi_operaciju(int semid, struct sembuf opr, int kolikoPuta) {
    int rv;
    for (int i = 0; i < kolikoPuta; i++) {
        rv = semop(semid, &opr, 1);
        validateReturnValue(rv);
    }
}

int main() {

    key_t key = ftok("./misionar.c", 'a');
    validateReturnValue(key);

    int semnum = 4;
    int semflg = 0644 | IPC_CREAT | IPC_EXCL;
    int semid = semget(key, semnum, semflg);

    if (semid == -1) {
        if (errno == EEXIST) {
            semid = semget(key, semnum, 0);
        } else {
            validateReturnValue(semid);
        }
    } else {
        union semun sem_init;
        sem_init.array = (unsigned short*)malloc(semnum * sizeof(unsigned short));

        sem_init.array[0] = 0; // semafor za prijavljivanje misionara
        sem_init.array[1] = 0; // semafor za prijavljivanje ljudozdera
        sem_init.array[2] = 0; // semafor za obavestavanje misionara
        sem_init.array[3] = 0; // semafor za obavestavanje ljudozdera

        int rv = semctl(semid, 0, SETALL, sem_init);
        validateReturnValue(rv);
    }

    struct sembuf opr_inc_misionar, opr_inc_ljudozder, opr_dec_misionar, opr_dec_ljudozder;

    opr_inc_misionar.sem_num = 2;
    opr_inc_misionar.sem_op = 1;
    opr_inc_misionar.sem_flg = 0;

    opr_inc_ljudozder.sem_num = 3;
    opr_inc_ljudozder.sem_op = 1;
    opr_inc_ljudozder.sem_flg = 0;

    opr_dec_misionar.sem_num = 0;
    opr_dec_misionar.sem_op = -1;
    opr_dec_misionar.sem_flg = 0;

    opr_dec_ljudozder.sem_num = 1;
    opr_dec_ljudozder.sem_op = -1;
    opr_dec_ljudozder.sem_flg = 0;

    srand(getpid());
    int rv;
    Kombinacija kombinacija;
    while (1) {
        kombinacija = (Kombinacija) rand() % 3;
        if (kombinacija == MISIONARI) {
            printf("Cekam izabranu kombinacija je: 3x misionar\n");
            izvrsi_operaciju(semid, opr_dec_misionar, 3);

            printf("Javljam putnicima da su se ukrcali...\n");
            izvrsi_operaciju(semid, opr_inc_misionar, 3);
        } else if (kombinacija == LJUDOZDERI) {
            printf("Cekam izabranu kombinacija je: 3x ljudozder\n");
            izvrsi_operaciju(semid, opr_dec_ljudozder, 3);

            printf("Javljam putnicima da su se ukrcali...\n");
            izvrsi_operaciju(semid, opr_inc_ljudozder, 3);
        } else {
            printf("Cekam izabranu kombinacija je: 2x misionar, 1x ljudozder\n");
            izvrsi_operaciju(semid, opr_dec_misionar, 2);
            izvrsi_operaciju(semid, opr_dec_ljudozder, 1);

            printf("Javljam putnicima da su se ukrcali...\n");
            izvrsi_operaciju(semid, opr_inc_misionar, 2);
            izvrsi_operaciju(semid, opr_inc_ljudozder, 1);
        }

        printf("Brod se otisnuo od obale!\n");
        sleep(2);
    }

    return 0;
}