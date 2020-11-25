#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <errno.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/msg.h>

void proveri(int povratnaVrednost)
{
	if(povratnaVrednost== -1)
	{
		perror("GRESKA");
		exit(1);
	}
}

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	
};

typedef struct 
{
	long tip;
	
}Poruka;
int main()
{
	key_t kljuc=ftok("./vodonik.c", 32);
	proveri(kljuc);
	
	int id_reda = msgget(kljuc, 0666 | IPC_CREAT);
	
	
	int brojMolekula = 0;
	
	Poruka poruka;
	
	while(1)
	{
		
		for(int i = 0; i<2; i++)
		{
			msgrcv(id_reda, &poruka, sizeof(poruka), 1, 0);
		}
		
	
		msgrcv(id_reda, &poruka, sizeof(poruka), 2, 0);
		
		for(int i = 0; i<4; i++)
		{
			msgrcv(id_reda, &poruka, sizeof(poruka), 3, 0);
		}
		
		
		printf("Napravljen je molekul: %d\n", ++brojMolekula);

		
	}
	
	
	
	return 0;	
}

