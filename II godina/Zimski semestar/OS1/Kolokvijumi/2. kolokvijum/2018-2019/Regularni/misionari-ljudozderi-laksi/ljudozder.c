#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <errno.h>
#include <unistd.h>

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

    struct sembuf opr_inc, opr_dec;

    opr_inc.sem_num = 1;
    opr_inc.sem_op = 1;
    opr_inc.sem_flg = 0;

    opr_dec.sem_num = 3;
    opr_dec.sem_op = -1;
    opr_dec.sem_flg = 0;

    int pid, rv;
    while (1) {
        pid = fork();
        validateReturnValue(pid);

        if (pid == 0) {
            rv = semop(semid, &opr_inc, 1);
            validateReturnValue(rv);

            printf("Ljudozder %d se prijavio!\n", getpid());  

            rv = semop(semid, &opr_dec, 1);
            validateReturnValue(rv);

            printf("Ljudozder %d se ukrcao na brod! (zavrsavam)\n", getpid());

            break;
        }

        sleep(8);
    }

    return 0;
}