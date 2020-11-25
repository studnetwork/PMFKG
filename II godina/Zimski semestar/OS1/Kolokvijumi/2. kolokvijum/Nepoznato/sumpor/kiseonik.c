#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

void proveri(int povratnaVrednost)
{
	if(povratnaVrednost == -1)
	{
		perror("GRESKA");
		exit(1);
	}
}

int main()
{
	key_t kljuc = ftok("./vodonik.c", 'a');
	
	int semid = semget(kljuc, 4, 0666 | IPC_CREAT);
	int semnum = 4;
	
    if (semid == -1) {
        if (errno == EEXIST) {
            semid = semget(kljuc, semnum, 0);
        }
        else
        {
			proveri(semid);
		}
    } else {
        union semun init_sem;
        init_sem.array = (unsigned short*)malloc(semnum * sizeof(unsigned short));

        init_sem.array[0] = 2; // sem za vodonik
        init_sem.array[1] = 0; // sem za sumpor
        init_sem.array[2] = 0; // sem za kiseonik
        init_sem.array[3] = 0; // sem za molekul

        int rv = semctl(semid, 0, SETALL, init_sem);
        proveri(rv);
    }
	
	struct sembuf opr_dec, opr_inc;
	
	opr_dec.sem_num = 2;
	opr_dec.sem_op = -1;
	opr_dec.sem_flg = 0;
	
	opr_inc.sem_num = 3;
	opr_inc.sem_op =  1;
	opr_inc.sem_flg = 0;
	

		
	while(1)
	{
		
		semop(semid, &opr_dec, 4);
		
		
		printf("Pravim atomy...\n");
		sleep(5);
		
		
		semop(semid, &opr_inc, 1);
		
		printf("Kreirano 4 atoma kiseonika!\n");
	}
	
	
	return 0;
}


