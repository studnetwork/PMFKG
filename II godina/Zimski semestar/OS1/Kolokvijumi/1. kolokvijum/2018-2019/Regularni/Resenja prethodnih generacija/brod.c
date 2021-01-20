#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

typedef struct Message {
    long mtype;
    int pid;
} Message;

typedef enum Passenger {
    MISSIONARY = 1,
    CANNIBAL
} Passenger;

typedef enum Combination {
    THREE_MISSIONARIES,
    THREE_CANNIBALS,
    MIX // 2 missionaries, 1 cannibal
} Combination;

Message fetchPassenger(int msgQueueId, int passengerType) {
    Message message;
    if ((msgrcv(msgQueueId, &message, sizeof(message) - sizeof(long), passengerType, IPC_NOWAIT)) == -1) {
        if (errno == ENOMSG) { // no specific type message in the queue
            message.mtype = -1;
        } else {
            perror("Unable to get queue message properly: ");
            exit(1);
        }
    }

    return message;
}

void sendBackPassenger(int msgQueueId, Message message) {
    if ((msgsnd(msgQueueId, &message, sizeof(message) - sizeof(long), 0)) == -1) {
        perror("Unable to send back message to the queue: ");
        exit(1);
    }
}

void shipPassengers(Message passengerOne, Message passengerTwo, Message passengerThree) {
    printf("Otisnuo se sa obale sa sledecim putnicima: %d, %d, %d\n", passengerOne.pid, passengerTwo.pid, passengerThree.pid);

    kill(passengerOne.pid, SIGINT);
    kill(passengerTwo.pid, SIGINT);
    kill(passengerThree.pid, SIGINT);

    sleep(10);
}

void fetchPassengers(int msgQueueId, int typeOne, int typeTwo, int typeThree) {
    Message passengerOne, passengerTwo, passengerThree;

    passengerOne = fetchPassenger(msgQueueId, typeOne);
    if (passengerOne.mtype != -1) {
        passengerTwo = fetchPassenger(msgQueueId, typeTwo);
        if (passengerTwo.mtype == -1) {
            sendBackPassenger(msgQueueId, passengerOne); // send back previous passenger(s)
        } else {
            passengerThree = fetchPassenger(msgQueueId, typeThree);
            if (passengerThree.mtype == -1) {
                sendBackPassenger(msgQueueId, passengerOne); // send back previous passenger(s)
                sendBackPassenger(msgQueueId, passengerTwo); // send back previous passenger(s)
            } else {
                // ship combination
                shipPassengers(passengerOne, passengerTwo, passengerThree);
            }
        }
    }
}


int main() {

    key_t uniqueId = ftok("/home/squirrelosopher/Desktop/OS/OS/2018-19R/postavka.pdf", 'a');
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

    Message passengerOne, passengerTwo, passengerThree;
    Combination combination;
    int shipped;

    srand(getpid());

    while (1) {
        combination = (Combination) (rand() % 3);
        shipped = 0;

        switch (combination)
        {
        case THREE_MISSIONARIES:
            printf("Pokusavam da ubacim 3 Misionara...\n");
            fetchPassengers(msgQueueId, MISSIONARY, MISSIONARY, MISSIONARY);
            break;
        case THREE_CANNIBALS:
            printf("Pokusavam da ubacim 3 Kanibala...\n");
            fetchPassengers(msgQueueId, CANNIBAL, CANNIBAL, CANNIBAL);
            break;
        default:
            printf("Pokusavam da ubacim 2 Misionara i 1-og Kanibala...\n");
            fetchPassengers(msgQueueId, MISSIONARY, MISSIONARY, CANNIBAL);
            break;
        }
    }

    return 0;
}
