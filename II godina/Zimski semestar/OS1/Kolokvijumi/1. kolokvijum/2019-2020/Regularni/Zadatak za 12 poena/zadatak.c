#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

typedef struct poruka
{
	long tip;
	char tekst[100];
	long pid;
	int br;
}poruka;

int main()
{
	int n, i;
	printf("Unesi n\n");
	scanf("%d", &n);
	
	
	key_t kljuc= ftok("./zadatak.c", 4);
	int id_reda;
	id_reda = msgget(kljuc, IPC_CREAT|0666);
	
	poruka moja_poruka;

	for(i=0; i<n; i++)
	{
		sleep(rand()%5);
		msgrcv(id_reda, &moja_poruka, sizeof(moja_poruka), 33, 0);
		printf("Primljen zahtev\n");
		moja_poruka.tip =moja_poruka.pid;
		moja_poruka.br = i+1;
		msgsnd(id_reda, &moja_poruka, sizeof(moja_poruka), 0);
	}
	return 0;
}
