#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include "sk.h"

int main()
{
	key_t key;
	ssize_t rcvRtn;
	int broj_klijenata;
	int qid;
	int broj_prijava = 0;
	Zahtev z;
	Odgovor o;

	int pom;
	do
	{
		printf("Unesite (paran) broj klijenata:\n");
		pom = scanf("%d", &broj_klijenata);
	}while( pom==0 || broj_klijenata % 2 == 1 || broj_klijenata > MAX_KLIJ );

	/* kreiraj red za komunikaciju server-klijent */
	key = ftok( FPATH_SRV, ID_PROJ1 );
	qid = msgget( key, IPC_CREAT | 0666 );

	printf("Cekam zahteve korisnika...\n");
	
	/* radi sve dok se ne registruje n klijenata */
	while( broj_prijava < broj_klijenata )
	{
		/* primi prijave */
		rcvRtn = msgrcv( qid, (void *)&z, sizeof(z.korIme), MTYPE_ZAHT, 0 );
		if( rcvRtn <= 0 )
		{
			printf("doslo je do greske tokom cekanja zahteva\n");
			exit(EXIT_FAILURE);
		}
		broj_prijava++;

		/* obavesti klijenta o uspesnoj registraciji i posalji njegov id */
		o.mtype = MTYPE_ODGO;
		o.id_klij = broj_prijava;
		o.poslednji = broj_prijava == broj_klijenata;
		msgsnd( qid, (void const *)&o, sizeof(o)-sizeof(long), 0 );

		printf("\nRegistrovan klijent sa korisnickim imenom:\n");
		printf("%s\n\n", z.korIme );
	}

	/* brisi red za komunikaciju server-klijent */
	msgctl( qid, IPC_RMID, NULL);
	printf("Red (%d) je obrisan\n", qid	);
}
