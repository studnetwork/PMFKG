#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

typedef struct poruka{
		long tip_poruke;
		pid_t pid;
		int k;
		char tekst[50];
	}poruka;

int main()
{
	key_t key;
	int id;
	pid_t pid;
	poruka igrac;
	int k;
	
	key=ftok("./tabla.c",20);
	id=msgget(key,IPC_CREAT|0666);
	pid=getpid();
	
	printf("IGRAC 4 : Prijavljujem se na tablu:\n");
	igrac.tip_poruke=1;
	igrac.pid=pid;
	msgsnd(id,&igrac,sizeof(igrac),0);
	while(1)
	{
		printf("IGRAC 4: Cekam potvrdu !!\n");
		msgrcv(id,&igrac,sizeof(igrac),pid,0);
		if(strcmp(igrac.tekst,"igraj") == 0)
		{
			printf("IGRAC 4 : Mogu da odigram potez!! Unosim jedan broj :\t");
			scanf("%d",&k);
			printf("IGRAC 4 : Saljem odigrani potez cekam odgovor o potezu!!\n");
			igrac.k=k;
			igrac.tip_poruke=pid;
			msgsnd(id,&igrac,sizeof(igrac),0);	
		}
		else
		if(strcmp(igrac.tekst,"pojeden") == 0)
			{
				printf("IGRAC 4 : Ja sam pojeden zavrsavam rad!!\n");
				exit(0);
			}
		else
		{
			printf("IGRAC 4 : Stigao sam do kraja!!\n");
			exit(0);
		}
	}	
	return 0;
}
