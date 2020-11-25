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


void signal_handler(int sig)
{
	printf("PRIMLJEN SIGNAL SIGINT\n");
	server.tip_poruke=1;
	strcpy(server.tekst,"KRAJ");
	msgsnd(id,&server,sizeof(server),0);
	sleep(5);
	msgctl(id, IPC_RMID, NULL);
	exit(0);
}

	
int main()
{
	key_t key;
	
	signal(SIGINT,signal_handler);
	key=ftok("./server.c",15);
	id=msgget(key,IPC_CREAT|0666);
	
	int i,N;
	N=4;
	for(i=0;i<N;i++)
	{
		printf("Primam poruke da dodelim id\n");
		msgrcv(id,&server,sizeof(server),21,0);
		server.tip_poruke=20;
		server.id=i+2;
		msgsnd(id,&server,sizeof(server),0);
	}
	printf("Pocinjem slanje poruke\n");
	while(1)
	{
		fgets(server.tekst,sizeof(server.tekst),stdin);
		server.tip_poruke=1;
		msgsnd(id,&server,sizeof(server),0);
		printf("Cekam poruku da se vrati\n");
		msgrcv(id,&server,sizeof(server),N+1,0);
		printf("%s\n",server.tekst);
		if(strcmp(server.tekst,"KRAJ")==0)
			break;
			
	}
	
	
	msgctl(id, IPC_RMID, NULL);
}	

