#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/sem.h>
#include <errno.h>
#include <sys/msg.h>

enum {
    VODONIK = 1,
    SUMPOR,
    KISEONIK
};

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

typedef struct {
    long mtype;
} Message;

void validateReturnValue(int returnValue) {
    if (returnValue == -1) {
        perror("unexpected error occurred");
        exit(1);
    }
}

void perform_op(int semid, struct sembuf *opr, int times) {
    int rv;
    for (int i = 0; i < times; i++) {
        rv = semop(semid, opr, 1);
        validateReturnValue(rv);
    }
}

void send_message(int msqid, int type, int times) {
    Message message;
    message.mtype = type;

    for (int i = 0; i < times; i++) {
        if ((msgsnd(msqid, &message, sizeof(message) - sizeof(long), 0)) == -1) {
            perror("unable to send message");
            exit(1);
        }
    }
}

int main() {

    key_t key = ftok("./vodonik.c", 'a');
    validateReturnValue(key);

    int msgflg = 0644 | IPC_CREAT;
    int msqid = msgget(key, msgflg);
    validateReturnValue(msqid);

    int semnum = 3;
    int semflg = 0644 | IPC_CREAT | IPC_EXCL;
    int semid = semget(key, semnum, semflg);

    if (semid == -1) {
        if (errno == EEXIST) {
            semid = semget(key, semnum, 0);
        } else {
            validateReturnValue(semid);
        }
    } else {
        union semun init_sem;
        init_sem.array = (unsigned short*)malloc(semnum * sizeof(unsigned short));

        init_sem.array[0] = 2; // sem za vodonik
        init_sem.array[1] = 0; // sem za sumpor
        init_sem.array[2] = 0; // sem za kiseonik

        int rv = semctl(semid, 0, SETALL, init_sem);
        validateReturnValue(rv);
    }

    struct sembuf opr_dec, opr_inc;

    opr_dec.sem_num = 0;
    opr_dec.sem_op = -1;
    opr_dec.sem_flg = 0;

    opr_inc.sem_num = 1;
    opr_inc.sem_op = 1;
    opr_inc.sem_flg = 0;

    while (1) {
        perform_op(semid, &opr_dec, 2);

        printf("Pravim atome...\n");
        sleep(5);

        send_message(msqid, VODONIK, 2);

        perform_op(semid, &opr_inc, 1);

        printf("Kreirana dva atoma vodonika!\n");
    }

    return 0;
}