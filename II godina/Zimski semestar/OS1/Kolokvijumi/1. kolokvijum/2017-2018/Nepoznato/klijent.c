#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <signal.h>

typedef struct poruka{
	long tip_poruke;
	char tekst[50];
	int id;
}poruka;



poruka klijent;
int IDK=0;
int id;

void signal_handler(int sig)
{
	printf("PRIMLJEN SIGNAL SIGINT\n");
	
	klijent.tip_poruke=IDK;
	strcpy(klijent.tekst,"KRAJ");
	msgsnd(id,&klijent,sizeof(klijent),0);
	msgctl(id, IPC_RMID, NULL);
	exit(0);
}

int main()
{
	key_t key;
	

	
	key=ftok("./server.c",15);
	id=msgget(key,IPC_CREAT|0666);
	
	klijent.tip_poruke=21;
	
	msgsnd(id,&klijent,sizeof(klijent),0);
	
	printf("Poslao sam poruku cekam da dobijem id\n");
	
	msgrcv(id,&klijent,sizeof(klijent),20,0);

	IDK=klijent.tip_poruke=klijent.id;
	
	printf("Primam poruke  moj id je %ld:\n",klijent.tip_poruke);
	signal(SIGINT,signal_handler);
	while(1)
	{
		int q=IDK - 1;
		msgrcv(id,&klijent,sizeof(klijent), q ,0);
		printf("Primljena poruka ima id %d - %s: \n" ,klijent.id,klijent.tekst);
		if(strcmp(klijent.tekst,"KRAJ")==0)
			{
				printf("Primljen je kraj\n");
				klijent.tip_poruke=IDK;
				msgsnd(id,&klijent,sizeof(klijent),0);
				break;
			}
		else
		{
			printf("Primljena poruka nije kraj\n");
			int d=strlen(klijent.tekst) - 1 ;
			int k=rand() % d;
			
			int s=rand() % 26;
			
			klijent.tekst[k]=s+64;
			printf("DODAJEM SLOVO %c\n",klijent.tekst[k]);
			printf("Saljem poruku : %s\n",klijent.tekst);	
			klijent.tip_poruke=IDK;
			msgsnd(id,&klijent,sizeof(klijent),0);
		}
	}
	
	
}	
