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

void receiveMessage(int msqid, int type, int times) {
    Message message;
    for (int i = 0; i < times; i++) {
        if ((msgrcv(msqid, &message, sizeof(message) - sizeof(long), type, 0)) == -1) {
            perror("unable to receive message");
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

    
    Message receivedMessage;
    int numMolecules = 0;
    while (1) {
        receiveMessage(msqid, VODONIK, 2);
        receiveMessage(msqid, SUMPOR, 1);
        receiveMessage(msqid, KISEONIK, 4);

        printf("Napravljen jos jedan molekul. Ukupno molekula %d...\n", ++numMolecules);
    }

    return 0;
}