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
#include <time.h>

#define MAX_IGRACA 4
#define MAX_IGARA 100
#define MAX_IZVLACENJA 6

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

int main()
{
	srand(time(NULL));
	
	struct sembuf opr_p,opr_v;
	struct poruka red_poruka;
	union semun sem;
	
	key_t kljuc;
	int ind, id, kljuc_arg;
	int msg_id,shm_id,sem_id;
	int *buff;
	
	kljuc = ftok("./server.c",'A');
	printf("kljuc = %d\n",kljuc);
	
	msg_id = msgget(kljuc,IPC_CREAT|0666);
	printf("msg_id = %d\n",msg_id);
	
	red_poruka.tip_poruke = 1;
	msgsnd(msg_id,&red_poruka,sizeof(red_poruka),0);
	
	msgrcv(msg_id,&red_poruka,sizeof(red_poruka),2,0);
	
	id = red_poruka.poruka[0] -'1';
	printf("id igraca = %d\n", id);
	
	kljuc_arg = red_poruka.kljuc_arg;
	
	kljuc = ftok("./igrac.c",kljuc_arg);
	printf("kljuc = %d\n",kljuc);
	
	shm_id = shmget(kljuc,sizeof(int)*3,0);
	printf("shm_id = %d\n",shm_id);
	
	buff = shmat(shm_id,NULL,0);
	
	sem_id = semget(kljuc,MAX_IGRACA,0);
	printf("sem_id = %d\n",kljuc);
	
	opr_p.sem_num = id;
	opr_p.sem_op = -1;
	opr_p.sem_flg = 0;
	
	opr_v.sem_op = 1;
	opr_v.sem_flg = 0;
	
	int vrednost,znak,flag = 0;
	
	while(flag < MAX_IZVLACENJA)
	{
		ind = semop(sem_id,&opr_p,1); // Kriticni region
		if(ind == -1) break;
		
		do{
			vrednost = rand()%15;
			znak = rand()%5;
		} while(vrednost == 0 || znak == 0);
		
		printf("\n-----Karta%d-----\nVrednost = %d\nZnak = %d\n----------------\n",flag+1,vrednost,znak);
		
		printf("\n-----Talon(pre)-----\nVrednost = %d\nZnak = %d\nSmer = %d\n--------------------\n",buff[0],buff[1],buff[2]);
		
		if(vrednost == buff[0] || znak == buff[1])
		{
			buff[0] = vrednost;
			buff[1] = znak;
			
			if(vrednost == 8)
			{
				if(buff[2]) buff[2] = 0;
				else buff[2] = 1;
			}
			
			printf("\n-----Talon(pos)-----\nVrednost = %d\nZnak = %d\nSmer = %d\n--------------------\n",buff[0],buff[1],buff[2]);
		}
		
		else printf("\nNemam adekvatnu kartu!\n\n");
		
		switch(buff[2])
		{
			case 0:
				if(id == 0) opr_v.sem_num = 3;
				else opr_v.sem_num = id-1;
				break;
				
			case 1:
				if(id == 3) opr_v.sem_num = 0;
				else opr_v.sem_num = id+1;
				break;
		}
		
		flag++;
		sleep(10);
		
		ind = semop(sem_id,&opr_v,1); // Kriticni region
		if(ind == -1) break;	
	}
	
	shmdt(buff);
	
	printf("Izvukao sam 6 karata, zavrsavam...\n");
	
	return 0;
}
