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

poruka server;
int id;
void signal_handler(int SIG)
{
	server.tip_poruke=1;
	strcpy(server.tekst,"odjava\n");
	msgsnd(id,&server,sizeof(server),0);
	
	server.tip_poruke=2;
	msgsnd(id,&server,sizeof(server),0);
	sleep(5);
	msgctl(id,IPC_RMID,NULL);
	exit(0);
}

int main()
{
	key_t key;
	
	signal(SIGINT,signal_handler);
	
	key=ftok("./server.c",20);
	id=msgget(key,IPC_CREAT | 0666);
	
	int i;
	for(i=1;i<=2;i++)
	{
		msgrcv(id,&server,sizeof(server),20,0);
		server.tip_poruke=21;
		server.id=i;
		msgsnd(id,&server,sizeof(server),0);
	}
	while(1)
	{
		printf("PRIJEM\n");
		msgrcv(id,&server,sizeof(server),1,0);
		printf("Primljena poruka je : %s primljeno sa %ld\n",server.tekst,server.tip_poruke);
		if(strcmp(server.tekst,"odjava\n")==0)
			{
				printf("ODJAVLJUJEM SE!!");
				
				sleep(5);
				msgctl(id,IPC_RMID,NULL);
				exit(0);
			}
			
		server.tip_poruke=2;
		msgsnd(id,&server,sizeof(server),0);
		msgrcv(id,&server,sizeof(server),2,0);
		printf("Primljena poruka je : %s primljeno sa %ld\n",server.tekst,server.tip_poruke);
		if(strcmp(server.tekst,"odjava\n")==0)
			{
				printf("ODJAVLJUJEM SE!!");
				
				sleep(5);
				msgctl(id,IPC_RMID,NULL);
				exit(0);
			}
			
		server.tip_poruke=1;
		msgsnd(id,&server,sizeof(server),0);
		
		sleep(3);
	}
	
	return 0;
}
