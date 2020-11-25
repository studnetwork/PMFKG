#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <string.h>
#include <time.h>
#include <signal.h>

typedef struct SignInMessage {
    long mtype;
    int msgQueueId; // send me on this queue my ordinal number
} SignInMessage;

typedef struct JoinedGameMessage {
    long mtype;
    int ordinalNumber; // send ordinal number to specific message queue
} JoinedGameMessage;

typedef struct Message {
    long mtype;
    char message[50];
} Message;

void modifyMessage(char *message) {

    int upperLimit = strlen(message);
    int randomCharOrdinal = rand() % upperLimit;

    // random pick another char within a string

    int randomCharReplacement = rand() % upperLimit;
    message[randomCharOrdinal] = message[randomCharReplacement];
}

int gameActive = 1;
int msgQueueId = -1;
int nextOrdinal = -1;

void signal_handler(int sig) {
    gameActive = 0;

    if (msgQueueId != -1 && nextOrdinal != -1) {
        Message message;
        message.mtype = nextOrdinal;
        strcpy(message.message, "KRAJ\0");

        if ((msgsnd(msgQueueId, &message, sizeof(message) - sizeof(long), 0)) == -1) {
            perror("Unable to send ending message to a next player: ");
            exit(1);
        }
    }
}

void removeQueue(int msgQueueId) {
    if (msgQueueId != -1) { 
        if ((msgctl(msgQueueId, IPC_RMID, NULL)) == -1) {
            perror("Unable to remove queue: ");
            exit(1);
        }
    }
}

int main() {

    int privateQueueId = msgget(IPC_PRIVATE, 0666);
    if (privateQueueId == -1) {
        perror("Unable to obtain private queue for signing in: ");
        exit(1);
    }

    SignInMessage signInMessage;
    signInMessage.mtype = 1;
    signInMessage.msgQueueId = privateQueueId;

    key_t uniqueKey = ftok("/home/squirrelosopher/Desktop/OS/OS/2017-18R/Server.c", 'a');
    if (uniqueKey == -1) {
        perror("Unable to obtain unique id: ");
        exit(1);
    }
    
    int msgflg = IPC_CREAT | 0666;
    msgQueueId = msgget(uniqueKey, msgflg);
    if (msgQueueId == 1) {
        perror("Unable to create/obtain message queue id: ");
        exit(1);
    }

    if ((msgsnd(msgQueueId, &signInMessage, sizeof(signInMessage) - sizeof(long), 0)) == -1) {
        perror("Unable to send sign in message: ");
        exit(1);
    }

    JoinedGameMessage joinedGameMessage;
    if ((msgrcv(privateQueueId, &joinedGameMessage, sizeof(joinedGameMessage) - sizeof(long), 1, 0)) == -1) {
        perror("Unable to receive joining respond: ");
        exit(1);
    }

    // joined the game, have ordinal number

    nextOrdinal = joinedGameMessage.ordinalNumber + 1;
    Message message;
    srand(getpid());

    signal(SIGINT, signal_handler);

    while (gameActive) {

        if ((msgrcv(msgQueueId, &message, sizeof(message) - sizeof(long), joinedGameMessage.ordinalNumber, 0)) == -1) {
            perror("Unable to receive specific player message: ");
            exit(1);
        }

        message.mtype = joinedGameMessage.ordinalNumber + 1; // always send to a next player
        if (strcmp(message.message, "KRAJ") == 0) {
            if ((msgsnd(msgQueueId, &message, sizeof(message) - sizeof(long), 0)) == -1) {
                perror("Unable to send message to a next player: ");
                exit(1);
            }

            break;
        } else {
            modifyMessage(message.message);

            if ((msgsnd(msgQueueId, &message, sizeof(message) - sizeof(long), 0)) == -1) {
                perror("Unable to send modified message to a next player: ");
                exit(1);
            }
        }
    }

    removeQueue(msgQueueId);

    return 0;
}