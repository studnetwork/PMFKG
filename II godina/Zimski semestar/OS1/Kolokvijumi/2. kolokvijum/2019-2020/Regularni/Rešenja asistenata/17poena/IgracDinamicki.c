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

int semid;

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

void signal_handler(int id)
{
    printf("Deleting semaphores\n");
    int i;
    for(i=0; i<4; i++)
    {
        semctl(semid, i, IPC_RMID);
    }
    exit(0);
}

int main()
{
	int ind,shmid,i;
	key_t kljuc;
	struct sembuf P,V;
	union semun operacija;
	Talon *data;
	srand(time(NULL));
	signal(SIGINT, signal_handler);
	int karta,znak, id;
	scanf("%d", &id);
	kljuc=ftok("MauMau.c",18);
	
	shmid=shmget(kljuc,sizeof(Talon),0666 | IPC_CREAT);
	semid=semget(kljuc,4,0666 | IPC_CREAT | IPC_EXCL);
	
	P.sem_num=id;
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

	data=shmat(shmid,NULL,0);
	if(id==0)
	{
		karta=rand()%14;
		znak=rand()%4;
		data->broj=karta;
		data->znak=znak;
		data->z=0;
		//Deo za sinhronizaciju
		V.sem_num = 1;
		semop(semid,&V,1);
		V.sem_num = 2;
		semop(semid,&V,1);
		V.sem_num = 3;
		semop(semid,&V,1);
	}
	else
	{
		//Deo za sinhronizaciju
		//Ne moze proces proces 1, 2 i 3 da prodju dalje dok nije generisan data
		ind=semop(semid,&P,1);
	}
	

	printf("%d-%d\n",data->broj,data->znak);
	
	if(karta == 8)
	{
		data->z=1;
	}
	else 
		data->z=0;

	if(data->z==0) 
	{
		if(id==3)
			i=V.sem_num=0;
		else
			i=V.sem_num=id+1;
	}
	else 
	{
		if(id==0)
			i=V.sem_num=3;
		else
			i=V.sem_num=id-1;
	}
	
	
	P.sem_num=id;
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
				if(data->z==0)
				{
					if(id-1<0)
						V.sem_num=3;
					else
						V.sem_num=id-1;
					data->z=1;
				}
				else if(data->z==1)
				{
					if(id+1>3)
						V.sem_num=0;
					else
						V.sem_num=id+1;
					
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
				if(id+1>3)
					V.sem_num=0;
				else
					V.sem_num=id+1;
				
			}
			else if(data->z==1)
			{
				
				if(id-1<0)
					V.sem_num=3;
				else
					V.sem_num=id-1;
			}
			printf("Ne mogu da spustim kartu %d-%d, na %d-%d\n",karta,znak, data->broj,data->znak);
		}
		
		sleep(5);
		ind=semop(semid,&V,1);
		if(ind==-1) 
			break;
	}
	
	return 0;
}
