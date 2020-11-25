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
	poruka proizvodjac;
	int br=0;
	pid_t pidd;
	
	pidd=getpid();
	key=ftok("./proizvodjac.c",20);
	
	id=msgget(key,IPC_CREAT|0666);
	
	while(1)
	{
		br++;
		proizvodjac.pid=pidd;
		proizvodjac.br=br;
		proizvodjac.tip_poruke=1;
		msgsnd(id,&proizvodjac,sizeof(proizvodjac),0);
		printf("Proizvodjac: %d\t%d\n",pidd,br);
		sleep(2);
	}
	
	return 0;
}
