#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>

typedef struct poruka {
	long tip_poruke;
	int iznos;
	char tekst[50];
	}poruka;

int main(int argc, char *argv[])
{
	key_t key;
	int id;
	poruka klijent;
	
	key=ftok("./server.c",20);
	id=msgget(key,IPC_CREAT | 0666);
	
	klijent.tip_poruke=(long)(*argv[1])-48;
//	printf("Primljeni argument je %ld\n",klijent.tip_poruke);
	
	int iz;
	srand(time(NULL));
	iz=rand() % 10000;
	//printf("%d\n",iz);
	iz++;
	klijent.iznos=iz;
	msgsnd(id,&klijent,sizeof(klijent),0);
	
	if(klijent.tip_poruke == 2)
	{
		//primam poruku posto sam zahtevao skidanje novca sa racuna
		msgrcv(id,&klijent,sizeof(klijent),3,0);
		printf("KLIJENT: %s\n",klijent.tekst);
	}
	
	return 0;
}
