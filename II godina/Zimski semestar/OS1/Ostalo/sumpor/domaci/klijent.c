#include <sys/types.h> 
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h> 
#include <unistd.h> 
#include <signal.h>
#include <string.h>

typedef struct poruka
{
	long tip;
	char tekst[100];
	int id;
	
}poruka;

int main()
{
	//red za poryku
	key_t kljuc = ftok("./server.c", 54);
	int id_reda = msgget(kljuc, IPC_CREAT|0666);
	poruka moja_poruka;

	printf("Unesi poruku:\n");
	fgets(moja_poruka.tekst, sizeof(moja_poruka.tekst), stdin);
	moja_poruka.tip= 1;
	moja_poruka.id=getpid();
	
	while(1)
	{
		msgsnd(id_reda, &moja_poruka, sizeof(moja_poruka), 0);
		
		
		poruka izmenjena;
		
		msgrcv(id_reda, &izmenjena, sizeof(izmenjena), getpid(), 0);
		printf("Izmenjena poruka: %s\n", izmenjena.tekst);

		sleep(5);
		printf("Unesi poruku:\n");
		
		fgets(moja_poruka.tekst, sizeof(moja_poruka.tekst), stdin);
		
	}
	return 0;
}
