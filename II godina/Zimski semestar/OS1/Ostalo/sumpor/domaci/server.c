
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

void izmeni(char* tekst)
{
	int i;
	for(i=0; i<strlen(tekst); i++)
	{
		if(tekst[i] > 'Z')
			tekst[i] = tekst[i] - 32;
	}
}

int main()
{
	//red za poryku
	key_t kljuc = ftok("./server.c", 54);
	int id_reda = msgget(kljuc, IPC_CREAT|0666);
	
	poruka moja_poruka;
	
	
	while(1)
	{
		msgrcv(id_reda, &moja_poruka, sizeof(moja_poruka), 1, 0);
		printf("Pristigla poruka je %s\n", moja_poruka.tekst);
		
		//izmeni
		izmeni(moja_poruka.tekst);
		
		moja_poruka.tip=moja_poruka.id;
		msgsnd(id_reda, &moja_poruka, sizeof(moja_poruka), 0);
		printf("Izmenjena poruka: %s\n", moja_poruka.tekst);
	}
	
	
	
	return 0;

}
