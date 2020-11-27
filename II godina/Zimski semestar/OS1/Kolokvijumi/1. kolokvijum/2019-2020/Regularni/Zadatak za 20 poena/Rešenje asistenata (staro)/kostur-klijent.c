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

int main() 
{
	struct poruka_prijava prijava,info_partije;
	struct poruka_potez potez;
	key_t key_red_kom;
	int red_kom_id, rbr, stat, duzina;
	char rec[100];
	
	// TODO : Povezi se na odgovarajuci red
	key_red_kom = ftok("./kostur-server.c", 70);
	printf("key_red_kom = %d\n", key_red_kom);
	
	red_kom_id = msgget(key_red_kom,IPC_CREAT|0666);
	printf("red_kom_id = %d\n", red_kom_id);
	
	// TODO : Prijavi se serveru, i omogući igranje partije
	prijava.tip_poruke = 2 * MAX_PARTIJA + 1;
	strcpy(prijava.poruka,"prijavi me");
	msgsnd(red_kom_id,&prijava,sizeof(prijava),0);
	
	msgrcv(red_kom_id,&prijava,sizeof(prijava),2 * MAX_PARTIJA + 2,0);
	rbr = prijava.id; printf("rbr = %d\n",rbr);
	
	if (rbr%2 == 1) 
	{
		printf("Unesi rec: ");
		fgets(potez.poruka,sizeof(potez.poruka),stdin);
		potez.poruka[strlen(potez.poruka)-1] = '\0';
		
		// TODO : Posalji poruku
		potez.tip_poruke = 2 * MAX_PARTIJA + 3;
		msgsnd(red_kom_id,&potez,sizeof(potez),0);
	}
	
	while (1) 
	{
		// TODO : Primi poruku
		msgrcv(red_kom_id,&potez,sizeof(potez),rbr,0);
		
		strcpy(rec, potez.poruka);
		duzina = strlen(rec);
		
		if (strcmp(rec, "pobeda") == 0) 
		{
			printf("Pobeda\n");
			exit(0);
		}
		
		if (strcmp(rec, "poraz") == 0) 
		{
			printf("Poraz\n");
			exit(0);
		}
		
		printf("Primljena rec: %s\n", rec);
		
		do {
			printf("Unesi rec: ");
			fgets(potez.poruka,sizeof(potez.poruka),stdin);
			potez.poruka[strlen(potez.poruka)-1] = '\0';
			
		} while(rec[duzina-2] != potez.poruka[0] || rec[duzina-1] != potez.poruka[1]);
		
		// TODO : Posalji poruku
		potez.tip_poruke = 2 * MAX_PARTIJA + 3;
		msgsnd(red_kom_id,&potez,sizeof(potez),0);
	}
}

