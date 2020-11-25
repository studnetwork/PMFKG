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
	
	int i;
	int brojac = 0;
	
	while(1)
	{
		for(i=0; i<2; i++)
		{
			msgrcv(id_reda, &moja_poruka, sizeof(moja_poruka), 1, 0);
		}
		
		msgrcv(id_reda, &moja_poruka, sizeof(moja_poruka), 2, 0);
		
		for(i = 0; i<4; i++)
		{
			msgrcv(id_reda, &moja_poruka, sizeof(moja_poruka), 3, 0);
		}
		
		printf("Napravljeno je %d molekula H2SO4\n", ++brojac);
	}
	return 0;
}

