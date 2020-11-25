#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

int brojUdaraca = 0;
void signal_handler(int sig)
{
	printf("Udario sam lopticu %d puta\n", brojUdaraca);
}
int main()
{
	signal(SIGINT, signal_handler);
	
	key_t kljuc = ftok("./ping.c", 'a');
	
	int semid = semget(kljuc, 2, 0666 | IPC_CREAT);
	
	if(semid == -1)
	{
		if(errno == EEXIST)
		{
			semid = semget(kljuc,2, 0);
		}
	}
	else
	{
		union semun init_sem;
		
		init_sem.val = 1;
		semctl(semid, 0, SETVAL, init_sem);
		
		
	}
	
	struct sembuf P, V;
	
	P.sem_num = 0;
	P.sem_op = -1;
	P.sem_flg = 0;
		
	V.sem_num = 1;
	V.sem_op = 	1;
	V.sem_flg = 0;
	
	
	while(1)
	{
		semop(semid, &P, 1);
		//kr
		printf("PING\n");
		//kr
		brojUdaraca++;
		sleep(3);
		semop(semid, &V, 1);
	}
	
	return 0;
}
