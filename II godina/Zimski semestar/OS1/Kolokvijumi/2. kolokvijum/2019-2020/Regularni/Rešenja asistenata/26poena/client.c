#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>
#include <errno.h>

int msgid;
int semid;

typedef struct card
{
    int card;   // Karta
    int col;    // Boja
} Card;

typedef struct data
{
    int card;
    int col;
    int way;    // 1 default | -1 reverse
} Data;

typedef union semun
{
    int val;
    struct semid_ds *buf;
    ushort *array;
} Semun;

typedef struct msg
{
    long type;
    int partija;
    long broj;
} Msg;

void signal_handler(int id)
{
    printf("Deleting semaphores\n");
    int i;
    for(i=0; i<4; i++)
    {
        semctl(semid, i, IPC_RMID);
    }
    msgctl(msgid, IPC_RMID, NULL);
    exit(0);
}

int main()
{
    key_t key1 = ftok("server.c", 0);
    int msgid = msgget(key1, IPC_CREAT|0666);
    printf("Client starting : %d\n", getpid());
    Msg msg;
    msg.type = 1;
    msg.broj = getpid();
    msgsnd(msgid, &msg, sizeof(msg), 0);
    printf("Waiting for reply\n");
    msgrcv(msgid, &msg, sizeof(msg), 2, 0);
    printf("Match starting : %d\n", msg.partija);

    // Actual game
    signal(SIGINT, signal_handler);
    key_t key = ftok("server.c", msg.partija);
    int shmid = shmget(key, sizeof(Data), 0666|IPC_CREAT);
    semid = semget(key, 4, 0666|IPC_CREAT|IPC_EXCL);
    Semun arg;
    struct sembuf sem_op_inc;
    struct sembuf sem_op_dec;
    arg.val = 0;
    if(semid != -1) // Just created
    {
        arg.val = 1;
        semctl(semid, 0, SETVAL, arg);
        arg.val = 0;
        semctl(semid, 1, SETVAL, arg);
        semctl(semid, 2, SETVAL, arg);
        semctl(semid, 3, SETVAL, arg);
    }
    else
    {
        semid = semget(key, 4, 0);
    }
    int MYSEM = msg.broj;
    //printf("shmid : %d | semid : %d\n", shmid, semid);
    Data *data;
    data = shmat(shmid, NULL, 0);

    sem_op_dec.sem_num = MYSEM;
    sem_op_dec.sem_op = -1;
    sem_op_dec.sem_flg = 0;

    sem_op_inc.sem_op = 1;
    sem_op_inc.sem_flg = 0;
    if(MYSEM == 0)
    {
        data->card = rand()%14;
        data->col = rand()%4;
        if(data->card == 8) 
            data->way = -1;
        else 
            data->way = 1;
        //Dodat kao deo za sinhronizaciju
		sem_op_inc.sem_num = 1;
		semop(semid,&sem_op_inc,1);
		sem_op_inc.sem_num = 2;
		semop(semid,&sem_op_inc,1);
		sem_op_inc.sem_num = 3;
		semop(semid,&sem_op_inc,1);
	}
    else
    {
        //Deo za sinhronizaciju
		//Ne moze proces proces 1, 2 i 3 da prodju dalje dok nije generisan data
        semop(semid, &sem_op_dec, 1); 
    }
    
    printf("Starting data : %d|%d|%d\n", data->card, data->col, data->way);
    Card myCard;

    int i;
    while(1)
    {
        srand(time(NULL));
        semop(semid, &sem_op_dec, 1);   // Kontrola da li je na potezu
        sleep(2);
        myCard.card = rand()%14;
        myCard.col = rand()%4;
        if(data->card == myCard.card || data->col == myCard.col)
        {
            printf("Izbacujem (%d|%d) na (%d|%d)\n", myCard.card, myCard.col, data->card, data->col);
            data->card = myCard.card;
            data->col = myCard.col;
            if(data->card == 8) data->way *= -1;
        }
        else
        {
            printf("Nemam adekvatnu kartu (%d|%d) na (%d|%d)\n", myCard.card, myCard.col, data->card, data->col);
        }

        if(data->way == 1)
        {
            if(MYSEM == 3) sem_op_inc.sem_num = 0;
            else sem_op_inc.sem_num = MYSEM+1;
            printf("--> Sledeci na potezu : %d\n", sem_op_inc.sem_num);
            semop(semid, &sem_op_inc, 1);
        }
        else if(data->way == -1)
        {
            if(MYSEM == 0) sem_op_inc.sem_num = 3;
            else sem_op_inc.sem_num = MYSEM-1;
            printf("<-- Sledeci na potezu : %d\n", sem_op_inc.sem_num);
            semop(semid, &sem_op_inc, 1);
        }
        
        sleep(2);
    }

    shmdt(data);
    return 0;
}