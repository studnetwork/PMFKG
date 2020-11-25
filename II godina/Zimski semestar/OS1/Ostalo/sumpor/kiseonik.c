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

int main()
{
	key_t kljuc = ftok("./vodonik.c", 87); //generise jedinstveni kljuc
	int id_reda = msgget(kljuc, IPC_CREAT|0666); 
	
	poruka moja_poruka;
	moja_poruka.tip = 3; //kiseonik je 3
	
	while(1)
	{
		msgsnd(id_reda, &moja_poruka, sizeof(moja_poruka), 0);
		printf("Napravio sam O\n");
		sleep(5);
	}
	return 0;
}

