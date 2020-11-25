#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <sys/sem.h>
#include <time.h>
#include <sys/shm.h>

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	
};



enum znak
{
	KARO = 0,
	PIK,
	TREF,
	HERC
};

typedef struct 
{
	int broj;
	enum znak z;
}Karta;
int main()
{
	key_t kljuc=ftok("./igrac1.c", 32);
	
	
	key_t kljuc2=ftok("./igrac1.c", 33);
	
	int semid = semget(kljuc, 4, 0666 | IPC_CREAT);
	
	
	int shmid = shmget(kljuc, sizeof(int), 0666 | IPC_CREAT);
	
	
	int shmid2 = shmget(kljuc2, sizeof(int), 0666 | IPC_CREAT);
	
	Karta *talon = (Karta*)shmat(shmid, NULL, 0);
	int *smer = (int*)shmat(shmid2, NULL, 0);
	
	(*smer) = 1; //na pocetku je ispravan smer

	
	if(semid==-1)
	{
		if(errno == EEXIST)
		{
			semid = semget(kljuc, 4, 0);
		}
		
	}
	else
	{
		union semun init_sem;
		init_sem.array=(unsigned short*)malloc(4 * sizeof(unsigned short));
		
		init_sem.array[0]=1;
		init_sem.array[1]=0;
		init_sem.array[2]=0;
		init_sem.array[3]=0;
		
		semctl(semid, 0, SETALL, init_sem);
		
		
	}
	
	
	struct sembuf P, V;
	
	
	int i;
	
	srand(getpid());
	
	for(i=0; i<6; i++)
	{
		Karta izvucena = (*talon);
		if(izvucena.broj==8 && (*smer)==1)
		{
			(*smer) = 0;
		}
		else
		if(izvucena.broj == 8 && (*smer)==0 )
		{
			(*smer) = 1;
		}
		
		if((*smer) == 1)
		{
				P.sem_num = 3;
				P.sem_op = -1;
				P.sem_flg = 0;
				
				V.sem_num = 0;
				V.sem_op = 1;
				V.sem_flg = 0;
				
		}
		else
		{
				P.sem_num = 3;
				P.sem_op = -1;
				P.sem_flg = 0;
				
				V.sem_num = 2;
				V.sem_op = 1;
				V.sem_flg = 0;
		}
		
			semop(semid, &P, 1);
		
		
		
		
		//generisi kartu
		
		Karta karta;
		karta.broj = rand() % 14 + 1;
		
		karta.z = rand() % 4;
		
		if(izvucena.broj == karta.broj || izvucena.z == karta.z)
		{
			
		switch(karta.z)
		{
			case 0:
			printf("Moja karta je: %d karo\n", karta.broj);
			break;
			case 1:
			printf("Moja karta je: %d pik\n", karta.broj);
			break;
			case 2:
			printf("Moja karta je: %d tref\n", karta.broj);
			break;
			case 3:
			printf("Moja karta je: %d herc\n", karta.broj);
			break;
			
		}
			(*talon) = karta;
		}
		else
		{
			printf("Nemam adekvatnu kartu\n");
		}
		
		sleep(2);
		semop(semid, &V, 1);
		
	}
	return 0;
}

