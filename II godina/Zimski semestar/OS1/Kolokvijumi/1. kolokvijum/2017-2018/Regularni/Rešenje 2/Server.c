#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <string.h>
#include <signal.h>

#define MAX_MESSAGE_LENGTH 50

int msgQueueId = -1;
int serverAlive = 1;

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
    char message[MAX_MESSAGE_LENGTH];
} Message;

void removeQueue(int msgQueueId) {
    if (msgQueueId != -1) { 
        if ((msgctl(msgQueueId, IPC_RMID, NULL)) == -1) {
            perror("Unable to remove queue: ");
            exit(1);
        }
    }
}

void signal_handler(int sig) {
    serverAlive = 0;

    if (msgQueueId != -1) {
        Message message;
        message.mtype = 1; // always send to first player
        strcpy(message.message, "KRAJ\0");

        if ((msgsnd(msgQueueId, &message, sizeof(message) - sizeof(long), 0)) == -1) {
            perror("Unable to sign off player: ");
            exit(1);
        }
    }
}

int main() {

    int numberOfPlayers;
    printf("Enter number of players:\n");
    scanf("%d", &numberOfPlayers);
    getchar();

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

    int *playersQueues = (int*)malloc(numberOfPlayers * sizeof(int));
    SignInMessage signInMessage;

    // wait for N players to sign in
    for (int i = 0; i < numberOfPlayers; i++) {
        if ((msgrcv(msgQueueId, &signInMessage, sizeof(signInMessage) - sizeof(long), 1, 0)) == -1) {
            perror("Unable to validate all the players: ");
            exit(1);
        }

        playersQueues[i] = signInMessage.msgQueueId; // each player will be notified on his specific queue that it's joined
    }

    JoinedGameMessage joinedGameMessage;
    joinedGameMessage.mtype = 1;
    
    // send ordinals to the players
    for (int i = 0; i < numberOfPlayers; i++) {
        joinedGameMessage.ordinalNumber = i + 1;

        if ((msgsnd(playersQueues[i], &joinedGameMessage, sizeof(joinedGameMessage) - sizeof(long), 0)) == -1) {
            perror("Unable to approve player: ");
            exit(1);
        }
    }

    // game begins, all players joined

    printf("%d\n", getpid());

    Message message;
    char tempMessage[MAX_MESSAGE_LENGTH];

    signal(SIGINT, signal_handler);

    while (serverAlive) {

        printf("Enter a message to play with chinese whispers: ");
        fgets(tempMessage, MAX_MESSAGE_LENGTH, stdin);

        strncpy(message.message, tempMessage, strlen(tempMessage) - 1);
        message.message[strlen(tempMessage) - 1] = '\0';
        message.mtype = 1; // always send to first player
        if ((msgsnd(msgQueueId, &message, sizeof(message) - sizeof(long), 0)) == -1) {
            perror("Unable to send message to a player: ");
            exit(1);
        }

        if ((msgrcv(msgQueueId, &message, sizeof(message) - sizeof(long), numberOfPlayers + 1, 0)) == -1) {
            perror("Unable to receive message from a last player: ");
            exit(1);
        }

        printf("Message received from last player: %s\n", message.message);
        if (strcmp(message.message, "KRAJ") == 0) {
            break;
        }
    }

    removeQueue(msgQueueId);

    return 0;
}