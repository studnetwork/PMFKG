#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int hitCounter = 0;

void signal_handler(int sig) {
    printf("Kraj... udario sam lopticu %d puta\n", hitCounter);
    exit(0);
}

void validateReturnValue(int returnValue) {
    if (returnValue == -1) {
        perror("unexpected error occurred");
        exit(1);
    }
}

int main() {

    key_t key = ftok("./ping.c", 'a');
    validateReturnValue(key);

    int semnum = 2;
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
        sem_init.array[0] = 1;
        sem_init.array[1] = 0;

        semctl(semid, 0, SETALL, sem_init);
    }

    signal(SIGINT, signal_handler);

    struct sembuf opr_dec, opr_inc;
    
    opr_dec.sem_num = 1;
    opr_dec.sem_op = -1;
    opr_dec.sem_flg = 0;

    opr_inc.sem_num = 0;
    opr_inc.sem_op = 1;
    opr_inc.sem_flg = 0;

    int status;
    while (1) {
        status = semop(semid, &opr_dec, 1);
        validateReturnValue(status);

        printf("pong\n");
        hitCounter++;

        sleep(5);

        status = semop(semid, &opr_inc, 1);
        validateReturnValue(status);
    }

    return 0;
}