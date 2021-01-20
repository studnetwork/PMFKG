#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>

#define MSGSZ( struktura ) ( sizeof( (struktura) ) - sizeof( (struktura).mtype ) )

typedef struct
{
	long mtype;
	pid_t pid;
} poruka;

int main()
{
	int qid ;
	key_t key;
	pid_t pid;
	poruka p;

	pid = getpid();
	
	key = ftok( "./brod.c", 'a' );
	qid = msgget( key, IPC_CREAT | 0660 );

	/* prijavi se za prevoz */
	p.mtype = 'm';
	p.pid = pid;
	msgsnd( qid, &p, MSGSZ(p), 0 );

	/* primi obavestenje o ukrcavanju na brod */
	msgrcv( qid, &p, MSGSZ(p), pid, 0 );
	printf("Ukrcao sam se na brod.\n");

	/* primi obavestenje o ukrcavanju na brod */
	msgrcv( qid, &p, MSGSZ(p), pid, 0 );
	printf("Stigao sam na desnu stranu.\n");
}
