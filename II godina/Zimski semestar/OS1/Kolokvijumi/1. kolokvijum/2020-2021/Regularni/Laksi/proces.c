#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/signal.h>
#include <sys/types.h>
void roditeljKraj(int a)
{
    printf("RODITELJ:Zavrsavam sa radom\n");
    exit(0);
}
int broj;
void povecaj(int a)
{
    broj++;
    printf("DETE:Uvecao sam promenljivu\n");
}
void smanji(int a)
{
    broj--;
    printf("DETE:Umanjio sam promenljivu\n");
}
void deteKraj(int a)
{
    printf("DETE:Ja zavrsavam\n");
    exit(0);
}
int main()
{
    pid_t pid;
    srand(time(0));
    broj = rand() % 10;
    pid = fork();
    switch (pid)
    {
    case -1:
        printf("GRESKA\n");
        exit(1);
        break;
    case 0:
        signal(SIGINT, &povecaj);
        signal(SIGCHLD, &smanji);
        signal(SIGQUIT, &deteKraj);
        sleep(6);
        while (1)
        {
            sleep(3);
            printf("DETE:Ja sam dete %d %d\n", getpid(), broj);
        }
        break;
    default:
        signal(SIGCHLD, &roditeljKraj);
        while (1)
        {
            sleep(6);
            printf("RODITELJ: broj je %d\n", broj);
            if (broj % 2 == 0)
            {
                if (broj == 0)
                {
                    printf("RODITELJ:saljem SIGQUIT\n");
                    kill(pid, SIGQUIT);
                }
                else
                {
                    printf("RODITELJ:saljem SIGINT\n");
                    kill(pid, SIGINT);
                }
            }
            else
            {
                printf("RODITELJ:saljem SIGCHLD\n");
                kill(pid, SIGCHLD);
            }
            broj = rand() % 10;
        }
        break;
    }
}