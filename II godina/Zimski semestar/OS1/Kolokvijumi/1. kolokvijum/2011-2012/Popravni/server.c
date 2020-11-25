#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>

typedef struct poruka {
	long tip_poruke;
	int iznos;
	char tekst[50];
	}poruka;

int main(int argc, char *argv[])
{
	key_t key;
	int id;
	poruka server;
	long racun=0;
	key=ftok("./server.c",20);
	id=msgget(key,IPC_CREAT | 0666);
	int s1=0,s2=0;
	while(1)
	{
		s1=msgrcv(id,&server,sizeof(server),1,IPC_NOWAIT);
		s2=msgrcv(id,&server,sizeof(server),2,IPC_NOWAIT);
		if(s1 != -1 || s2 != -1)
		{
			if(server.tip_poruke == 1)
			{
				//uplata na racun;
				racun+=server.iznos;
				printf("Izvrsena je uplata na racun, trenutno stanje na racunu je %ld \n",racun);
			}
			else
			{
				//skidanje sa racuna;
				int e = 0;
				e= racun - server.iznos;
				if(e >= 0)
				{
					//moguce je skinuti novac
					racun-=server.iznos;
					strcpy(server.tekst,"izvrsena isplata");
					server.tip_poruke=3;
					msgsnd(id,&server,sizeof(server),0);
					printf("Novac je skinut sa racuna, trenutno stanje na racunu je %ld \n",racun);
					
				}
				else
				{
					strcpy(server.tekst,"nema dovoljno sredstava");
					server.tip_poruke=3;
					msgsnd(id,&server,sizeof(server),0);
					printf("Nije moguce skinuti novac sa racuna, trenutno stanje na racunu je %ld \n",racun);
				}
			}
		}
	}
	
	
	return 0;
}
