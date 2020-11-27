#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <time.h>
#include <stdlib.h>

pid_t pid;

void shChild( int sig )
{
	printf("Prekid nije moguc, signal: %d\n", sig);
}

void shParent( int sig )
{
	kill( pid, SIGKILL );
}

int main()
{
		int n, i;
		scanf("%d", &n );

		srand(time(NULL));

		pid = fork();
		if( pid == 0 )
		{
			signal( SIGINT, shChild );
			for(i = 1; i < n; i+=2)
			{
				printf("C:%d\n", i);
				sleep(rand() % 5);
			}
		}
		else
		{
			signal( SIGINT, shParent );
			for(i = 2; i < n; i+=2)
			{
				printf("P:%d\n", i);
				sleep(rand() % 5);
			}
			wait(NULL);
			
			signal( SIGINT, SIG_IGN );
		}
}
