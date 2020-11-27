/* U ovom header-u se nalaze macro-i i strukture
 * koje koriste programi "server.c" i "klijent.c"             */

/* maksimalan broj klijenata koji se moze registrovati        */
#define MAX_KLIJ 20

/* putanje ka fajlovima koje se koriste za generisanje kljuca */
#define FPATH_SRV "./server.c"
#define FPATH_KLIJ "./klijent.c"

/* ID-jevi projekata koji se koriste za generisanje kljuca;
 * predstavljaju drugi argument funkcije msgget()             */
#define ID_PROJ1 '1'
#define ID_PROJ2 '2'

/* maksimalna duzina korisnickog imena                        */
#define KORIME_LEN 20

/* maksimalna duzina teksta poruke                            */
#define MSGTEXT_LEN  40

/* tipovi poruke                                              */
#define MTYPE_ZAHT 'a' // predstavlja klijent-server poruku
#define MTYPE_ODGO 'b' // predstavlja server-klijent poruku

typedef struct
{
	long mtype;
	char korIme[KORIME_LEN];
} Zahtev;

typedef struct
{
	long mtype;
	char a[1];
	int id_klij;
	int poslednji;
} Odgovor;

typedef struct
{
	long mtype;
	char sadrzaj[MSGTEXT_LEN];
} Poruka;
 
