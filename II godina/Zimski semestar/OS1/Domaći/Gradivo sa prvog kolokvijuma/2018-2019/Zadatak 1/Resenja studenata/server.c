#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#define MAX_LEN 30
#define MSGSZ( struktura ) ( sizeof( (struktura) ) - sizeof( (struktura).mtype ) )
#define MTYPE_SERVER 1

typedef struct
{
	long mtype;
	char mtext[MAX_LEN];
	pid_t pidKlijenta;
} poruka;

int main()
{
	int i, qid, len;
	key_t key;
	poruka p;

	key = ftok( "./server.c", 'a' );
	qid = msgget( key, IPC_CREAT | 0660 );

	printf("Cekam prouke...\n");
	while(1)
	{
		/* primi poruku od klijenta */
		msgrcv( qid, &p, MSGSZ(p), MTYPE_SERVER, 0 );

		printf("Primio sam poruku: %s\n", p.mtext );

		/* proveri da li je potrebno prekinuti izvrsavanje programa */
		if( !strcmp( p.mtext, "dosta" ) )
		{
			printf("Klijent je poslao rec \"dosta\"\n");
			printf("Prekida se izvrsavanje programa.\n");

			exit(EXIT_SUCCESS);
		}

		/* pretvori u uppercase */
		len = strlen( p.mtext );
		for(i = 0; i < len; i++)
		{
			/* proveri da li je lowercase slovo */
			if( p.mtext[i] >= 'a' && p.mtext[i] <= 'z' )
				p.mtext[i] += 'A' - 'a' ; 
		}

		printf("Primljena poruka pretvorena u uppercase: %s\n", p.mtext );

		/* posalji klijentu nazad poruku u uppercase-u */
		p.mtype = p.pidKlijenta;
		msgsnd( qid, &p, MSGSZ(p), 0 );
		printf("Uppercase poruka je poslata nazad klijentu\n\n");
	}
}
