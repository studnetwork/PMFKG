#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>
#include <errno.h>

union semun
{
	int val;
	struct semid_ds *buf;
	ushort *array;
};

typedef struct
{
	int broj;
	int znak;
	int z;
}Talon;




int main()
{
	int ind,shmid,semid;
	key_t kljuc;
	struct sembuf P,V;
	union semun operacija;
	Talon *data;
	srand(time(NULL));
	int karta,znak;
	
	kljuc=ftok("MauMau.c",18);
	
	shmid=shmget(kljuc,sizeof(Talon),0666 | IPC_CREAT);
	semid=semget(kljuc,4,0666 | IPC_CREAT | IPC_EXCL);
	
	P.sem_num=3;
	P.sem_op=-1;
	P.sem_flg=0;

	V.sem_op=1;
	V.sem_flg=0;
	
	if(semid != -1)
	{
		operacija.val=1;
		semctl(semid,0,SETVAL,operacija);
		operacija.val=0;
		semctl(semid,1,SETVAL,operacija);
		operacija.val=0;
		semctl(semid,2,SETVAL,operacija);
		operacija.val=0;
		semctl(semid,3,SETVAL,operacija);
	}
	else if(errno == EEXIST)
	{
		semid=semget(kljuc,4,0);
	}
	else
	{
		printf("Desila se greska\n");
		exit(0);
	}
	//Deo za sinhronizaciju
	//Ne moze proces proces 1, 2 i 3 da prodju dalje dok nije generisan data
	semop(semid,&P,1);
	data=shmat(shmid,NULL,0);
	
	
	printf("%d-%d\n",data->broj,data->znak);
	
	int i;
	
	if(data->z==0) i=0;
	else i=2;
	
	P.sem_num=3;
	P.sem_op=-1;
	P.sem_flg=0;
	
	V.sem_num=i;
	V.sem_op=1;
	V.sem_flg=0;
	
	while(1)
	{
		ind=semop(semid,&P,1);
		if(ind==-1) 
			break;
		karta=rand()%14;
		znak=rand()%4;
		if(karta == data->broj || znak==data->znak)
		{
			if(karta == 8)
			{
				//na nenormalno
				if(data->z==0)
				{
					V.sem_num=0;
					data->z=1;
				}
				else if(data->z==1)
				{
					//na normalno
					V.sem_num=3;
					data->z=0;
				}
			}
			printf("Spustio sam kartu %d-%d, na %d-%d\n",karta,znak, data->broj,data->znak);
			data->broj=karta;
			data->znak=znak;
		}
		else
		{
			if(data->z==0)
			{
				V.sem_num=0;
				
			}
			else if(data->z==1)
			{
				V.sem_num=2;
				
			}
			printf("Ne mogu da spustim kartu %d-%d, na %d-%d\n",karta,znak, data->broj,data->znak);
		}
		sleep(3);
		ind=semop(semid,&V,1);
		if(ind==-1) 
			break;
	}
	
	return 0;
}
