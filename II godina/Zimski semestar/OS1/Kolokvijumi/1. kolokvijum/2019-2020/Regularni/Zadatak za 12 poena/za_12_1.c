#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

int pid;
int dete=-1;

void sighandler(int sig){
	if(getpid()==pid){
		
		printf("\nPrimio sam SIGINT.\n");
		if(dete!=-1) { 
			printf("Saljem SIGKILL detetu\n");
			kill(dete, SIGKILL);
		}
		exit(0);
	}
	else printf("\nProces dete nije moguce prekinuti.\n");
}

int main(){
	int n,i;
	int random;
	pid=getpid();
	signal(SIGINT, sighandler);
	scanf("%d", &n);
	dete = fork(); // ditety vraca 0
	switch(dete){
		case -1:
			printf("Greska!\n");
		case 0:
			//proces dite
			random = rand()%10;
			for(i=1; i<n; i++){
				if(i%2!=0){
					printf("PD: %d\n",i);
					sleep(random);
				}
			}
			printf("Proces dite %d\n", getpid());
			break; //dete se razobada. uleti u difjult i ako je 0
		default:
			//proces rodite LJ
			random = rand()%10;
			for(i=1; i<n; i++){
				if(i%2==0){
					printf("PR: %d\n",i);
					sleep(random);
				}
			}
	}
	
}
