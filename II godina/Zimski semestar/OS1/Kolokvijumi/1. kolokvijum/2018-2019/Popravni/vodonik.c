#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

// 1 type - H
// 2 type - S
// 3 type - O 

typedef struct Message {
    long mtype;
} Message;

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

    Message message;
    message.mtype = 1;

    while (1) {
        sleep(3); // simulates producing
        
        if ((msgsnd(msgQueueId, &message, sizeof(message) - sizeof(long), 0)) == -1) {
            perror("Unable to send message to server: ");
            exit(1);
        }

        printf("Produced one hydrogen atom...\n");
    }

}
