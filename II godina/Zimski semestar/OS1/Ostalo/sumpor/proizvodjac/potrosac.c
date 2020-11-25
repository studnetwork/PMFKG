#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

typedef struct poruka
{
	long tip;
	int pid;
	char tekst[100];
	int rbr;
}poruka;
int main()
{
	key_t kljuc=ftok("./potrosac.c", 34);
	int id_reda = msgget(kljuc, IPC_CREAT|0666);
	
	poruka moja_poruka;

	int pid = fork();
	
	while(1)
	{
		switch(pid)
		{
			case -1:
				perror("Greska\n");
				exit(0);
			case 0: //dete
				msgrcv(id_reda, &moja_poruka, sizeof(moja_poruka), 1, 0);
				printf("p2:\n");
				printf("%s %d %d\n", moja_poruka.tekst, moja_poruka.pid, moja_poruka.rbr);
				
			default: //roditelj
				msgrcv(id_reda, &moja_poruka, sizeof(moja_poruka), 1, 0);
				printf("P1:\n");
				printf("%s %d %d\n", moja_poruka.tekst, moja_poruka.pid, moja_poruka.rbr);
			
				
		}
	}
}

