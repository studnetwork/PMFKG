#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <sys/msg.h>


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

void proveri(int povratnaVrednost)
{
	if(povratnaVrednost == -1)
	{
		perror("GRESKA");
		exit(1);
	}
}
	
int main()
{
	key_t kljuc = ftok("./vodonik.c", 32);
	int semid = semget(kljuc, 4, 0666 | IPC_CREAT);
	
	
	int id_reda = msgget(kljuc, 0666 | IPC_CREAT);
	
	
	
	
	if(semid==-1)
	{
		if(errno == EEXIST)
		{
			//semafor postoji
			semget(kljuc, 4, 0);
		}
		else
        {
			proveri(semid);
		}
	}
	else
	{
		union semun init_sem;
		init_sem.array = (unsigned short*)malloc(4 * sizeof(unsigned short));
		
		init_sem.array[0] = 2;
		init_sem.array[1] = 0;
		init_sem.array[2] = 0;
		init_sem.array[3] = 0;
		
		int rv = semctl(semid, 0, SETALL, init_sem);
		proveri(rv);
		
	}
	
	struct sembuf P, V;
	
	P.sem_num = 0;
	P.sem_op = -1;
	P.sem_flg = 0;
	
	
	P.sem_num = 1;
	P.sem_op = 1;
	P.sem_flg = 0;
	
	
	Poruka poruka;
	poruka.tip = 1;
	
	
	while(1)
	{
		for(int i=0; i<2; i++)
			semop(semid, &P, 1);
		
		printf("PRAVIM ATOM\n");
		sleep(5);
		//posalji poruku
		for(int i=0; i<2; i++)
		{
			msgsnd(id_reda, &poruka, sizeof(poruka), 0);
		}
		
		semop(semid, &V, 1);
		
		printf("Napravljen je jedan vodonik\n");
	}
		
	return 0;
	
}
