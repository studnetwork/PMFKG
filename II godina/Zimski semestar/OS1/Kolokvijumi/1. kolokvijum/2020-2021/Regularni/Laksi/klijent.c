#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
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
    int i, j;
    int queeID = msgget(kljuc, 0660 | IPC_CREAT);
    if (queeID == -1)
    {
        printf("GRESKA\n");
        exit(1);
    }
    msg poruka;
    poruka.type = MAX_SIZE + 1;
    poruka.flag = getpid();
    msgsnd(queeID, &poruka, PORUKA_SIZE, 0);
    msgrcv(queeID, &poruka, PORUKA_SIZE, getpid(), 0);
    int rbr = poruka.flag;
    if (rbr % 2)
    {
        //prvi
        printf("Unesite rec koja se pogadja\n");
        char rec[50], pogodjeno[50];
        scanf("%s", rec);
        int n = strlen(rec), p = 0;
        for (i = 0; i < n; i++)
            pogodjeno[i] = '*';
        pogodjeno[n] = '\0';
        poruka.type = rbr;
        strcpy(poruka.message, pogodjeno);
        poruka.flag = 0;
        msgsnd(queeID, &poruka, PORUKA_SIZE, 0); //pogadjanje pocinje
        for (i = 0; i < 5; i++)
        {
            msgrcv(queeID, &poruka, PORUKA_SIZE, rbr + 1, 0);
            char c = poruka.message[0];
            for (j = 0; j < n; j++)
            {
                if (c == rec[j] && pogodjeno[j] == '*')
                {
                    pogodjeno[j] = c;
                    p++;
                }
            }
            if (p == n)
            {
                printf("Igrac je pogodio rec. Kraj igre.\n");
                poruka.type = rbr;
                poruka.flag = 1;
                strcpy(poruka.message, pogodjeno);
                msgsnd(queeID, &poruka, PORUKA_SIZE, 0);
                exit(0);
            }
            poruka.type = rbr;
            strcpy(poruka.message, pogodjeno);
            msgsnd(queeID, &poruka, PORUKA_SIZE, 0);
        }
        msgrcv(queeID, &poruka, PORUKA_SIZE, rbr + 1, 0);
        if (strcmp(poruka.message, rec) == 0)
        {
            printf("Igrac je pogodio rec. Kraj igre.\n");
            poruka.flag = 1;
        }
        else
        {
            printf("Igrac nije pogodio rec. Kraj igre.\n");
            poruka.flag = 0;
        }
        strcpy(poruka.message, rec);
        poruka.type = rbr;
        msgsnd(queeID, &poruka, PORUKA_SIZE, 0);
    }
    else
    {
        //drugi
        for (i = 0; i < 5; i++)
        {
            msgrcv(queeID, &poruka, PORUKA_SIZE, rbr - 1, 0);
            printf("Igra pocinje\n");
            char c;
            for (i = 0; i < 5; i++)
            {
                printf("\nUnesite slovo koje pogadjate\n");
                c = getchar();
                if (c == ' ' || c == '\n' || c == '\t')
                    scanf("%c", &c);
                poruka.type = rbr;
                poruka.message[0] = c;
                msgsnd(queeID, &poruka, PORUKA_SIZE, 0);
                msgrcv(queeID, &poruka, PORUKA_SIZE, rbr - 1, 0);
                printf("Rec posle pogadjanja:%s\n", poruka.message);
                if (poruka.flag)
                {
                    printf("Pogodio sam rec.Kraj igre\n");
                    exit(0);
                }
            }
            printf("\nUnesite rec koju pogadjate\n");
            scanf("%s", poruka.message);
            poruka.type = rbr;
            msgsnd(queeID, &poruka, PORUKA_SIZE, 0);
            msgrcv(queeID, &poruka, PORUKA_SIZE, rbr - 1, 0);
            printf("Zadata rec:%s\n", poruka.message);
            if (poruka.flag)
            {
                printf("Pogodio sam rec.Kraj igre\n");
            }
            else
            {
                printf("Nisam pogodio sam rec.Kraj igre\n");
            }
        }
    }
    return 0;
}
