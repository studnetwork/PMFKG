#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

union semun {
    int val; // vrednost koja se dodeljuje           
    struct semid_ds *buf; // bufer za IPC_STAT, IPC_SET, nismo i necemo koristiti
    unsigned short *array; // niz vrednosti koji se koristi ukoliko se zahteva SETALL umesto SET (nad pojedinacnim semaforom)
    // ili niz objekata u koji ce se smestiti vrednosti svih semafora koriscenjem GETALL
};

int brojUdaraca = 0;

void signal_handler(int sig) {
    printf("Kraj... udario sam lopticu %d puta\n", brojUdaraca);
    exit(0);
}

int main() {

    signal(SIGINT, signal_handler);

    key_t key = ftok("./ping.c", 'a');
    if (key == -1) {
        perror("Ne mogu da sastavim jedinstven kljuc");
        exit(1);
    }

    int smgflg = 0666 | IPC_CREAT | IPC_EXCL;
    int semid = semget(key, 2, smgflg); // pravljenje dva semafora uz odredjene permisije
    // man semget objasnjava koriscenje IPC_CREAT i IPC_EXCL makroa zajedno
    
    if (semid != -1) { // semafor nije bio kreiran, ja sam ga kreirao
        union semun init_operacija;

		init_operacija.val = 1;
		semctl(semid, 0, SETVAL, init_operacija); // postavljanje vrednosti prvog (0-og) semafora na 1

        init_operacija.val = 0;
		semctl(semid, 1, SETVAL, init_operacija); //postavljanje vrednosti drugog semafora na 0

        // SETVAL, setuje vrednost val promenljive (iz unije semun) za odredjeni semafor
        // SETALL, respektivno setuje vrednosti iz array niza za sve semafore iz tog skupa (npr. array {3, 5} -> prvi sem = 3, drugi sem = 5)
        // GET, dohvata vrednost odredjenog semafora i smesta je u val promenljivu (iz unije semun)
        // GETALL, dohvata vrednosti svih semafora iz tog skupa i smesta ih u promenljivu array
    } else if (errno == EEXIST) { // greska se dogodila, uzrok greske jeste postojanje semafora
		// printf("Semafor je kreirao i inicijalizovao neko drugi, ja se samo povezujem \n");
		semid = semget(key, 2, 0); // semflg je skroz nebitan ovde
    } else { // ukoliko je semid = -1, a neki drugi errno
		printf("Neka druga greska! Izlazim .. \n");
		exit(1);
	}

    struct sembuf opr_povecaj, opr_smanji; // operacije za rad nad semaforom

    opr_smanji.sem_num = 0;
    opr_smanji.sem_op = -1; // nad semaforom 0, odradi -1
    opr_smanji.sem_flg = 0; // ukoliko je nula, onda je blokirajuce stanje, isto kao za redove za poruke, i ovde moze biti IPC_NOWAIT

    opr_povecaj.sem_num = 1;
    opr_povecaj.sem_op = 1; // nad semaforom 1, odradi +1
    opr_povecaj.sem_flg = 0;

    // na pocetku je stanje 0-og semafora [1], a 1-og [0]
    int status;
    while (1) {
        status  = semop(semid, &opr_smanji, 1); // nad skupom semafora semid, odradi operaciju umanjenja
        // to jest cekaj (jer je sem_flg 0) sve dok ne mozes da skines/umanjis za 1

		if (status == -1) {
            perror("greska se dogodila");
            exit(1);

            // moze i break
        }

        printf("ping\n");
        brojUdaraca++;
        sleep(3);

        // po izlasku iz kriticnog regiona, povecaj vrednost prvog semafora (tren [0]) na [1]
        // kako bi drugi proces (pong.c) mogao da udje u kriticni region umanjenjem tog semafora za 1
        status  = semop(semid, &opr_povecaj, 1); // nad skupom semafora semid, odradi operaciju uvecanja
        // parametar 1 oznacava da nad skupom semafora semid treba da se odradi 1 komanda, posto je 
        // drugi parametar pokazivac na niz komandi, u ovom slucaju na samo jednu

        if (status == -1) {
            perror("greska se dogodila");
            exit(1);

            // moze i break
        }
    }

    return 0;
}