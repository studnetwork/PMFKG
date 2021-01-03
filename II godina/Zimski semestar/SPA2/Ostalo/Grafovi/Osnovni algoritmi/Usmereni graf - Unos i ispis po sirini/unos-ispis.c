#include <stdio.h>
#include <stdlib.h>

// za matricu povezanosti
#define VEZA 1 
#define BEZ_VEZE 0

// pise se umesto id-a elementa tamo gde treba naznaciti ne postojanje elementa
#define NE_ELEMENT -1


// Element pomocni red (listu) potrebnog za pretragu po sirini
typedef struct _Node {
    int id;
    struct _Node *next;
} Node;


// Dodavanje novog elementa u red
void Dodaj(Node **pHead, int id)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->id = id;
    newNode->next = NULL;

    if(*pHead == NULL)
    {
        *pHead = newNode;
        return;
    }

    Node *p = *pHead;
    while (p->next != NULL)
        p = p->next;
    
    p->next = newNode;
}

// Uzimanje elementa sa pocetka reda
int Uzmi(Node **pHead)
{
    int x;

    if(*pHead == NULL)
        return NE_ELEMENT;

    x = (*pHead)->id;

    Node *next = (*pHead)->next;
    free(*pHead);
    *pHead = next;

    return x;
}


int main()
{
    int n, m; // n - broj elemenata u grafu, m - broj veza u grafu
    int i, j, v1, v2; // pomocne promenljive

    // Unos broja elemenata grafa
    scanf("%d", &n);

    // Alokacija memorije za graf (matricu povezanosti)
    int **graf = (int**)malloc(sizeof(int*) * n);
    for(i = 0; i < n; i++)
        graf[i] = (int*)malloc(sizeof(int) * n);

    // Unos broja veza grafa
    scanf("%d", &m);
    
    // Popunjavanje grafa (matrice povezanosti)
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            graf[i][j] = BEZ_VEZE;
            
    for(i = 0; i < m; i++) {
        scanf("%d%d", &v1, &v2);
        graf[v1][v2] = VEZA;
    }

    // --- Ispis svih elemenata grafa (po sirini), pocevsi od elementa s --- //
    int s, c; // s (start) - pocetni element, c (current) - trenutni element
    scanf("%d", &s);

    Node *red = NULL; // red za cekanje na ispis
    Dodaj(&red, s); // krece se ispis od elementa s

    int *d = (int*)malloc(sizeof(int) * n); // udaljenost svakog elementa od elementa s (d - dubina, valjda???)
    int *p = (int*)malloc(sizeof(int) * n); // prethodnik svakog elementa na putu od s do njega (p - parent)
    int *nb = (int*)malloc(sizeof(int) * n);; // nb - nije bio (1 ako element nije bio u redu za cekanje, u suprotnom 0) (to je onaj niz color, gde boja moze da bude siva (0) ili bela (1))

    // inicijalizacija ova dva niza
    for(i = 0; i < n; i++) {
        d[i] = -1; // jos se ne zna ko je koliko udaljen od s
        p[i] = NE_ELEMENT; // jos se ne zna ko je kome prethodnik
        nb[i] = 1; // zna se da ni jedan element jos nije bio u redu za cekanje
    }
    d[s] = 0; // ali se za element s zna koliko je udaljen sam od sebe (0)
    p[s] = NE_ELEMENT; // kao i da nema prethodnika
    nb[s] = 0; // 0 jer je s dodat na red

    int td = -1; // td - trenutna dubina (sluzi samo da se zna kad treba da se odstampa \n, svaki sloj u novom redu, lepse izgleda)
    while((c = Uzmi(&red)) != NE_ELEMENT) // ja sam c (prvi u redu), treba da se odstampam i da susedne elemente ubacim u red
    {
        // stampanje
        if(td < d[c]) printf("\n%d> ", ++td); // ako sam prvi iz tog sloja onda prelazim u novi red
        printf("%d ", c); // stampam se
        
        // ubacivanje susednih elemenata u red
        for(i = 0; i < n; i++) // prolazak kroz sve veze koje krecu od mene (c) a prema ostalim elementima (i) (ukljucujuci i mene gde je i==c)
            if(graf[c][i] && nb[i]) { // provera da li posoji veza, i da li je taj element (i) vec bio u redu
                d[i] = d[c] + 1; // ovaj susedni (i) je od pocetka (s) udaljeniji za samo 1 u odnosu na mene (c)
                p[i] = c; // tom susednom (i) sam ja prethodnik (c)
                Dodaj(&red, i); // posle ce taj moj susedni element (i) da se stampa, jer se sad dodaje na red za cekanje
                nb[i] = 0; // ubacen je u red, tako da je netacno da nije bio u redu, pa se stavlja 0 (jer sad je u redu)
            }
    }

    printf("\n");
}



/* Author: dr460r */