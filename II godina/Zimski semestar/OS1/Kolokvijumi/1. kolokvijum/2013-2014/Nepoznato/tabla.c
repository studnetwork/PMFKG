#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>



typedef struct poruka{
		long tip_poruke;
		pid_t pid;
		int k;
		char tekst[50];
	}poruka;



int main()
{
	key_t key;
	int id;
	pid_t pid;
	poruka tabla;
	int k,i;
	
	key=ftok("./tabla.c",20);
	id=msgget(key,IPC_CREAT|0666);
	
	int prijave[4];
	int pozicija[4];
	
	//Prijave igraca !!!
	printf("PRIJAVLJUJU SE IGRACI!!\n");
	for(i=0;i<4;i++)
	{
		msgrcv(id,&tabla,sizeof(tabla),1,0);
		prijave[i]=tabla.pid;
		pozicija[i]=0;
	}
	int n=4,j,l;
	printf("POCINJE IGRA!!\n");
	while(1)
	{
		printf("NOVI KRUG U IGRI!!!\n");
		sleep(3);
		for(i=0;i<n;i++)
		{
			printf("Saljem poruku igracu %d da je on na redu\n",i);
			tabla.tip_poruke=prijave[i];
			strcpy(tabla.tekst,"igraj");
			msgsnd(id,&tabla,sizeof(tabla),0);
			printf("TABLA : Cekam da primim signal od igraca %d\n",i);
			msgrcv(id,&tabla,sizeof(tabla),prijave[i],0);
			pozicija[i]+=tabla.k;
			if(pozicija[i] >= 20 )
				{
					printf("Saljem poruku igracu %d da je zavrsio igru\n",i);
					tabla.tip_poruke=prijave[i];
					strcpy(tabla.tekst,"kraj");
					msgsnd(id,&tabla,sizeof(tabla),0);
					//igrac je pobedio igra se zavrsava
					exit(0);
				}
			else
			{
				// proveravamo da li smo pojeli nekog i ukolioko jesmo to treba da javimo
				for(j=0;j<n;j++)
				{
					if(i != j && pozicija[i] == pozicija[j]) 
					{
						// igrac na poziciji i je pojeo igraca na poziciji j
						//izbacujemo j iz niza;
						printf("Saljem poruku igracu %d da je pojeden\n",j);
						tabla.tip_poruke=prijave[j];
						strcpy(tabla.tekst,"pojeden");
						msgsnd(id,&tabla,sizeof(tabla),0);
						for(l=j;l<n-1;l++)
						{
							pozicija[l]=pozicija[l+1];
							prijave[l]=prijave[l+1];
						}
						if(i > j)
							i--;
						n--;
						j--;
						if(n==0)
							exit(0);
					}
				}	
			}
			
		}
	}
	
	return 0;
}
