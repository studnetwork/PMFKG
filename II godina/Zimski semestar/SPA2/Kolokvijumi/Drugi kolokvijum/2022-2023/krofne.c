#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define INF -1

typedef struct {
    int x;
    int y;
} Tacka;

typedef struct Stek {
    Tacka tacka;
    struct Stek *sledeci;
} Stek;

void push(Stek **stek, Tacka tacka) {
    Stek *novi = (Stek *) malloc(sizeof(Stek));
    novi->sledeci = NULL;
    novi->tacka = tacka;

    if (*stek == NULL)
        *stek = novi;
    else {
        Stek *pom = *stek;

        while (pom->sledeci)
            pom = pom->sledeci;

        pom->sledeci = novi;
    }
}

int pop(Stek **stek, Tacka *tacka) {
    if (*stek == NULL)
        return FALSE;

    *tacka = (*stek)->tacka;

    if ((*stek)->sledeci == NULL) {
        free(*stek);
        *stek = NULL;
    } else {
        Stek *pom = (*stek)->sledeci;
        free(*stek);
        *stek = pom;
    }

    return TRUE;
}

int main() {
    int n, m;

    scanf("%d%d", &n, &m);

    getchar();

    char **lavirint = (char **) malloc(sizeof(char *) * n);
    int **poseceni = (int **) malloc(sizeof(int *) * n);
    Tacka **prethodnici = (Tacka **) malloc(sizeof(Tacka *) * n);
    int **rastojanja = (int **) malloc(sizeof(int *) * n);

    for (int i = 0; i < n; i++) {
        lavirint[i] = (char *) malloc(sizeof(char) * m);
        poseceni[i] = (int *) malloc(sizeof(int) * m);
        prethodnici[i] = (Tacka *) malloc(sizeof(Tacka) * m);
        rastojanja[i] = (int *) malloc(sizeof(int) * m);

        for (int j = 0; j < m; j++) {
            poseceni[i][j] = FALSE;
            prethodnici[i][j].x = prethodnici[i][j].y = INF;
            rastojanja[i][j] = INF;
        }
    }

    Tacka pocetna;

    Tacka *krofne = (Tacka *) malloc(sizeof(Tacka) * n * m);
    int krofne_len = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char polje = getchar();

            if (polje == 'G') {
                pocetna.x = i;
                pocetna.y = j;
            }

            if (polje == 'o') {
                krofne[krofne_len].x = i;
                krofne[krofne_len++].y = j;
            }

            lavirint[i][j] = polje;
        }

        getchar();
    }

    poseceni[pocetna.x][pocetna.y] = TRUE;
    rastojanja[pocetna.x][pocetna.y] = 0;

    Stek *stek = NULL;

    push(&stek, pocetna);

    Tacka trenutna; // bfs
    while (pop(&stek, &trenutna)) {
        if (trenutna.x - 1 >= 0 && poseceni[trenutna.x - 1][trenutna.y] == FALSE && lavirint[trenutna.x - 1][trenutna.y] != 'X') { // Idemo gore
            poseceni[trenutna.x - 1][trenutna.y] = TRUE;
            rastojanja[trenutna.x - 1][trenutna.y] = rastojanja[trenutna.x][trenutna.y] + 1;
            prethodnici[trenutna.x - 1][trenutna.y] = trenutna;

            Tacka nova;
            nova.x = trenutna.x - 1;
            nova.y = trenutna.y;

            push(&stek, nova);
        }

        if (trenutna.x + 1 < n && poseceni[trenutna.x + 1][trenutna.y] == FALSE && lavirint[trenutna.x + 1][trenutna.y] != 'X') { // Dole
            poseceni[trenutna.x + 1][trenutna.y] = TRUE;
            rastojanja[trenutna.x + 1][trenutna.y] = rastojanja[trenutna.x][trenutna.y] + 1;
            prethodnici[trenutna.x + 1][trenutna.y] = trenutna;

            Tacka nova;
            nova.x = trenutna.x + 1;
            nova.y = trenutna.y;

            push(&stek, nova);
        }

        if (trenutna.y - 1 >= 0 && poseceni[trenutna.x][trenutna.y - 1] == FALSE && lavirint[trenutna.x][trenutna.y - 1] != 'X') { // Levo
            poseceni[trenutna.x][trenutna.y - 1] = TRUE;
            rastojanja[trenutna.x][trenutna.y - 1] = rastojanja[trenutna.x][trenutna.y] + 1;
            prethodnici[trenutna.x][trenutna.y - 1] = trenutna;

            Tacka nova;
            nova.x = trenutna.x;
            nova.y = trenutna.y - 1;

            push(&stek, nova);
        }

        if (trenutna.y + 1 < m && poseceni[trenutna.x][trenutna.y + 1] == FALSE && lavirint[trenutna.x][trenutna.y + 1] != 'X') { // Desno
            poseceni[trenutna.x][trenutna.y + 1] = TRUE;
            rastojanja[trenutna.x][trenutna.y + 1] = rastojanja[trenutna.x][trenutna.y] + 1;
            prethodnici[trenutna.x][trenutna.y + 1] = trenutna;


            Tacka nova;
            nova.x = trenutna.x;
            nova.y = trenutna.y + 1;

            push(&stek, nova);
        }
    }

    int pojedeno_krofni = 0;
    int maks_rastojanje = INF;
    for (int i = 0; i < krofne_len; i++) {
        int x = krofne[i].x;
        int y = krofne[i].y;

        if (rastojanja[x][y] != INF) {
            pojedeno_krofni += 1;

            if (rastojanja[x][y] > maks_rastojanje)
                maks_rastojanje = rastojanja[x][y];
        }
    }

    printf("%d %d\n", pojedeno_krofni, maks_rastojanje);

    return 0;
}
