#include <stdio.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>
#include "sk.h"

int main()
{
	key_t key_srv, key_chat;
	int qid_srv, qid_chat;
	
	Zahtev z;
	Odgovor o;
	Poruka p;

	/* Unesi podatke za zahtev */
	printf("Unesite korisnicko ime:\n");
	fgets(z.korIme, KORIME_LEN, stdin );
	z.korIme[strlen(z.korIme)-1] = '\0';
	z.mtype = MTYPE_ZAHT;

	/* kreiranje kljuca i reda za kom. sa serverom */
	key_srv = ftok( FPATH_SRV, ID_PROJ1 );
	qid_srv = msgget( key_srv, IPC_CREAT | 0666 );

	/* salje zahtev serveru za prijavu */
	msgsnd( qid_srv, (void const *)&z, sizeof(z.korIme), 0 );

	/* prima odgovor servera na zahtev za prijavu */
	msgrcv( qid_srv, (void *)&o, sizeof(o)-sizeof(long), MTYPE_ODGO,0 );
	printf("Primljen odgovor servera. Moj ID je: %d\n", o.id_klij );
	
	/* kreiranje kljuca i reda kom. sa drugim klijentom */
	key_chat = ftok( FPATH_KLIJ, ID_PROJ2 );
	qid_chat = msgget( key_chat, IPC_CREAT | 0666 );

	/* komunikacija izmedju dva klijenta */
	if( o.id_klij % 2 )
	{
		/* ucitaj poruku koja ce se poslati drugom klijentu */
		printf("Unesi poruku koja ce se poslati drugom klijentu:\n");
		fgets( p.sadrzaj, MSGTEXT_LEN, stdin );
		p.mtype = o.id_klij+1;
		p.sadrzaj[strlen(p.sadrzaj)-1] = '\0';

		/* posalji poruku */
		msgsnd( qid_chat, (void const *)&p, sizeof(p)-sizeof(long), 0 );

		/* primi odgovor na poslatu poruku */
		msgrcv( qid_chat, (void *)&p, sizeof(p)-sizeof(long), o.id_klij, 0 );
		printf("Odgovor drugog klijenta na poslatu poruku:\n");
		printf("\"%s\"\n", p.sadrzaj);

	}
	else
	{
		/* primi poruku */
		printf("Cekam poruku...\n");
		msgrcv( qid_chat, (void *)&p, sizeof(p)-sizeof(long), o.id_klij, 0 );
		printf("Primljena poruka: \"%s\"\n", p.sadrzaj);

		/* ucitaj poruku koja ce se poslati drugom klijentu */
		printf("Unesi odgovor:\n");
		fgets( p.sadrzaj, MSGTEXT_LEN, stdin );
		p.mtype = o.id_klij-1;
		p.sadrzaj[strlen(p.sadrzaj)-1] = '\0';

		/* posalji odgovor primljenu poruku */
		msgsnd( qid_chat, (void const *)&p, sizeof(p)-sizeof(long), 0 );
		printf("Odgovor je poslat\n");
	}


	/* ako je klijent poslednji registrovani klijent onda on brise red */
	if( o.poslednji )
	{
		msgctl( qid_chat, IPC_RMID, NULL );
		printf("Red (%d) za medjusobnu komunikaciju klijenata je obrisan\n", qid_chat );
	}
}
