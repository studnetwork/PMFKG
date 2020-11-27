#include <stdio.h>
#include <sys/ipc.h>  /* key_t, ftok         */
#include <sys/msg.h>  /* msgget              */
#include <unistd.h>   /* pid_t, getpid       */
#include <string.h>	  /* strcmp, strcpy      */

#define MAX_GAMES 20
#define WORD_LEN 20
#define KEYPATH_COMM "./klijent.c"
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

int main()
{
	key_t key;
	pid_t myPid;
	int queID;
	int len;

	char buff[WORD_LEN + 1];

	Login l;
	Potez p;

	myPid = getpid();
	printf("PID klijenta: %d\n", myPid );

	key = ftok( KEYPATH_COMM, PROJ_ID );
	queID = msgget( key, IPC_CREAT | 0666 );

	l.mtype = MTYPE_REQ;
	l.pid = myPid;
	printf("Poslat zahtev za prijavu\n");
	msgsnd( queID, &l, sizeof(l), 0 );

	printf("Cekam potvrdu prijave...\n");
	msgrcv( queID, &l, sizeof(l), myPid, 0 );
	printf("Uspesno sam se prijavio.\n");

	printf("Uspostavi vezu za serverom partije...\n");
	msgrcv( queID, &l, sizeof(l), myPid, 0 );
	printf("Uspostavljena veza sa serverom #%d\n", l.srvPid );

	if( l.id % 2 == 1 )
	{
		/* zapocinje partiju*/
		printf("Unesite rec:\n");
		fscanf( stdin, "%s", p.mtext );
		getchar();

		p.mtype = l.srvPid;
		msgsnd( queID, &p, sizeof(p), 0 );
	}
	else
		printf("Ceka se prvi igrac da zapocne igru...\n");

	
	while(1)
	{
		msgrcv( queID, &p, sizeof(p), l.id, 0 );
		if( !strcmp( p.mtext, POBEDA ) )
		{
			printf("%s\n", POBEDA );
			return 0;
		}
		else if( !strcmp( p.mtext, PORAZ ) )
		{
			printf("%s\n", PORAZ );
			return 0;
		}
		else
			printf(" <-- Primljena rec: %s\n", p.mtext );

		
		len = strlen( p.mtext );
		do
		{
			printf("Unesite rec:\n");
			fscanf( stdin, "%s", buff );
			getchar();
			
		}while( p.mtext[len-2] != buff[0] || p.mtext[len-1] != buff[1] );

		strcpy( p.mtext, buff );
		p.mtype = l.srvPid;
		msgsnd( queID, &p, sizeof(p), 0 );
		printf(" --> Poslata rec: %s\n", p.mtext );
	}
	
}
