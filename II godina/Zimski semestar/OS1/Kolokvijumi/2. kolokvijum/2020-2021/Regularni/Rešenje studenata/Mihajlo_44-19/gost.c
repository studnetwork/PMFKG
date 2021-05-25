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

int msg_id,shm_id,sem_id;

struct poruka
{
	long tip_poruke;
	char poruka[100];
	int tmp;
};

int main()
{
	srand(time(NULL));
	
	struct sembuf opr_p, opr_v;
	struct poruka red_poruka;
	key_t kljuc;
	pid_t pid;
	int flag,pice_id,rbr,gost_id;
	int *buff; // 0 = br_piva, 1 = br_sokova
	
	kljuc = ftok("./organizator.c",'Z');
	//printf("kljuc = %d\n", kljuc);
	
	msg_id = msgget(kljuc,IPC_CREAT|0666);
	//printf("msg_id = %d\n", msg_id);
	
	pid = getpid();
	
	red_poruka.tip_poruke = 1;
	red_poruka.tmp = pid;
	
	msgsnd(msg_id, &red_poruka, sizeof(red_poruka), 0);
	
	printf("Proces %d: Cekam da se pronadje sto\n",pid);
	
	msgrcv(msg_id, &red_poruka, sizeof(red_poruka), 2, 0);
	rbr = red_poruka.tmp;
	
	printf("Proces %d: Dobio sam sto sa brojem %d\n",pid,rbr);
	
	kljuc = ftok("./gost.c", rbr);

	shm_id = shmget(kljuc, sizeof(int)*2, 0);
	//printf("shm_id = %d\n", shm_id);
	
	buff = shmat(shm_id, NULL, 0);
	
	sem_id = semget(kljuc, 6, 0);
	//printf("sem_id = %d\n", sem_id);
	
	int ind;
	
	while(1)
	{
		flag = rand()%2;
		if(flag) pice_id = 0;
		else pice_id = 3;
		
		if(!pice_id) printf("Proces %d: Proveravam da li na stolu ima piva\n",pid);
		else printf("Proces %d: Proveravam da li na stolu ima sokova\n",pid);
		
		opr_p.sem_op = -1;
		opr_p.sem_flg = 0;
		opr_v.sem_op = 1;
		opr_v.sem_flg = 0;
		
		opr_p.sem_num = pice_id+2;
		ind = semop(sem_id, &opr_p, 1); // Da li neko vec pije pivo(sok)
		if(ind == -1) break;
		
		opr_p.sem_num = pice_id;
		opr_v.sem_num = pice_id+1;
		
		ind = semop(sem_id, &opr_p, 1); // Kriticni region
		if(ind == -1) break;
		
		if(pice_id == 0)
		{	
			printf("Proces %d: Dosao sam na red, uzimam pivo\n",pid);
			buff[0]++; sleep(3);
			printf("Proces %d: Do sada je popijeno %d piva\n", pid, buff[0]);
			printf("Proces %d: Pijem pivo\n", pid); sleep(3);
			printf("Proces %d: Vratio sam praznu kriglu\n", pid);
			printf("--------------------------------------\n");
		}
		
		else 
		{
			printf("Proces %d: Dosao sam na red, uzimam sok\n",pid);
			buff[1]++; sleep(3);
			printf("Proces %d: Do sada je popijeno %d sokova\n", pid, buff[1]);
			printf("Proces %d: Pijem sok\n", pid); sleep(3);
			printf("Proces %d: Vratio sam praznu casu od soka\n", pid);
			printf("--------------------------------------------\n");
		}
		
		ind = semop(sem_id, &opr_v, 1); // Kriticni region
		if(ind == -1) break;
		
		opr_v.sem_num = pice_id+2;
		ind = semop(sem_id, &opr_v, 1); // Da li neko vec pije pivo(sok)
		if(ind == -1) break;
	}
	
	shmdt(buff);
	
	return 0;
}
