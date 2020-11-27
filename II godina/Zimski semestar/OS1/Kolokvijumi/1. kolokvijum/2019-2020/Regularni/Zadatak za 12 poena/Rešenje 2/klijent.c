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
	
	key_t kljuc= ftok("./zadatak.c", 4);
	int id_reda;
	id_reda = msgget(kljuc, IPC_CREAT|0666);
	
	poruka moja_poruka;

	moja_poruka.tip = 33;
	moja_poruka.pid = getpid();
	
	msgsnd(id_reda, &moja_poruka, sizeof(moja_poruka), 0);
	printf("Poslat zahtev\n");
	
	
	msgrcv(id_reda, &moja_poruka, sizeof(moja_poruka), getpid(), 0);
	printf("Primljen redni broj %d\n",moja_poruka.br);
	int br = moja_poruka.br;
	
	if(br%2==1)
	{
		sleep(rand()%5);
		printf("Unesi poruku\n");
		fgets(moja_poruka.tekst, sizeof(moja_poruka.tekst), stdin);
		moja_poruka.tip = br + 1;
		msgsnd(id_reda, &moja_poruka, sizeof(moja_poruka), 0);
		
		printf("Poslao sam %s\n", moja_poruka.tekst);
		msgrcv(id_reda, &moja_poruka, sizeof(moja_poruka), br, 0);
		printf("Primio sam:%s\n", moja_poruka.tekst);
	}
	else
	{
		sleep(rand()%5);
		
		msgrcv(id_reda, &moja_poruka, sizeof(moja_poruka), br, 0);
		printf("Primio sam:%s\n", moja_poruka.tekst);
		
		printf("Unesi poruku\n");
		fgets(moja_poruka.tekst, sizeof(moja_poruka.tekst), stdin);
		moja_poruka.tip = br - 1;
		msgsnd(id_reda, &moja_poruka, sizeof(moja_poruka), 0);
		printf("Poslao sam %s\n", moja_poruka.tekst);
	}
	
	return 0;
}
