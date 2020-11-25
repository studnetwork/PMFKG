#include <sys/types.h> //msg
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h> //msg
#include <unistd.h> //fork
#include <signal.h>

typedef struct poruka
{
	long tip;
	
}poruka;

poruka moja_poruka;


int main()
{
	key_t kljuc = ftok("./vodonik.c", 87); //generise jedinstveni kljuc
	int id_reda = msgget(kljuc, IPC_CREAT|0666); 
	
	
	moja_poruka.tip = 1; //vodonik je 1
	
	
	
	while(1)
	{
		msgsnd(id_reda, &moja_poruka, sizeof(moja_poruka), 0);
		printf("Napravio sam H\n");
		sleep(5);
	}
	return 0;
}
