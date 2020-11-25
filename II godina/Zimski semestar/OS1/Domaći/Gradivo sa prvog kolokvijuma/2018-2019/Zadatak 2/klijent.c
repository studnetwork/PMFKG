#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <string.h>

typedef struct poruka
{
	long tip;
	char tekst[100];
	int id;
	
}poruka;

int main()
{
	key_t kljuc = ftok("./server.c", 65);
	int id_reda=msgget(kljuc, IPC_CREAT|0666);
	poruka moja_poruka, primljena_poruka;
	
	moja_poruka.tip=1;
	moja_poruka.id = getpid();
	
	printf("Unesi poruku:\n");
	fgets(moja_poruka.tekst, sizeof(moja_poruka.tekst), stdin);
	while(1)
	{
	
		
		if(strcmp(moja_poruka.tekst, "dosta\n")==0)
		{
			return 0;
		}
		
		
		msgsnd(id_reda, &moja_poruka, sizeof(moja_poruka), 0);
		sleep(5);
		
		msgrcv(id_reda, &primljena_poruka, sizeof(primljena_poruka), getpid(), 0);
		
		printf("Primljena poruka od servera: %s\n", primljena_poruka.tekst);
		printf("Unesi poruku:\n");
		fgets(moja_poruka.tekst, sizeof(moja_poruka.tekst), stdin);
		
		
		
	}
	
	return 0;
}
