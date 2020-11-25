#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MAX_MESSAGE_LENGTH 50

typedef struct Message {
    long mtype;
    int processId;
    char message[MAX_MESSAGE_LENGTH];
} Message;

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

    Message messageToSend, messageToReceive;
    messageToSend.mtype = 1;
    messageToSend.processId = getpid();

    while (1) {

        printf("Enter a new message:\n");
        fgets(messageToSend.message, MAX_MESSAGE_LENGTH, stdin);
        messageToSend.message[strlen(messageToSend.message) - 1] = '\0';

        if ((msgsnd(msgQueueId, &messageToSend, sizeof(messageToSend) - sizeof(long), 0)) == -1) {
            perror("Unable to send message to server: ");
            exit(1);
        }

        if (strcmp(messageToSend.message, "dosta") == 0) {
            break;
        }

        sleep(5); // to easier see in the console

        if ((msgrcv(msgQueueId, &messageToReceive, sizeof(messageToReceive) - sizeof(long), getpid(), 0)) == -1) {
            perror("Unable to receive message from server: ");
            exit(1);
        }

        printf("Received message from the server: %s\n", messageToReceive.message);
    }

    return 0;
}