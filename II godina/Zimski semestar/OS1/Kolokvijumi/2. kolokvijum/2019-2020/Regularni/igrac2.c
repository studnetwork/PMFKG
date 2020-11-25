#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <sys/msg.h>

union semun{
	int val;
	struct semid_ds *buf;
	ushort *array;
};

typedef struct karta{
	int znak;
	int broj;
	int smer;
}karta;

typedef struct poruka_prijava{
	long tip;
	int pidforka;
}poruka_prijava;

char dajZnak(int broj, char *str){
	/*znak karo(0),pik(1),tref(2),herc(3)*/
	if(broj==0)
		strcpy(str, "karo");
	if(broj==1)
		strcpy(str, "pik");
	if(broj==2)
		strcpy(str, "tref");
	if(broj==3)
		strcpy(str, "herc");
}

int semid;
int msgid;

void sig_handler(int sig){
	printf("\nPrimio SIGINT\n");
	semctl(semid, 0, IPC_RMID);
	semctl(semid, 1, IPC_RMID);
	semctl(semid, 2, IPC_RMID);
	semctl(semid, 3, IPC_RMID);
	msgctl(msgid, IPC_RMID, NULL);
	exit(0);
}
void srand (unsigned int seed);

int main(){
	
	karta *karte;
	srand (time(NULL));
	/*Prijave*/
	int mojtip;
	poruka_prijava prijave;
	key_t kljuc = ftok("./karte.c", 'x');
	msgid = msgget(kljuc, 0);
	prijave.tip=21;
	msgsnd(msgid, &prijave, sizeof(prijave), 0);
	msgrcv(msgid, &prijave, sizeof(prijave), 0, 0);
	mojtip=prijave.tip;
	printf("Igrac1: Dodeljen redni broj %d\n", mojtip);
	msgrcv(msgid, &prijave, sizeof(prijave), mojtip, 0); // ceka dozvolu od forkovanog karte.c
	/***********************************************/
	/*SAD U prijavama imam tipforka*/
	key_t kljucsem, kljucshm;
	kljucsem = kljucshm = ftok("./karte.c", prijave.pidforka);
	semid = semget(kljucsem, 4, 0666|IPC_CREAT);
	int shmid = shmget(kljucshm, sizeof(karta), 0666|IPC_CREAT);
	signal(SIGINT, sig_handler);
	union semun arg; //semctl
	struct sembuf ig2S, ig3P, ig1P; //semop
	if(semid != -1){
		//semafor nije bio kreiran
		arg.val=0;
		semctl(semid, 0, SETVAL, arg);
		semctl(semid, 1, SETVAL, arg);
		semctl(semid, 2, SETVAL, arg);
		semctl(semid, 3, SETVAL, arg);
	}
	else if(errno == EEXIST){ semid = semget(kljucsem, 4, 0); }
	else { printf("Neka druga greska!\n"); exit(0);}
	karte = (karta*)shmat(shmid, NULL,0);
	/*****************************************************/
	/*povezan na semafore, deljenu mem... */
	
	
	/*znak karo(0),pik(1),tref(2),herc(3)*/
	ig2S.sem_num=1;
	ig2S.sem_op=-1;
	ig2S.sem_flg=0;
	
	ig3P.sem_num=2;
	ig3P.sem_op=1;
	ig3P.sem_flg=0;
	
	ig1P.sem_num=0;
	ig1P.sem_op=1;
	ig1P.sem_flg=0;
	
	int znak, broj, ind, potez=1;
	char znakt[4];
	while(1){
		if(potez==7) break;
		ind = semop(semid, &ig2S, 1); //blok
		if(ind==-1)
			break;
		znak = rand()%4;
		broj = rand()%13+1; //necemo nulu
		printf("Potez %d-----------------------\n", potez);
		dajZnak(znak, znakt);
		printf("Igrac: %d %s\n", broj, znakt);
		dajZnak(karte->znak, znakt);
		printf("Deljena: %d %s\n", karte->broj, znakt);
		if(znak==karte->znak || broj==karte->broj){
			printf("Izbacio sam kartu igrac2\n"); 
			karte->broj=broj;
			karte->znak=znak;
			if(broj==8){
				if(karte->smer==1) karte->smer=0;
				else karte->smer=1;
			}
		}
		else 
			printf("Nemam adekvatnu kartu\n");
		potez++;
		sleep(3);
		if(karte->smer==0)
			semop(semid, &ig3P, 1);
		else
			semop(semid, &ig1P, 1);
	}
	
}
















