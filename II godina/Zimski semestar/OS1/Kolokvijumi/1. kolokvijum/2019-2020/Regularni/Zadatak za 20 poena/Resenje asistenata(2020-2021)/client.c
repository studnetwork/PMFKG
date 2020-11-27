#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_GAMES 20

typedef struct {
    long msgType;
    int PID_ID;
}loginMsg;

typedef struct{
    long msgType;
    char msgText[100];
}moveMsg; //poruka koja se salje prilikom poteza


int main()
{
    key_t commQueueKey;
    loginMsg login;
    moveMsg move;
    int commQueueID, myID;
    int miniServerPID;
    char word[100];
    int wordLen;

    commQueueKey = ftok("./server.c", 1);
    commQueueID = msgget(commQueueKey, IPC_CREAT | 0666);

    login.msgType = 2 * MAX_GAMES + 1;
    login.PID_ID = getpid();
    msgsnd(commQueueID, &login, sizeof(login), 0); //prijava serveru
    msgrcv(commQueueID, &login, sizeof(login), getpid(), 0); //server mi salje ID
    myID = login.PID_ID;

    msgrcv(commQueueID, &login, sizeof(login), getpid(), 0);
    miniServerPID = login.PID_ID;

    if(myID % 2) //neparan broj, zapocinjem igru
    {
        printf("Unesi rec:\n");
        fgets(move.msgText, sizeof(move.msgText), stdin);
        move.msgType = miniServerPID;
        msgsnd(commQueueID, &move, sizeof(move), 0);
    }

    while(1)
    {
        msgrcv(commQueueID, &move, sizeof(move), myID, 0);
        strcpy(word, move.msgText);
        wordLen = strlen(word);

        if(!strcmp(word, "pobeda"))
        {
            printf("Pobeda.\n");
            exit(0);
        }
        if(!strcmp(word, "poraz"))
        {
            printf("Poraz.\n");
            exit(0);
        }

        printf("Primljena rec %s\n", word);

        do
        {
            printf("Unesi rec:\n");
            fgets(move.msgText, sizeof(move.msgText), stdin);
        } while (word[wordLen - 3] != move.msgText[0] || word[wordLen - 2] != move.msgText[1]);
        
        move.msgType = miniServerPID;
        msgsnd(commQueueID, &move, sizeof(move), 0);
    }
}