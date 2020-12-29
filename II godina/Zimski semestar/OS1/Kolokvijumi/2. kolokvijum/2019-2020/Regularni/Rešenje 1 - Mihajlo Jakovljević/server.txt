#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include<time.h>

#define MAX_IGRACA 4
#define MAX_IGARA 100

int msg_id, shm_arr[MAX_IGARA], sem_arr[MAX_IGARA], pid_arr[MAX_IGARA];
int kljuc_arg = 30, igra_ind = 0, pid_ind = 0;

struct poruka
{
	long tip_poruke;
	char poruka[20];
	int kljuc_arg;
};

union semun
{
	int val;
	struct semid_ds *buf;
	ushort *array;
};

void sig_handler()
{
	printf("Proces server prekinut komandom CTRL+C, brise sve i zavrsava...\n");
	
	msgctl(msg_id,IPC_RMID,NULL);
	for(int i = 0; i < igra_ind; i++)
	{
		for(int j = 0; j < MAX_IGRACA; j++) semctl(sem_arr[i],j,IPC_RMID,NULL);
		shmctl(shm_arr[i],IPC_RMID,NULL);
	}
	
	exit(0);
}

int main()
{
	struct poruka red_poruka;
	union semun sem;
	
	key_t kljuc;
	pid_t pid = 1;
	int sem_id,shm_id;
	int *buff;
	
	kljuc = ftok("./server.c",'A');
	printf("kljuc = %d\n",kljuc);
	
	msg_id = msgget(kljuc,IPC_CREAT|0666);
	printf("msg_id = %d\n",msg_id);
	
	srand(time(NULL));
	
	while(1)
	{
		for(int i = 0; i < MAX_IGRACA; i++)
		{
			msgrcv(msg_id,&red_poruka,sizeof(red_poruka),1,0);
			printf("Prijavljen igrac %d\n",i+1);
		}
		
		if(pid) pid = fork();
		
		switch(pid)
		{
			case 0:
				red_poruka.kljuc_arg = kljuc_arg;
				red_poruka.tip_poruke = 2;
				
				kljuc = ftok("./igrac.c",kljuc_arg);
				printf("kljuc = %d\n",kljuc);
				
				shm_id = shmget(kljuc,sizeof(int)*3,0644|IPC_CREAT);
				printf("shm_id = %d\n",shm_id);
				
				sem_id = semget(kljuc,MAX_IGRACA,0644|IPC_CREAT);
				printf("sem_id = %d\n",kljuc);
				
				shm_arr[igra_ind] = shm_id;
				sem_arr[igra_ind] = sem_id;
				igra_ind++;
				
				buff = shmat(shm_id,NULL,0); // Kriticni region
				
				do{
					buff[0] = rand()%15; // Vrednost
					buff[1] = rand()%5; // Znak
				} while(buff[0] == 0 || buff[1] == 0);
				
				buff[2] = 1; // Smer
				
				printf("-----Talon%d-----\nVrednost = %d\nZnak = %d\nSmer = %d\n---------------\n",kljuc_arg-30,buff[0],buff[1],buff[2]);
				
				shmdt(buff); // Kriticni region
				
				for(int i = 0; i < MAX_IGRACA; i++)
				{
					if(i == 0) sem.val = 1;
					else sem.val = 0;
					
					semctl(sem_id,i,SETVAL,sem);
				}
				
				
				char tmp[] = "0";
				for(int i = 0; i < MAX_IGRACA; i++)
				{
					tmp[0] = tmp[0]+1;
					strcpy(red_poruka.poruka,tmp);
					
					msgsnd(msg_id,&red_poruka,sizeof(red_poruka),IPC_NOWAIT);
				}
				
				printf("Dete(pid = %d) je zavrsilo...\n", getpid());
				exit(0);
				break;
			
			case -1:
				printf("Greska pri forkovanju!\n");
				exit(1);
				break;
				
			default:
				signal(SIGINT,sig_handler);
				kljuc_arg++;
				break;
		}
		
	}
	
	return 0;
}
