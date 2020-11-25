#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <ctype.h>
#include <string.h>

#define MAX_MESSAGE_LENGTH 50

typedef struct Message {
    long mtype;
    int processId;
    char message[MAX_MESSAGE_LENGTH];
} Message;

void convertMessageToUppercase(char *message) {
    for (int i = 0; message[i] != '\0'; i++) {
        message[i] = toupper(message[i]);
    }
}

void removeMessageQueue(int msgQueueId) {
    if ((msgctl(msgQueueId, IPC_RMID, NULL)) == -1) {
        perror("Unable to remove message queue: ");
        exit(1);
    }
}

int main() {

    key_t uniqueKey = ftok("/home/squirrelosopher/Desktop/OS/OS/2018-19D/domaci.pdf", 'a');
    if (uniqueKey == -1) {
        perror("Unable to obtain unique id: ");
        exit(1);
    }

    int msgflg = IPC_CREAT | 0666;
    int msgQueueId = msgget(uniqueKey, msgflg);
    if (msgQueueId == -1) {
        perror("Unable to obtain message queue id: ");
        exit(1);
    }

    Message message;

    while (1) {
        if ((msgrcv(msgQueueId, &message, sizeof(message) - sizeof(long), 1, 0)) == -1) {
            perror("Unable to receive message: ");
            exit(1);
        }

        if (strcmp(message.message, "dosta") == 0) {
            break;
        }

        printf("Received message: %s\n", message.message);
        
        convertMessageToUppercase(message.message);
        message.mtype = message.processId;
        
        printf("Sending back '%s' to %d process\n", message.message, message.processId);
        if ((msgsnd(msgQueueId, &message, sizeof(message) - sizeof(long), 0)) == -1) {
            perror("Unable to send message: ");
            exit(1);
        }

        putchar('\n');
    }

    removeMessageQueue(msgQueueId);
    return 0;
}