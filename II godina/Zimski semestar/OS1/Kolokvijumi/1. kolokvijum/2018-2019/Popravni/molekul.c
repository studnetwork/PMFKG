#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// 1 type - H
// 2 type - S
// 3 type - O

typedef struct Message {
    long mtype;
} Message;

enum atom { hydrogen = 1, sulfur, oxygen };

void fetchAtoms(int msgQueueId, int atomType, int times) {
    Message message;

    for (int i = 0; i < times; i++) {
        if ((msgrcv(msgQueueId, &message, sizeof(message) - sizeof(long), atomType, 0)) == -1) {
            perror("Unable to receive message: ");
            exit(1);
        }

        // printf("Fetched %d atom type [fetching %d/%d]\n", atomType, i + 1, times);
    }
}

int main() {

    key_t uniqueId = ftok("./molekul.c", 'a');
    if (uniqueId == -1) {
        perror("Unable to obtain unique id: ");
        exit(1);
    }

    int msgflg = IPC_CREAT | 0666;
    int msgQueueId = msgget(uniqueId, msgflg);
    if (msgQueueId == -1) {
        perror("Unable to obtain message queue id: ");
        exit(1);
    }

    int createdMolecules = 0;
    while (1) {

        fetchAtoms(msgQueueId, hydrogen, 2);

        fetchAtoms(msgQueueId, sulfur, 1);

        fetchAtoms(msgQueueId, oxygen, 4);

        printf("Napravljen jos jedan molekul. Ukupno molekula %d\n", ++createdMolecules);
    }
}
