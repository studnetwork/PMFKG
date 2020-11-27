#include <stdio.h>
#include <sys/ipc.h>  /* key_t, ftok         */
#include <sys/msg.h>  /* msgget              */
#include <unistd.h>   /* fork, pid_t, getpid */
#include <string.h>	  /* strcmp, strcpy      */
#include <stdlib.h>   /* exit, EXIT_SUCCESS  */
#include <sys/wait.h> /* waitpid             */

#define MAX_GAMES 20
#define WORD_LEN 20
#define KEYPATH_COMM "./klijent.c"
#define KEYPATH_STAT "./server.c"
#define PROJ_ID '1'
#define MTYPE_REQ (2*MAX_GAMES+1)
#define POBEDA "pobedio"
#define PORAZ "izgubio"

typedef struct
{
	long mtype;
	//char mtext[1];
	int id;
	/* ukoliko bi server odgovorio na zahtev za prijavu
	 * sa porukom koja je nekog odredjenog tipa 't' onda
	 * bi postojala mogucnost da neki drugi korisnik
	 * pokupi poruku koja nije namenjena njemu         */
	pid_t pid;
	pid_t srvPid;
} Login;

typedef struct
{
	long mtype;
	char mtext[WORD_LEN+1];
} Potez;

typedef struct
{
	long mtype;
	int pozPobedn;
} Ishod;

pid_t g_chldPids[MAX_GAMES];
int g_nchild;

int g_statQID;
int g_commQID;

void shParent( int sig )
{
	int i;
	int neparna, parna;
	Ishod ish;

	neparna = parna = 0;
	
	for( i = 0; i < g_nchild; i++ )
	{
		/* nije potpuno ispravno; bolje bi da je izvrsena
		 * provera izlaza svakog child procesa; odnosno da
		 * se proveri da li su uspesno izvrseni sa WIFEXITED */
		waitpid( g_chldPids[i], NULL, 0 );

		msgrcv( g_statQID, &ish, sizeof(ish), g_chldPids[i], 0 );
		printf("Partija (%d) je zavrsena\n", g_chldPids[i] );
		printf("Pozicija pobednika: %d\n\n", ish.pozPobedn );

		if( ish.pozPobedn % 2 )
			neparna++;
		else
			parna++;
	}
	printf("neparna/parna pozicija : %d/%d\n", neparna, parna );
	printf("Turnir je zavrsen\n");

	msgctl( g_commQID, IPC_RMID, NULL );
	msgctl( g_statQID, IPC_RMID, NULL );
}

int main()
{
	printf("PID glavnog servera: %d\n",  getpid() );
	Login l1, l2;
	Potez p1, p2;
	Ishod ish;
	key_t commKey, statKey;
	pid_t pid;
	int len;
	int commQID, statQID;
	int count = 0;
	g_nchild = 0;

	commKey = ftok( KEYPATH_COMM, PROJ_ID );
	statKey = ftok( KEYPATH_STAT, PROJ_ID );

	g_commQID = commQID = msgget( commKey, IPC_CREAT | 0666 );
	g_statQID = statQID = msgget( statKey, IPC_CREAT | 0666 );

	printf("Cekam zahteve za prijavu...\n");
	while(1)
	{
		msgrcv( commQID, &l1, sizeof(l1), MTYPE_REQ, 0 );
		printf("Uspesno ulogovan ucesnik #%d\n", count+1);
		
		msgrcv( commQID, &l2, sizeof(l2), MTYPE_REQ, 0 );
		printf("Uspesno ulogovan ucesnik #%d\n", count+2);

		l1.mtype = l1.pid;
		l1.id = ++count;
		msgsnd( commQID, &l1, sizeof(l1), 0 );

		l2.mtype = l2.pid;
		l2.id = ++count;
		msgsnd( commQID, &l2, sizeof(l2), 0 );

		pid = fork();
		if( pid )
		{
			signal( SIGINT, shParent );
			g_chldPids[g_nchild++] = pid;
		}
		else
		{
			signal( SIGINT, SIG_IGN );
			pid = getpid();
			printf("PID partije: %d\n", pid );
			
			/* ukoliko bi smo u narednoj while petlji prihvatali
			 * poruke od igraca preko istog tipa, doslo bi do toga
			 * da razliciti child procesi uzimaju poruke od igraca
			 * za cije partije nisu zaduzeni; iz tog razloga za tip
			 * poruke postavljamo pid, cime bi smo omogucili da samo
			 * igraci za ciju je partiju taj child proces zaduzen,
			 * mogu da mu salju poruke                              */
			l1.mtype = l1.pid;
			l1.srvPid = pid;
			msgsnd( commQID, &l1, sizeof(l1), 0 );

			l2.mtype = l2.pid;
			l2.srvPid = pid;
			msgsnd( commQID, &l2, sizeof(l2), 0 );

			while(1)
			{
				msgrcv(	commQID, &p1, sizeof(p1), l1.srvPid, 0 );
				len = strlen(p1.mtext);
				if( !strcmp( p1.mtext + (len - 2), "nt" ) )
				{
					printf("Partija igraca %d i %d je gotova\n", l1.id, l2.id );
					p1.mtype = l1.id;
					strcpy( p1.mtext, POBEDA );
					msgsnd( commQID, &p1, sizeof(p1), 0 );

					p2.mtype = l2.id;
					strcpy( p2.mtext, PORAZ );
					msgsnd( commQID, &p2, sizeof(p2), 0 );

					ish.mtype = l1.srvPid;
					ish.pozPobedn = 1;
					msgsnd( statQID, &ish, sizeof(ish), 0 );

					exit(EXIT_SUCCESS);
				}
				else
				{
					p2.mtype = l2.id;
					strcpy( p2.mtext, p1.mtext );
					msgsnd( commQID, &p2, sizeof(p2), 0 );
				}

				/* drugi prima poruku i saljem je prvom,
				 * ukoliko se rec ne zavrsava sa "nt";
				 * u suprotnom zavrsava partiju  */
				msgrcv( commQID, &p2, sizeof(p2), l2.srvPid, 0 );
				len = strlen( p2.mtext );
				if( !strcmp( p2.mtext + (len - 2), "nt" ) )
				{
					printf("Partija igraca %d i %d je gotova\n", l1.id, l2.id );
					p1.mtype = l1.id;
					strcpy( p1.mtext, PORAZ );
					msgsnd( commQID, &p1, sizeof(p1), 0 );

					p2.mtype = l2.id;
					strcpy( p2.mtext, POBEDA );
					msgsnd( commQID, &p2, sizeof(p2), 0 );

					ish.mtype = l2.srvPid;
					ish.pozPobedn = 2;
					msgsnd( statQID, &ish, sizeof(ish), 0 );

					exit(EXIT_SUCCESS);
				}
				else
				{
					p1.mtype = l1.id;
					strcpy( p1.mtext, p2.mtext );
					msgsnd( commQID, &p1, sizeof(p1), 0 );
				}
			}
		}
		
	}
}
