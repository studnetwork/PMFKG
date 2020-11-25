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
	
	int semid = semget(kljuc, 4, 0666 | IPC_CREAT);
	
	if(semid==-1)
	{
		if(errno == EEXIST)
		{
			semid = semget(kljuc, 4, 0);
		}
		else
		{
			proveri(semid);
		}
	}
	else
	{
		union semun init_sem;
		init_sem.array=(unsigned short*)malloc(4 * sizeof(unsigned short));
		
		init_sem.array[0]=2;
		init_sem.array[1]=0;
		init_sem.array[2]=0;
		init_sem.array[3]=0;
		
		int rv = semctl(semid, 0, SETALL, init_sem);
		proveri(rv);
		
		
	}
	
	struct sembuf P, V;
	
	P.sem_num = 2;
	P.sem_op = -1;
	P.sem_flg = 0;
	
	V.sem_num = 3;
	V.sem_op = 1;
	V.sem_flg = 0;
	
	
	Poruka poruka;
	poruka.tip = 3;
	
	
	while(1)
	{
		
		
		for(int i=0; i<4; i++)
			semop(semid, &P, 1);
		
		sleep(5);
		for(int i=0; i<4; i++)
		{
			msgsnd(id_reda, &poruka, sizeof(poruka), 0);
		}
	
		
		semop(semid, &V, 1);
		semop(semid, &V, 1);
			
		printf("Napravljen je kisik\n");

	}
	
	
	
	return 0;	
}
