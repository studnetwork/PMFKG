#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>

int main()
{
	
	 //  ZA DVA PROCESA
	  pid_t pid;
	
	pid=fork();
	int rv;
	switch(pid)
	{
		case -1:
			perror("Greska pri forkovanju!!!\n");
			exit(0);
		case 0 :
			printf(" D Proces sa PID-om %d : FAZA 1 ZAVRSENA\n",getpid());
			sleep(20);
			printf(" D Proces sa PID-om %d : FAZA 2 ZAVRSENA\n",getpid());
			exit(1);	
		default:
			printf(" R Proces sa PID-om %d : FAZA 1 ZAVRSENA\n",getpid());
			//waitpid(pid,NULL,0);
			sleep(10);
			printf(" R Proces sa PID-om %d : FAZA 2 ZAVRSENA\n",getpid());
	}
	return 0;
	
	//ZA TRI PROCESA
	/*pid_t pid,pid1;
	pid=fork();
	int rv;
	switch(pid)
	{
		case -1:
			perror("Greska pri forkovanju!!!\n");
			exit(0);
		case 0 :
				pid1=fork();
					switch(pid1)
					{
						case -1:
							perror("Greska pri forkovanju!!!\n");
							exit(0);
						case 0 :
							printf(" DD Proces sa PID-om %d : FAZA 1 ZAVRSENA\n",getpid());
							printf(" DD Proces sa PID-om %d : FAZA 2 ZAVRSENA\n",getpid());
							exit(1);	
						default:
							printf(" DR Proces sa PID-om %d : FAZA 1 ZAVRSENA\n",getpid());
							waitpid(pid1,NULL,0);
							printf(" DR Proces sa PID-om %d : FAZA 2 ZAVRSENA\n",getpid());
					}
				exit(0);		
		default:
			printf(" R Proces sa PID-om %d : FAZA 1 ZAVRSENA\n",getpid());
			waitpid(pid,NULL,0);
			printf(" R Proces sa PID-om %d : FAZA 2 ZAVRSENA\n",getpid());
	}*/
}
