#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_PARTIJA 20
#define MAX_LEN 21

//TODO : Deklarisati potrebne globalne promenljive
int flag = 1, br_partija = 0, red_kom_id, red_info_id;
int pid_niz[20];

//TODO : Definisati potrebne strukture za razmenu poruka (može i drugačije)
struct poruka_prijava
{
	long tip_poruke;
	char poruka[MAX_LEN];
	int id;
};

struct poruka_potez
{
	long tip_poruke;
	char poruka[MAX_LEN];
};

struct poruka_partija
{
	long tip_poruke;
	char poruka[1000];
	int pobednik_id;
};

// Za zadata dva redna broja igrača, čita poruku prvog, proverava da li je kraj igre i ako jeste šalje odgovarajuće poruke a ako nije, prosleđuje poruku drugom igraču

int proveri_rec(int rbr1, int rbr2, int red_kom_id) 
{
	struct poruka_prijava klijent;
	struct poruka_potez potez;
	char rec[100];
	int duzina;
	
	//TODO :  primi poruku od klijenta 
	msgrcv(red_kom_id,&klijent,sizeof(klijent),2 * MAX_PARTIJA + 3,0);
	
	strcpy(rec,klijent.poruka);
	duzina = strlen(rec);
	
	if (rec[duzina-2]=='n' && rec[duzina-1]=='t') //kraj igre
	{
		struct poruka_partija pobednik;

		printf("Partija igraca %d i %d je gotova\n", rbr1, rbr2);
		
		// TODO: Poslati poruku prvom igracu da je pobedio a drugom da je izgubio
		strcpy(potez.poruka,"poraz");
		if(flag) potez.tip_poruke = rbr2;
		else potez.tip_poruke = rbr1;
		msgsnd(red_kom_id,&potez,sizeof(potez),0);
		
		strcpy(potez.poruka,"pobeda");
		if(flag) pobednik.pobednik_id = potez.tip_poruke = rbr1;
		else pobednik.pobednik_id = potez.tip_poruke = rbr2;
		msgsnd(red_kom_id,&potez,sizeof(potez),0);
		
		//TODO: Upisati u red partija redni broj pobednika
		pobednik.tip_poruke = 1;
		msgsnd(red_info_id,&pobednik,sizeof(pobednik),0);
		
		return 1; // partija je gotova
	}
	
	else //TODO: prosledi poruku drugom igracu
	{
		if(flag) 
		{
			potez.tip_poruke = rbr2;
			flag = 0;
		}
		
		else
		{
			potez.tip_poruke = rbr1;
			flag = 1;
		}
		
		strcpy(potez.poruka,rec);
		printf("\n%s\n",potez.poruka);
		msgsnd(red_kom_id,&potez,sizeof(potez),0);
		return 0; // partija još uvek traje
	}
}


void sighandler(int sig) 
{
	struct poruka_partija partija;
	int i, parni = 0, neparni = 0;
	
	//TODO : Sačekaj svu decu da završe
	for(i = 0; i < 2*br_partija; i++) waitpid(pid_niz[i],NULL,0);
	
	//TODO : Procitaj statistiku i ispiši na standardni izlaz
	for(i = 0; i < br_partija; i++)
	{
		msgrcv(red_info_id,&partija,sizeof(partija),1,0);
		
		if(partija.pobednik_id%2 == 0) parni++;
		else neparni++;	
	}
	
	printf("Turnir je zavrsen\n");
	printf("Neparna/parna pozicija - %d/%d\n", neparni, parni);
	msgctl(red_kom_id, IPC_RMID, NULL);
	msgctl(red_info_id, IPC_RMID, NULL);
	exit(0);
}

int main() 
{
	struct poruka_prijava prijava1, prijava2;
	struct poruka_partija partija_tmp;
	key_t key_red_kom, key_red_info;
	pid_t pid, pid_servera;
	int i = 1, j = 0, rbr = 1, rbr1, rbr2, stat, pid_partija;
	
	pid_servera = getpid(); printf("pid servera: %d\n",pid_servera);
	signal(SIGINT,sighandler);
	
	// TODO : Kreiraj redove
	key_red_kom = ftok("./kostur-server.c", 70);
	printf("key_red_kom = %d\n", key_red_kom);
	
	key_red_info = ftok("./kostur-server.c", 71);
	printf("key_red_info = %d\n", key_red_info);
	
	red_kom_id = msgget(key_red_kom,IPC_CREAT|0666);
	printf("red_kom_id = %d\n", red_kom_id);
	
	red_info_id = msgget(key_red_info,IPC_CREAT|0666);
	printf("red_info_id = %d\n", red_info_id);
	
	while(1) // TODO : Prijava klijenta, fork, igra
	{
		//printf("\n+\n");
		msgrcv(red_kom_id,&prijava1,sizeof(prijava1),2 * MAX_PARTIJA + 1,0);
		if(strcmp(prijava1.poruka,"prijavi me") == 0)
		{
			rbr1 = prijava1.id = i++;
			prijava1.tip_poruke = 2 * MAX_PARTIJA + 2;
			strcpy(prijava1.poruka,"prijavljen si");
			msgsnd(red_kom_id,&prijava1,sizeof(prijava1),0);
		}
		
		msgrcv(red_kom_id,&prijava2,sizeof(prijava2),2 * MAX_PARTIJA + 1,0);
		if(strcmp(prijava2.poruka,"prijavi me") == 0)
		{
			rbr2 = prijava2.id = i++;
			prijava2.tip_poruke = 2 * MAX_PARTIJA + 2;
			strcpy(prijava2.poruka,"prijavljen si");
			msgsnd(red_kom_id,&prijava2,sizeof(prijava2),0);
		}
		
		pid = fork();
		
		switch(pid)
		{
			case -1:
				printf("Doslo je do greske u forkovanju!\n");
				exit(1);
				break;
			
			case 0: // Partija
				pid_niz[br_partija] = getpid();
				
				while(1) if(proveri_rec(rbr1,rbr2,red_kom_id)) break;
				
				return 0;
				break;
			
			default:
				br_partija++;	
				break;
		}
	}
	
	return 0;
}

