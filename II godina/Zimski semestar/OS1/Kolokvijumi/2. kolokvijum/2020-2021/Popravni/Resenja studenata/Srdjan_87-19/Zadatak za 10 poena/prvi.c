#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

union semun
{
	int val;
	struct semid_ds *buf;	
	ushort *array;
};

extern errno;

int main()
{
	//printf("Prvi:\n");
	srand( getpid() );
	
	key_t key;
	int semid, randBr, mojaPoz, sledeci;
	
	mojaPoz = 1;
	
	union semun arg;
	struct sembuf p,v;
	
	key = ftok( "./prvi.c", 'a' );
	semid = semget( key, 4, 0666 | IPC_CREAT | IPC_EXCL );
	
	if( semid != -1 )
	{
		arg.val = 1;
		semctl( semid, 0, SETVAL, arg );
		
		arg.val = 0;
		semctl( semid, 1, SETVAL, arg );
		
		arg.val = 0;
		semctl( semid, 2, SETVAL, arg );
		
		arg.val = 0;
		semctl( semid, 3, SETVAL, arg );
	}
	else if( errno == EEXIST )
	{
		semid = semget( key, 4, 0 );
	}
	else
	{
		exit(EXIT_FAILURE);
	}
	
	p.sem_num = 0;
	p.sem_op = -1;
	p.sem_flg = 0;
	
	v.sem_op = 1;
	v.sem_flg = 0;
	
	while(1)
	{
		semop( semid, &p, 1 );
		randBr = rand() % 3 + 1;
		sleep(3);
		
		sledeci = ( mojaPoz + randBr );
		
		if( sledeci > 4 )
			sledeci = sledeci - 4;
		/*printf("rand=%d\n", randBr );
		printf("sledeci=%d\n", sledeci );
		*/
		v.sem_num = sledeci-1;
		semop( semid, &v, 1 );
		
		printf("%d\n", randBr );
	}
}
