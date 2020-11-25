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
/*PAZI! Ako su razlicite strukuture nece raditi lepo
Stack overflow - Ako nestavim 'int rbr' lupa mi stack-overflow*/
int msgid;

void sighandler(int sig){
	msgctl(msgid, IPC_RMID, NULL);
	exit(0);
}

int main(){
	int n;
	key_t kljuc = ftok("./server.c", 65);
	msgid = msgget(kljuc, IPC_CREAT|0660);
	signal(SIGINT, sighandler);
	poruka mymsg;
	//printf("AAA %ld\n", sizeof(mymsg.tekst));
	scanf("%d", &n);
	for(int i=1; i<=n; i++){
		/*Ceka prijavljivanje klijenata*/
		msgrcv(msgid, &mymsg, sizeof(mymsg), 21, 0);
		printf("Prihvacen klijent, dodeljujem ID %d .\n", i);
		mymsg.tip=i; // tip za slanje
		msgsnd(msgid, &mymsg, sizeof(mymsg), 0);
	}
	//msgctl(msgid, IPC_RMID, NULL);
}
