#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <string.h>

typedef struct poruka
{
	long tip;
	char tekst[100];
}poruka;

int main()
{
	key_t kljuc = ftok("./proizvodjac.c", 44);
	int id_reda = msgget(kljuc, IPC_CREAT|0666);
	
	
	pid_t prviPotrosac = fork();
	
	if(prviPotrosac == -1)
	{
		perror("GRESKA\n");
	}
	else if(prviPotrosac == 0)
	{
		poruka primljenaPoruka;
		//dete, drugi potrosac
		pid_t drugiPotrosac = fork();
		switch(drugiPotrosac)
		{
			case -1: perror("GRESKA\n"); exit(0);
			case 0: //treci	
		
			default:
			
				while (1) {
		
					msgrcv(id_reda, &primljenaPoruka, sizeof(primljenaPoruka) - sizeof(long), 1, 0);	
					printf("[%d] Potrosac: %s\n", getpid(), primljenaPoruka.tekst);
						}
		}
	}
	else
	{
		//proizvodjac
		//generisi poruku proizvodjacaaaa
		poruka moja_poruka;
		moja_poruka.tip = 1;
		int rbr = 1;
		
		pid_t proizvodjacPid = getpid();
		char ppid[10];
		sprintf(ppid, "%d ", proizvodjacPid); //upisuje u ppid proizvodjac pid kao string
		
		char trenutnaPoruka[10];

		while (1) {
		
			strcpy(moja_poruka.tekst, "Proizvodjac ");
			strcat(moja_poruka.tekst, ppid); //spaja stringove

			sprintf(trenutnaPoruka, "%d", rbr++); //upisuje u trenutnu poruku 
			strcat(moja_poruka.tekst, trenutnaPoruka); //spaja

			msgsnd(id_reda, &moja_poruka, sizeof(moja_poruka), 0);

			sleep(5);
		}
	}
	
	
	return 0;
}
