#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

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
	int qid;
	key_t key;
	pid_t pid;
	poruka p;

	pid = getpid();

	key = ftok( "./server.c", 'a' );
	qid = msgget( key, IPC_CREAT | 0666 );

	/* ucitaj poruku */
	printf("Unesi poruku:\n");
	fgets( p.mtext, sizeof( p.mtext ), stdin );
	p.mtext[ strlen(p.mtext) - 1 ] = '\0';

	/* posalji ucitanu poruku serveru */
	p.mtype = MTYPE_SERVER;
	p.pidKlijenta = pid;
	msgsnd( qid, &p, MSGSZ(p), 0 );

	/* primi uppercase poruku od servera */
	msgrcv( qid, &p, MSGSZ(p), pid, 0 );

	printf("Primljena poruka: %s\n", p.mtext );
}
