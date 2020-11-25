#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <errno.h>
#include <unistd.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array; 
};


int main()
{
	key_t kljuc = ftok("./osoba.c", 'a');
	
	int semid = semget(kljuc, 3, 0666 | IPC_CREAT); //potrebna su nam 3 sem
	
	int shmid = shmget(kljuc, sizeof(int), 0666 | IPC_CREAT);
	
	
	//koristicemo deljenu memoriju kao kasicuuuu
	int *kasica = (int*)shmat(shmid, NULL, 0);
	
	
	
	if(semid == -1)
	{
		if(errno ==EEXIST)
		{
			semid = semget(kljuc, 3, 0);
		}
	}
	else
	{
		union semun init_sem;
		
		init_sem.array = (unsigned short*)malloc(3 *sizeof(unsigned short));
		
		init_sem.array[0] = 1; //sinhonizacija osoba
		init_sem.array[1] = 0; //javi detetu //dete je semafor 1
		init_sem.array[2] = 0; //javi osobi, dakle osoba je semafor 2
				
		semctl(semid, 0, SETALL, init_sem);
		
		(*kasica) = 0;
	
	}
	
	//pravimo operacije
	struct sembuf P, V;
	
	P.sem_num = 1;
	P.sem_op = -1;
	P.sem_flg = 0;
	
	V.sem_num = 2; //javi osobi
	V.sem_op = 	1;
	V.sem_flg = 0;
	
	while(1)
	{
		semop(semid, &P, 1);
		
		printf("Kasica je napunjena, uzimam sve pary (%d)\n", *kasica);
		
		(*kasica) = 0;
		sleep(5);
		semop(semid, &V, 1);
	}
	return 0;
}

