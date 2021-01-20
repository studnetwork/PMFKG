#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

int g;

#define MAX_PUTNIKA 3

#define MSGSZ( struktura ) ( sizeof( (struktura) ) - sizeof( (struktura).mtype ) )

typedef struct
{
	long mtype;
	pid_t pid;
} poruka;

void sh( int sig )
{
	msgctl( g, IPC_RMID, NULL);
	exit(EXIT_FAILURE);
}

int main()
{
signal(SIGINT, sh );
	int i, qid, brMisionara, brLjudozdera, temp;
	key_t key;
	poruka p;
	int pidLjud[MAX_PUTNIKA];
	int pidMisi[MAX_PUTNIKA];
	
	key = ftok( "./brod.c", 'a' );
	qid = msgget( key, IPC_CREAT | 0660 );
g = qid; /* debugging */
	srand( time(NULL) );
	while(1)
	{
		/* debugging */
		sleep(4);
		
		/* nasumican odabir; ljudozdera ne sme imati vise od misionara */
		do
		{
			brMisionara = rand() % ( MAX_PUTNIKA + 1 );
			brLjudozdera = MAX_PUTNIKA - brMisionara;
		} while( brLjudozdera > brMisionara && brLjudozdera != 3 );

		printf("Izabran je sastav (Lj:M): %d:%d\n", brLjudozdera, brMisionara );

		/* pokupi prijave ljudozdera za dati sastav */
		for(i = 0, temp = 0; i < brLjudozdera; i++)
		{
			if( msgrcv( qid, &p, MSGSZ(p), 'l' + 'j', IPC_NOWAIT ) != -1 )
			{
				temp++;
				pidLjud[i] = p.pid;
			}
		}

		/* proveri da li neki fali za predvidjeni sastav */
		if( temp < i )
		{
			printf("Nema dovoljno putnika za izabrani sastav\n\n");

			/* vrati ucitane ljudozdere */
			p.mtype = 'l' + 'j';
			for(i = 0; i < temp; i++)
			{
				p.pid = pidLjud[i];
				msgsnd( qid, &p, MSGSZ(p), 0 );
			}
			
			continue;
		}
		else
		{
			/* pokupi prijave misionara za dati sastav */
			for(i = 0, temp = 0; i < brMisionara; i++)
			{
				if( msgrcv( qid, &p, MSGSZ(p), 'm', IPC_NOWAIT ) != -1 )
				{
					temp++;
					pidMisi[i] = p.pid;
				}
			}

			/* proveri da li neki fali za predvidjeni sastav */
			if( temp < i )
			{
				printf("Nema dovoljno putnika za izabrani sastav\n\n");

				/* vrati ucitane misionare */
				p.mtype = 'm';
				for(i = 0; i < temp; i++)
				{
					p.pid = pidMisi[i];
					msgsnd( qid, &p, MSGSZ(p), 0 );
				}

				/* vrati ucitane ljudozdere */
				p.mtype = 'l' + 'j';
				for(i = 0; i < brLjudozdera; i++)
				{
					p.pid = pidLjud[i];
					msgsnd( qid, &p, MSGSZ(p), 0 );
				}
				
				continue;
			}
			/* brod moze da preveze putnike */
			else
			{
				printf("Brod je otisnut sa obale.\n");

				/* obavestava ljudozdere da su se ukrcali na brod */
				for(i = 0; i < brLjudozdera; i++)
				{
					p.mtype = pidLjud[i];
					msgsnd( qid, &p, MSGSZ(p), 0 );
				}

				/* obavestava misionare da su se ukrcali na brod */
				for(i = 0; i < brMisionara; i++)
				{
					p.mtype = pidMisi[i];
					msgsnd( qid, &p, MSGSZ(p), 0 );
				}

				/* vreme koje je potrebno da predje sa leve strane na desnu */
				sleep(4);

				/* obavestava ljudozdere da su prevezeni na desnu stranu */
				for(i = 0; i < brLjudozdera; i++)
				{
					p.mtype = pidLjud[i];
					msgsnd( qid, &p, MSGSZ(p), 0 );
				}

				/* obavestava misionare da su prevezeni na desnu stranu */
				for(i = 0; i < brMisionara; i++)
				{
					p.mtype = pidMisi[i];
					msgsnd( qid, &p, MSGSZ(p), 0 );
				}

				printf("Putnici su prevezeni na drugu stranu obale\n");
				
				/* vreme koje je potrebno da predje sa desne strane na levu */
				sleep(4);

				printf("Brod se vratio na levu stranu obale.\n");
			}
		}
	}
}
