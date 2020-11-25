#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

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
	poruka moja_poruka;
	int i;
	
	
	
	while(1)
	{
		msgrcv(id_reda, &moja_poruka, sizeof(moja_poruka), 1, 0);
		
		for(i = 0; i<strlen(moja_poruka.tekst); i++)
		{
			
			char a = toupper(moja_poruka.tekst[i]);
			moja_poruka.tekst[i] = a;
		}
		
		printf("Poruka je %s\n", moja_poruka.tekst);
		
		
		
		moja_poruka.tip = moja_poruka.id;
		
		
		msgsnd(id_reda, &moja_poruka, sizeof(moja_poruka), 0);
		
	
		
	}
	
	return 0;
}
