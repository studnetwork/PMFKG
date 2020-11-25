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
int id;
int rbr;
void signal_handler(int SIG)
{
	klijent.tip_poruke=rbr;
	strcpy(klijent.tekst,"odjava\n");
	msgsnd(id,&klijent,sizeof(klijent),0);
	exit(0);
}

int main()
{
	key_t key;
	signal(SIGINT,signal_handler);
	
	key=ftok("./server.c",20);
	id=msgget(key,IPC_CREAT | 0666);
	
	klijent.tip_poruke=20;
	klijent.id=id;
	msgsnd(id,&klijent,sizeof(klijent),0);
	
	msgrcv(id,&klijent,sizeof(klijent),21,0);
	
	rbr=klijent.id;
	printf("MOJ REDNI BROJ JE %d\n",rbr);
	while(1)
	{
		if(rbr == 1)
		{
			//saljem poruku server pa onda primam od servera
			printf("UNESI PORUKU\n");
			klijent.tip_poruke=1;
			klijent.id=rbr;
			fgets(klijent.tekst,sizeof(klijent.tekst),stdin);
			msgsnd(id,&klijent,sizeof(klijent),0);
			msgrcv(id,&klijent,sizeof(klijent),1,0);
			printf("Primljena poruka je : %s\n",klijent.tekst);
			if(strcmp(klijent.tekst,"odjava\n")==0)
			{
				printf("ODJAVLJUJEM SE!!");
				exit(0);
			}
		}
		else
		{
			//prvo primam poruku od servera pa saljem serveru
			msgrcv(id,&klijent,sizeof(klijent),2,0);
			printf("Primljena poruka je : %s\n",klijent.tekst);
			if(strcmp(klijent.tekst,"odjava\n")==0)
			{
				printf("ODJAVLJUJEM SE!!");
				exit(0);
			}
			else
			{
				printf("UNESI PORUKU\n");
				klijent.tip_poruke=2;
				klijent.id=rbr;
				fgets(klijent.tekst,sizeof(klijent.tekst),stdin);
				msgsnd(id,&klijent,sizeof(klijent),0);
			}
		}
		
		
	}
	
	return 0;
}
