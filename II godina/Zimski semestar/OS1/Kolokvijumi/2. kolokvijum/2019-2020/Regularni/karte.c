/*http://www.cplusplus.com/reference/cstdlib/srand/
Da lepo izbacuje randome
#include <time.h>
void srand (unsigned int seed);
main(){ srand(time(NULL)); }
*/
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
#include <sys/msg.h>
#include <time.h>

union semun{
	int val;
	struct semid_ds *buf;
	ushort *array;
};

typedef struct karta{
	int znak;
	int broj;
	int smer; //0 desno, 1 levo
}karta;

typedef struct poruka_prijava{
	long tip;
	int pidforka;
}poruka_prijava;

int semid;
int msgid;
int dete;
int roditelj;

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

void sig_handler(int sig){
	if(getpid()==roditelj && dete!=-1)
		kill(dete, SIGKILL);
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
	srand(time(NULL));
	roditelj=getpid();
	signal(SIGINT, sig_handler);
	union semun arg; //semctl
	struct sembuf ig1P; //semop
	
	/*Prijave*/
	int i=1, mojtip, shmid;
	char znakt[4];
	poruka_prijava prijave;
	key_t kljuc = ftok("./karte.c", 'x');
	msgid = msgget(kljuc, IPC_CREAT|0666);
	
	key_t kljucsem, kljucshm;
	
	while(1){
		msgrcv(msgid, &prijave, sizeof(prijave), 21, 0);
		prijave.tip=i;
		msgsnd(msgid, &prijave, sizeof(prijave), 0);
		i++;
		if(prijave.tip%4==0){
			dete=fork();
			switch(dete){
				case -1: printf("Greska\n"); exit(0);
				case 0:
					/*trebaju zasebni semafori i deljena memorija za svaka 4 igraca*/
					kljucsem = kljucshm = ftok("./karte.c", getpid());
					
					semid=semget(kljucsem, 4, 0666|IPC_CREAT);
					shmid=shmget(kljucshm, sizeof(karta), 0666|IPC_CREAT);
					if(semid != -1){
						//semafor nije bio kreiran
						arg.val=0;
						semctl(semid, 0, SETVAL, arg);
						semctl(semid, 1, SETVAL, arg);
						semctl(semid, 2, SETVAL, arg);
						semctl(semid, 3, SETVAL, arg);
					}
					else if(errno == EEXIST){ semid = semget(kljucsem, 4, 0); }
					else { printf("Neka druga greska!\n"); exit(0); }
					karte = (karta*)shmat(shmid, NULL,0);
					karte->broj=rand()%13+1;
					karte->znak=rand()%4;
					karte->smer=0;
					dajZnak(karte->znak, znakt);
					printf("karte.c: %d %s\n", karte->broj, znakt);
					/*****************************************************/
					printf("karte.c \nSEMID: %d, SHMID: %d\n", semid,shmid);
					ig1P.sem_num=0;
					ig1P.sem_op=1;
					ig1P.sem_flg=0;
					/*slanje dozvola*/
					mojtip = prijave.tip; //
					prijave.pidforka=getpid(); /*treba mi pid forka zbog kljuca*/
					prijave.tip=mojtip-3;
					msgsnd(msgid, &prijave, sizeof(prijave), 0);
					prijave.tip=mojtip-2;
					msgsnd(msgid, &prijave, sizeof(prijave), 0);
					prijave.tip=mojtip-1;
					msgsnd(msgid, &prijave, sizeof(prijave), 0);
					prijave.tip=mojtip;
					msgsnd(msgid, &prijave, sizeof(prijave), 0);
					sleep(5); // mora pre igrac da se zablokira neg sto ovaj poveca..
					semop(semid, &ig1P, 1);
					printf("Pustio sam keca\n");
					while(1){} // ne sme da se ugasi dok traju igre.. TODO
					break;
				default:
					break;
			}
		}
	}
}
















