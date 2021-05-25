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

#define MAX_OSOBA 4
#define N 4

int msg_id,shm_id,sem_id;
int rbr = 1;

struct poruka
{
	long tip_poruke;
	char poruka[100];
	int tmp;
};

union semun 
{
	int val;
	struct semid_ds *buf;
	ushort *array;
};

int main()
{
	struct sembuf opr_p, opr_v;
	struct poruka red_poruka;
	union semun sem;
	
	key_t kljuc;
	pid_t pid;
	int *buff;
	
	kljuc = ftok("./organizator.c",'Z');
	//printf("kljuc = %d\n", kljuc);
	
	msg_id = msgget(kljuc,IPC_CREAT|0666);
	//printf("msg_id = %d\n", msg_id);
	
	int ind;
	int konobar_id; // pivo = 1, sok = 4
	while(1)
	{
		konobar_id = 1;
		
		for(int i = 0; i < MAX_OSOBA; i++)
		{
			msgrcv(msg_id, &red_poruka, sizeof(red_poruka), 1, 0);
			printf("Gost %d\n",red_poruka.tmp);
		}
		
		kljuc = ftok("./gost.c", rbr);
		
		shm_id = shmget(kljuc, sizeof(int)*2, 0644 | IPC_CREAT);
		//printf("shm_id = %d\n", shm_id);
		
		buff = shmat(shm_id, NULL, 0);
		
		buff[0] = 0;
		buff[1] = 0;
		
		shmdt(buff);
		
		sem_id = semget(kljuc, 6, 0644 | IPC_CREAT);
		//printf("sem_id = %d\n", sem_id);
		
		/*
		0 - pivo_gost
		1 - pivo_konobar
		2 - pivo_binarni
		3 - sok_gost
		4 - sok_konobar
		5 - sok_binarni
		*/
		
		sem.val = 0;
		for(int i = 0; i < 6; i=i+3) semctl(sem_id, i, SETVAL, sem);
		
		sem.val = N;
		for(int i = 1; i < 6; i=i+3) semctl(sem_id, i, SETVAL, sem);
		
		sem.val = 1;
		for(int i = 2; i < 6; i=i+3) semctl(sem_id, i, SETVAL, sem);
		
		red_poruka.tip_poruke = 2;
		red_poruka.tmp = rbr;
		
		for(int i = 0; i < MAX_OSOBA; i++)
		{
			msgsnd(msg_id, &red_poruka, sizeof(red_poruka), 0);
		}
		
		pid = fork();
		
		if(pid) 
		{
			konobar_id = 4;
			pid = fork();
		}
		
		switch(pid)
		{
			case 0:
				opr_p.sem_num = konobar_id;
				opr_p.sem_op = -N;
				opr_p.sem_flg = 0;
				
				opr_v.sem_num = konobar_id-1;
				opr_v.sem_op = N;
				opr_v.sem_flg = 0;
				
				while(1)
				{
					if(konobar_id == 1) printf("Proces %d: Proveravam da li za stolom %d ima %d praznih krigli\n",getpid(),rbr,N);
					else printf("Proces %d: Proveravam da li za stolom %d ima %d praznih casa za sok\n",getpid(),rbr,N);
					
					ind = semop(sem_id, &opr_p, 1); // Prazne case(krigle)
					if(ind == -1) break;
					
					if(konobar_id == 1) 
					{
						printf("Proces %d: Prazne su sve krigle za stolom %d\n",getpid(),rbr);
						printf("Proces %d: Uzeo sam krigle sa stola %d i stavio ih na pranje\n",getpid(),rbr); sleep(1);
						printf("Proces %d: Tocim pivo i stavljam pice na sto %d\n",getpid(),rbr); sleep(3);
						printf("Proces %d: Stavio sam %d novih piva na sto %d\n",getpid(),N,rbr);
					}
					
					else
					{
						printf("Proces %d: Prazne su sve case za sok za stolom %d\n",getpid(),rbr);
						printf("Proces %d: Uzeo sam case sa stola %d i stavio ih na pranje\n",getpid(),rbr); sleep(1);
						printf("Proces %d: Tocim sok i stavljam pice na sto %d\n",getpid(),rbr); sleep(3);
						printf("Proces %d: Stavio sam %d novih sokova na sto %d\n",getpid(),N,rbr);
					}
					
					ind = semop(sem_id, &opr_v, 1); // Prazne case(krigle)
					if(ind == -1) break;
				}
				
				break;
				
			case -1:
				printf("Greska pri forkovanju, izlazim...\n");
				exit(1);
				break;
				
			default:
				rbr++;
				break;
		}
	}
	
	return 0;
}
