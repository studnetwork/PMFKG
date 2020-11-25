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

int brojUdaraca=0;

void signal_handler(int sig)
{
	printf("Kraj... udario sam lopticu %d puta\n", brojUdaraca);
	//exit(0);
}

int main()
{
	signal(SIGINT, signal_handler);
	key_t kljuc = ftok("./ping.c", 'a');
	
	int semid = semget(kljuc, 2, 0666 | IPC_CREAT);
	
	if(semid != -1)
	{
		union semun init_operacija;
		
		init_operacija.val = 1;
		semctl(semid, 0, SETVAL, init_operacija);
		
		init_operacija.val = 0;
		semctl(semid, 1, SETVAL, init_operacija);
	}
	else if(errno == EEXIST)
	{
		semid = semget(kljuc, 2, 0);
	}
	else
	{
		printf("Neka druga greska. Izlazim...\n");
		exit(1);
	}
	
	struct sembuf opr_povecaj, opr_smanji;
	
	opr_smanji.sem_num=1;
	opr_smanji.sem_op = -1;
	opr_smanji.sem_flg = 0;
	
	opr_povecaj.sem_num = 0;
	opr_povecaj.sem_op = 1;
	opr_povecaj.sem_flg = 0;
	
	while(1)
	{
		semop(semid, &opr_smanji, 1);
		
		printf("pong\n");
		brojUdaraca++;
		sleep(3);
		
		semop(semid, &opr_povecaj, 1);
		
	}
	return 0;
}
