#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
typedef struct poruka{	
	long tip;
	char tekst[30];
	int rbr;
}poruka;

int msgid;

void sighandler(int sig){
	msgctl(msgid, IPC_RMID, NULL);
	exit(0);
}

int main(){
	int n, mojtip;
	poruka mymsg;
	key_t kljuc = ftok("./server.c", 65);
	msgid = msgget(kljuc, 0);
	signal(SIGINT, sighandler);
	mymsg.tip=21;
	msgsnd(msgid, &mymsg, sizeof(mymsg), 0);
	msgrcv(msgid, &mymsg, sizeof(mymsg), 0, 0); //bilo koi tip+block
	printf("KLIJENT: %ld\n", mymsg.tip);
	/******************************************/
	mojtip=mymsg.tip;
	if(mojtip%2!=0) { //neparan, salje za 1 vise
		printf("Klijent %d: Unesi poruku:\n", mojtip);
		fgetc(stdin); fgets(mymsg.tekst, 30, stdin);
		mymsg.tekst[strlen(mymsg.tekst)-1]=0; 
		//okej al nmvz sa stekOverflow-om
		mymsg.tip+=1;
		msgsnd(msgid, &mymsg, sizeof(mymsg), 0);
		msgrcv(msgid, &mymsg, sizeof(mymsg), mojtip, 0);
	}
	else{
		msgrcv(msgid, &mymsg, sizeof(mymsg), mojtip, 0);
		printf("Klijent %d: Prihvacena poruka,unesi odg:\n", mojtip);
		fgetc(stdin); fgets(mymsg.tekst, 30, stdin);
		mymsg.tekst[strlen(mymsg.tekst)-1]=0;
		mymsg.tip-=1;
		msgsnd(msgid, &mymsg, sizeof(mymsg), 0);
	}
}





