#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

int *num;

void signal_handler(int sig) {
    printf("Ukupno primljenih paketa: %d\n", *num);
    exit(0);
}

void validateReturnValue(int returnValue) {
    if (returnValue == -1) {
        perror("unexpected error occurred");
        exit(1);
    }
}

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main() {

    key_t key = ftok("./sluzbenik.c", 'a');
    validateReturnValue(key);

    int semflg = 0644 | IPC_CREAT | IPC_EXCL;
    int semnum = 2;
    int semid = semget(key, semnum, semflg);

    if (semid == -1) {
        if (errno == EEXIST) {
            semid = semget(key, semnum, 0);
        } else {
            validateReturnValue(semid);
        }
    } else {
        union semun sem_init;
        sem_init.array = (short unsigned int*)malloc(semnum * sizeof(short unsigned int));
        sem_init.array[0] = 1;
        sem_init.array[1] = 0;

        semctl(semid, 0, SETALL, sem_init);
    }

    int shmflg = 0644 | IPC_CREAT;
    int shmid = shmget(key, sizeof(int), shmflg);
    validateReturnValue(shmid);

    num = (int*) shmat(shmid, NULL, 0);

    signal(SIGINT, signal_handler);

    struct sembuf opr_inc_mutex, opr_dec_mutex, opr_dec_product;

    opr_inc_mutex.sem_num = 0;
    opr_inc_mutex.sem_op = 1;
    opr_inc_mutex.sem_flg = 0;

    opr_dec_mutex.sem_num = 0;
    opr_dec_mutex.sem_op = -1;
    opr_dec_mutex.sem_flg = 0;

    opr_dec_product.sem_num = 1;
    opr_dec_product.sem_op = -1;
    opr_dec_product.sem_flg = 0;

    int status;
    while (1) {
        status = semop(semid, &opr_dec_product, 1);
        validateReturnValue(status);

        status = semop(semid, &opr_dec_mutex, 1);
        validateReturnValue(status);

        printf("Preuzeo %d paket!\n", *num);
        sleep(5);
        printf("Ukupno poslao %d posiljki!\n", 5 * (*num));

        status = semop(semid, &opr_inc_mutex, 1);
        validateReturnValue(status);
    }

    return 0;
}