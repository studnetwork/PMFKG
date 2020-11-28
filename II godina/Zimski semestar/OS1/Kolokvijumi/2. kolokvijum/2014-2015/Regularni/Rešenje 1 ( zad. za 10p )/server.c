#include <stdio.h>
#include <sys/ipc.h> // ftok, key_t, pid_t
#include <sys/msg.h> // msgsnd, msgrcv, IPC_CREAT, msgctl, IPC_RMID
#include <string.h>  // strcmp
#include <unistd.h>  // getpid
#include <stdlib.h>  // exit, EXIT_FAILURE

#define KEYPATH "./server.c"
#define PROJ_ID '1'
#define NPLAYER 4
#define MTYPE_REQ 'a'
#define MTYPE_SRV 'b'
#define MSG_LEN 20

#define MSG_PRIJAVA "prijava"
#define MSG_IGRAJOS "igra"
#define MSG_POJEDEN "pojeden"
#define MSG_ZAVRSIO "kraj"
#define MSG_NA_REDU "tvoj je red"

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

typedef struct
{
	pid_t pid;
	int pozicija;
	int rezultat;
} Igrac;

int main()
{
	/* ne sme se menjati nakon inicijalizacije */
	const int kraj = 10;
	
	key_t key;
	//pid_t pids[NPLAYER];
	int i, j;
	int queid;
	int naKraju;
	int zavrsilo;

	Poruka p;
	Potez po;
	Igrac igraci[NPLAYER];

	naKraju = 0;
	zavrsilo = 0;

	key = ftok( KEYPATH, PROJ_ID );
	queid = msgget( key, IPC_CREAT | 0666 );

	printf("Cekam zahteve za prijavu klijenata...\n");
	for(i = 0; i < NPLAYER; i++)
	{
		msgrcv( queid, &p, sizeof(p), MTYPE_REQ, 0 );
		if( strcmp( p.mtext, MSG_PRIJAVA ) )
		{
			printf("Klijent nije poslao ispravan zahtev\n");
			exit(EXIT_FAILURE);
		}
		igraci[i].pid = p.pidKlij;
		igraci[i].rezultat = 0; /* inicijalizacija; 0 oznacava da jos nije zavrsio */
		igraci[i].pozicija = 0;
		printf("Prijavljen #%d\n", igraci[i].pid );
	}

	/* prvi igrac zapocinje igru;
	 * potrebno je da se resetuje
	 * jer je promenljiva vec koriscena */
	i = 0;
	while( zavrsilo < NPLAYER )
	{
		/* kad zavrsi poslednji,
		 * neka prvi dodje na red */
		i %= NPLAYER;
		
		/* ako je trenutni igrac zavrsio
		 * predji na sledeceg*/
		if( igraci[i].rezultat != 0 )
		{
			i++;
			continue;
		}
		
		/* obavesti klijenta da je on na potezu */
		p.mtype = igraci[i].pid;
		strcpy( p.mtext, MSG_NA_REDU );
		msgsnd( queid, &p, sizeof(p), 0 );
		printf(" <-- Obavesti #%d da je na potezu\n", igraci[i].pid );

		/* primi poruku klijenta o njegovom dobijenom broju */
		msgrcv( queid, &po, sizeof(Potez), MTYPE_SRV, 0 );
		printf(" --> #%d je dobio broj %d\n\n", igraci[i].pid, po.dobijenBroj );
		igraci[i].pozicija += po.dobijenBroj;
		printf(" #%d pozicija je %d\n", igraci[i].pid, igraci[i].pozicija );
		if( igraci[i].pozicija >= kraj )
		{
			igraci[i].rezultat = ++naKraju;
			p.mtype = igraci[i].pid;
			strcpy( p.mtext, MSG_ZAVRSIO );
			msgsnd( queid, &p, sizeof(p), 0 );
			
			zavrsilo++;

			i++;
			
			/* ako je stigao na kraj nema potreba da
			 * proverava da li je nekoga pojeo      */
			continue;
		}

		/* proveri da li je neki igrac pojeden */
		for(j = 0; j < NPLAYER; j++)
		{
			/* proveri da li je igrac vec izbacen;
			 * ne sme da se ispituje jedan te isti
			 * igrac*/
			if( i != j && igraci[j].rezultat == 0  )
			{
				/* proveri da li ce igrac i pojesti igraca j */
				if( igraci[i].pozicija == igraci[j].pozicija )
				{
					/* -1 oznacava da je dati igrac pojeden */
					igraci[j].rezultat = -1; 
					
					p.mtype = igraci[j].pid;
					strcpy( p.mtext, MSG_POJEDEN );
					msgsnd( queid, &p, sizeof(p), 0 );
					
					zavrsilo++;

					/* nema potreba za daljom proverom jer
					 * se samo jedan igrac moze naci na
					 * jednom polju                        */
					break;
				}
			}
		}

		/* daj pravo na potez narednom igracu*/
		i++;
	}

	for(i = 0; i < NPLAYER; i++)
	{
		if( igraci[i].rezultat == -1 )
			printf("#%d je ispao\n", igraci[i].pid );
		else
			printf("#%d stigao je kao %d.\n", igraci[i].pid, igraci[i].rezultat );
	}

	/* oslobodi zauzete resurse, tj.
	 * napravljeni red za poruke*/
	msgctl( queid, IPC_RMID, NULL );
}
