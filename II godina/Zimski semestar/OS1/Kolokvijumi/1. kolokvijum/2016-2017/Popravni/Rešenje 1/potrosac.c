#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <signal.h>


typedef struct poruka{
	long tip_poruke;
	pid_t pid;
	int br;
	}poruka;

int main()
{
	key_t key;
	int id;
	poruka potrosac;
	int br=0;

	key=ftok("./proizvodjac.c",20);
	
	id=msgget(key,IPC_CREAT|0666);
	
	pid_t pid;
	pid=fork();
	
	switch (pid){
		case -1:
				perror("Greska pri forkovanju!!\n");
				exit(0);
		case 0:
				//proces dete
				while(1)
				{
					msgrcv(id,&potrosac,sizeof(potrosac),1,0);
					printf("Potrosac dete: %d\t%d\n",potrosac.pid,potrosac.br);	
				}
				exit(1);	
		default:
				//proces roditelj
				while(1)
				{
					msgrcv(id,&potrosac,sizeof(potrosac),1,0);
					printf("Potrosac roditelj: %d\t%d\n",potrosac.pid,potrosac.br);
				}
	
	
	}
		
		
	
	return 0;
}
