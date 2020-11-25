#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024

int main()
{
	key_t kljuc;
	int id_memorije;
	char *data;
	char poruka[SHM_SIZE];
	
	
	//pravi kljyc
	kljuc = ftok("./deljenaMermorija1.c", 32);
	printf("Kljuc je:%d\n", kljuc);
	
	//povezuje se (i ako je moguce kreira) segment 
	id_memorije = shmget(kljuc, SHM_SIZE, 0644 | IPC_CREAT);
	
	printf("ID segmenta je %d\n", id_memorije);
	
	data = shmat(id_memorije, NULL, 0);
	
	//ucitava poryky
	printf("Ucitaj poruku\n");
	fgets(poruka, SHM_SIZE, stdin);
	strcpy(data, poruka);
	
	//sleep(20);
	
	//odvaja se od segmenta
	
	shmdt(data);
	
	return 0;
}
