#include <stdio.h>
#include <sys/ipc.h> // ftok, key_t
#include <sys/msg.h> // msgget, msgsnd, msgrcv, IPC_CREAT
#include <stdlib.h>  // exit, EXIT_FAILURE
#include <string.h>  // strcmp
/**/#include <signal.h>  // !! nije potreban; koriscen samo za debugging

#define MSG_LEN 40
#define PROJ_ID '1'
#define MTYPE_NOTF 3
#define MTYPE_RESP ( MTYPE_NOTF + 1 )
#define QUE_PERMS 0666

char const * const stat_path = "./server.c";
char const * const comm_path = "./klijent.c";
char const * const respMsgFail = "Na racunu nema dovoljno sredstava";
char const * const respMsgSucc = "Isplata je izvrsena" ;

typedef struct
{
	long mtype;
	char mtext[MSG_LEN+1];
} Poruka;

typedef struct
{
	long mtype;
	int iznos;
} Transakcija;

/* ################################################## */
/* sve sto ispred cega stoji
 * prazan komentar moze da se
 * obrise                        */
/*   nisu potrebne               */
/* */int g1;/*                   */
/* */int g2;/*                   */
/* njima su dodeljene vrednosti
 * za stat_queID i comm_queID    */

/* nije potreban za zadatak; koriscen za
 * jednostavnije brisanje napravljenih redova */
void sh( int sig )
{
	/* oslobodi zauzete resurse */
	msgctl( g1, IPC_RMID, NULL );
	msgctl( g2, IPC_RMID, NULL );
	exit(EXIT_FAILURE);
}
/* ################################################## */


int main( )
{
/**/signal( SIGINT, sh ); // nepotrebno
	
	key_t stat_key, comm_key;
	int comm_queID, stat_queID;
	int racun;

	Poruka p;
	Transakcija t;

	/* red za obavestenja */
	stat_key = ftok( stat_path, PROJ_ID );
	g1 =/**/stat_queID = msgget( stat_key, IPC_CREAT | QUE_PERMS );

	/* red za transakcije */
	comm_key = ftok( comm_path, PROJ_ID );
	g2 = /**/comm_queID = msgget( comm_key, IPC_CREAT | QUE_PERMS );

	racun = 0;
	
	while(1)
	{	
		printf("\nCekam zahtev za transakciju...\n");
		msgrcv( comm_queID, &t, sizeof(t.iznos), 0, 0 );
		
		switch( t.mtype )
		{
			case 1:
					racun += t.iznos;
					printf(" --> Zahtev za uplatu u iznosu od %d din\n", t.iznos );
					printf("Trenutno stanje racuna: %d\n\n", racun );
					
					break;
			case 2:
					
					printf(" --> Zahtev za isplatu u iznosu od %d din\n", t.iznos );
					if( racun - t.iznos < 0 )
					{
						p.mtype = MTYPE_RESP;
						strcpy( p.mtext, respMsgFail );
						msgsnd( stat_queID, &p, sizeof(p.mtext), 0 );
					}
					else
					{
						racun -= t.iznos;
						p.mtype = MTYPE_RESP;
						strcpy( p.mtext, respMsgSucc );
						msgsnd( stat_queID, &p, sizeof(p.mtext), 0 );
						
						printf("Trenutno stanje racuna: %d\n\n", racun );
					}
					
					break;

			default:
					printf("Nepoznati tip poruke\n");
					printf("Server se gasi\n");

					/* oslobodi zauzete resurse */
					msgctl( comm_queID, IPC_RMID, NULL );
					msgctl( stat_queID, IPC_RMID, NULL );
					
					exit(EXIT_FAILURE);
		}
	}
}
