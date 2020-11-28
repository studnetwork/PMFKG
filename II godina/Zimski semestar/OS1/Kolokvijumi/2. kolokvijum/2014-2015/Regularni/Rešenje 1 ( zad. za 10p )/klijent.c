#include <stdio.h>
#include <sys/ipc.h> // ftok, key_t, pid_t
#include <sys/msg.h> // msgsnd, msgrcv, IPC_CREAT
#include <string.h>  // strcmp
#include <unistd.h>  // getpid
#include <stdlib.h>  // exit, EXIT_FAILURE

#define KEYPATH "./server.c"
#define PROJ_ID '1'
#define NPLAYER 4
#define MSG_LEN 20

#define MTYPE_REQ 'a'
#define MTYPE_SRV 'b'

#define MSG_PRIJAVA "prijava"
#define MSG_POJEDEN "pojeden"
#define MSG_ZAVRSIO "kraj"


typedef struct
{
	long mtype;
	char mtext[MSG_LEN+1];
	pid_t pidKlij;
} Poruka;

typedef struct
{
	long mtype;
	int dobijenBroj;
} Potez;

int main()
{
	pid_t myPid;
	key_t key;
	int queid;
	int kockica;
	char buff[MSG_LEN+1];
	
	Poruka p;
	Potez pot;

	myPid = getpid();
	printf("PID klijenta: %d\n\n", myPid );
	
	key = ftok( KEYPATH, PROJ_ID );
	queid = msgget( key, IPC_CREAT | 0666 );

	/* posalji zahtev za prijavu */
	p.mtype = MTYPE_REQ;
	p.pidKlij = myPid;
	strcpy( p.mtext, MSG_PRIJAVA );
	msgsnd( queid, &p, sizeof(p), 0 );

	while(1)
	{
		/* sacekaj svoj red */
		msgrcv( queid, &p, sizeof(p), myPid, 0 );
		//printf("test$$$\n");
		strcpy( buff, p.mtext );
		//printf("test %s\n", buff);
		
		if( !strcmp( buff , MSG_POJEDEN ) || !strcmp( buff , MSG_ZAVRSIO ) )
		{
			printf(" --> Server: zavrsio si sa igrom\n");
			return 0;
		}
		printf(" --> Server: ti si na potezu\n");
	
		/* simuliraj bacanje kockice */
		do
		{
			printf("\n### Simulacija kockice ###\n");
			printf("Unesi broj(1-6):\n");
			scanf("%d", &kockica );
			getchar();
		} while( kockica < 1 || kockica > 6 );

		/* posalji svoj potez serveru */
		pot.mtype = MTYPE_SRV;
		pot.dobijenBroj = kockica;
		msgsnd( queid, &pot, sizeof(Potez), 0 );
		printf(" <-- Broj %d je poslat\n", kockica );
		printf("Cekam svoj red...\n\n");
	} 
	
}
