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

typedef struct{
    long msgType;
    int PID_ID;
}loginMsg;

typedef struct{
    long msgType;
    char msgText[100];
}moveMsg; //poruka koja se salje prilikom poteza

typedef struct{
    long msgType;
    int winnerID;
}winnerMsg;

int gamesArray[20];
int numOfGames = 0;
int commQueueID, dataQueueID;

int checkAWord(int player1ID, int player2ID)
{
    moveMsg move;
    char word[100];
    int wordLen;

    winnerMsg winner;

    msgrcv(commQueueID, &move, sizeof(move), getpid(), 0);
    strcpy(word, move.msgText);
    wordLen = strlen(word);

    if(word[wordLen - 3] == 'n' && word[wordLen - 2] == 't')
    {
        //kraj igre
        printf("Partija igraca %d i %d je gotova.\n", player1ID, player2ID);
        //javi igracima rezultate
        strcpy(move.msgText, "pobeda");
        move.msgType = player1ID;
        msgsnd(commQueueID, &move, sizeof(move), 0);
        strcpy(move.msgText, "poraz");
        move.msgType = player2ID;
        msgsnd(commQueueID, &move, sizeof(move), 0);

        winner.msgType = 1;
        winner.winnerID = player1ID;
        msgsnd(dataQueueID, &winner, sizeof(winner), 0);
        return 1;
    }
    else
    {
        //prosledi ovu poruku drugom igracu
        move.msgType = player2ID;
        msgsnd(commQueueID, &move, sizeof(move), 0);
        return 0;
    }
}

void serverSigHandler(int sig)
{
    int even = 0; //parni
    int odd = 0; //neparni
    winnerMsg winner;

    for(int i = 0; i < numOfGames; i++)
    {
        printf("Cekam dete %d\n", gamesArray[i]);
        waitpid(gamesArray[i], NULL, 0);
    }
    //gotove su sve igre
    for(int i = 0; i < numOfGames; i++)
    {
        msgrcv(dataQueueID, &winner, sizeof(winner), 1, 0);
        if(winner.winnerID % 2)
            ++odd;
        else
            ++even;
    }

    printf("Turnir je zavrsen.\n");
    printf("Neparna/parna pozicija - %d/%d\n", odd, even);

    msgctl(commQueueID, IPC_RMID, NULL);
    msgctl(dataQueueID, IPC_RMID, NULL);
    exit(0);
}

int main()
{
    key_t commQueueKey, dataQueueKey;
    loginMsg login1, login2;
    int SN = 0;
    pid_t gamePID;
    int status; //da li je kraj ili nije
    int playerID1, playerID2;

    commQueueKey = ftok("./server.c", 1);
    dataQueueKey = ftok("./server.c", 2);

    commQueueID = msgget(commQueueKey, IPC_CREAT | 0666);
    dataQueueID = msgget(dataQueueKey, IPC_CREAT | 0666);
    signal(SIGINT, serverSigHandler);

    while(1)
    {
        //server ceka na dva igraca da se prijave
        msgrcv(commQueueID, &login1, sizeof(login1), 2 * MAX_GAMES + 1, 0);
        msgrcv(commQueueID, &login2, sizeof(login2), 2 * MAX_GAMES + 1, 0);
        login1.msgType = login1.PID_ID;
        login2.msgType = login2.PID_ID;
        login1.PID_ID = ++SN;
        login2.PID_ID = ++SN;
        msgsnd(commQueueID, &login1, sizeof(login1), 0);
        msgsnd(commQueueID, &login2, sizeof(login2), 0);

        playerID1 = login1.PID_ID;
        playerID2 = login2.PID_ID;

        
        gamePID = fork();
        if(!gamePID) //dete
        {
            signal(SIGINT, SIG_IGN);

            login1.PID_ID = getpid();
            login2.PID_ID = getpid();
            msgsnd(commQueueID, &login1, sizeof(login1), 0);
            msgsnd(commQueueID, &login2, sizeof(login2), 0);

            while(1)
            {
                status = checkAWord(playerID1, playerID2); //prvi potez ima igrac sa neparnim brojem

                if(status)
                    exit(0);
                
                status = checkAWord(playerID2, playerID1);
                if(status)
                    exit(0);
            }
        }
        else
            gamesArray[numOfGames++] = gamePID;
    }
}