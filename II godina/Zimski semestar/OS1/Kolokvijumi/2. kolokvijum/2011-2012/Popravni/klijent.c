#include <stdio.h>
#include <stdlib.h> // srand, rand, exit, EXIT_FAILURE
#include <time.h>   // time

#include <sys/ipc.h> // ftok, key_t
#include <sys/msg.h> // msgget, msgsnd, msgrcv, IPC_CREAT
#include <string.h>  // strcmp

#define MSG_LEN 40
#define PROJ_ID '1'
#define QUE_PERMS 0666
#define IZNOS_LIM 10000

#define MTYPE_NOTF 3
#define MTYPE_RESP ( MTYPE_NOTF + 1 )

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


int main( int argc, char **argv )
{
	if( argc != 2 )
	{
		printf("Pokrenite program sa tacno jednim argumentom!\n");
		return EXIT_FAILURE;
	}
	
	key_t stat_key, comm_key;
	int comm_queID, stat_queID;
	
	Poruka p;
	Transakcija t;

	/* postavi seed za funkciju rand */
	srand( time(NULL) );

	/* red za obavestenja */
	stat_key = ftok( stat_path, PROJ_ID );
	stat_queID = msgget( stat_key, IPC_CREAT | QUE_PERMS );

	/* red za transakcije */
	comm_key = ftok( comm_path, PROJ_ID );
	comm_queID = msgget( comm_key, IPC_CREAT | QUE_PERMS );

	/* ekstraktuj broj iz stringa p.mtext
	 * i unesi ga u p.mtype */
	sscanf( argv[1],"%ld", &t.mtype );

	/* generise random vrednost za iznos koja nije
	 * veca od IZNOS_LIM; 0 < iznos < IZNOS_LIM    */
	t.iznos = rand() % IZNOS_LIM + 1; 

	if( t.mtype == 1 )
		printf(" <-- Zahtev za uplatu u iznosu od %d din.\n", t.iznos );
	else
		printf(" <-- Zahtev za isplatu u iznosu od %d din.\n", t.iznos );

	msgsnd( comm_queID, &t, sizeof(t.iznos), 0 );
	printf("Zahtev je poslat\n\n");
	
	if( t.mtype == 2 )
	{
		/* prihvati odgovor transakcije*/
		printf("Cekam odgovor na zahtev...\n");
		msgrcv( stat_queID, &p, sizeof(p.mtext), MTYPE_RESP, 0 );

		printf(" --> %s\n", p.mtext );
	}
}
