#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
typedef struct
{
    long type;
    int flag;
    char message[50];
} msg;
#define PORUKA_SIZE sizeof(msg) - sizeof(long)
#define MAX_SIZE 10
int main()
{
    key_t kljuc = ftok("./server.c", 10);
    int queeID = msgget(kljuc, IPC_CREAT | 0666);
    if (queeID == -1)
    {
        printf("GRESKA\n");
        exit(1);
    }
    msg poruka;
    int n, i;
    scanf("%d", &n);
    for (i = 1; i < n + 1; i++)
    {
        msgrcv(queeID, &poruka, PORUKA_SIZE, MAX_SIZE + 1, 0);
        poruka.type = poruka.flag;
        poruka.flag = i;
        msgsnd(queeID, &poruka, PORUKA_SIZE, 0);
    }
    return 0;
}