#include <stdio.h>
#include <stdlib.h>

typedef struct _put {
    int bus;
    int voz;
} Put;

#define create(t, n) (t*)malloc(sizeof(t) * (n))

#define INF (-1)
#define NIL (-2)

Put **CreateGraph(int n)
{
    Put **g = create(Put*, n);
    
    int i, j;
    for(i = 0; i < n; i++) {
        g[i] = create(Put, n);
        for(j = 0; j < n; j++)
            g[i][j].bus = g[i][j].voz = INF;

    }

    return g;
}

void LoadGraph(Put **g, int twoDir) // twoDir - da li su svi uneti putevi dvosmerni [0|1]
{
    int n, i, a, b;
    scanf("%d", &n);

    Put w;
    for(i = 0; i < n; i++) {
        scanf("%d%d%d%d", &a, &b, &(w.bus), &(w.voz));
        g[a][b] = w;
        if(twoDir) g[b][a] = w;
    }
}

int AddW(int a, int b) // sabiranje tezina veza (vremena puta izmedju cvorova) (jer mogu biti i beskonacni tako da valja imati posebnu funkciju za to)
{
    if(a == INF || b == INF)
        return INF;
    return a + b;
}

int MinW(int a, int b) // vraca manju od dve poslate tezine puta (vreme) (isti razlog kao i za AddW())
{
    if(a == INF) return b;
    if(b == INF) return a;
    return (a < b)? a : b;
}

// vraca id cvora za koga se trenutno zna da se do njega najbrze stize od polazista
int GetNextMin(int *q, int *d, int n) // q - niz koji sadrzi informacije o tome da li je cvor obradjen [0] ili ne [1], d - distance od polazista, n - broj cvorova
{
    int i, x = 0; // x - id cvora sa najmanjom udaljenoscu od polazista
    while(x < n && !q[x]) x++; // pronalazenje prvog cvora koji nije obradjen

    if(x == n) return NIL; // ako nema neobradjenih cvorova

    for(i = x+1; i < n; i++) // pronalazak neobradjenog cvora sa najmanjom distancom od polazista
        if(q[i] && MinW(d[i], d[x]) == d[i])
            x = i;
    
    q[x] = 0; // sad je taj pronadjeni cvor obradjen
    return x;
}

// relaksacija veze | vp - niz vrsta prevoza (0-bus, 1-voz) iskoriscenih izmedju nekog cvora i njegovog prethodnika na putu od polazista, v - vrsta prevoza koja bi se iskoristila za put od cvora i do j
void Relax(int i, int j, int wij, int *d, int *p, int *vp, int v) // wij - tezina/vreme puta (weight) izmedju i-j
{
    int newD = AddW(d[i], wij); // tezina puta (vreme putovanja) cvora j od polazista preko cvora i
    int oldD = d[j]; // trenutna tezina puta (vremena putovanja) do cvora j od polazista
    if(MinW(newD, oldD) == newD) { // relaksacije veze
        d[j] = newD;
        p[j] = i;
        vp[j] = v; // cuva se preko
    }
}

void Dijkstra(Put **g, int *d, int *p, int *vp, int n, int s) // vp | 0-bus, 1-voz
{
    int i, j, *q = create(int, n);

    // Inicijalizacija
    for(i = 0; i < n; i++) {
        d[i] = INF;
        p[i] = NIL;
        q[i] = 1;
        vp[i] = NIL; // ne zna se koja se vrsta prevoza gde koristila
    }
    d[s] = 0;

    while((i = GetNextMin(q, d, n)) != NIL)
    {
        for(j = 0; j < n; j++)
        {
            int minw = MinW(g[i][j].bus, g[i][j].voz); // nalazi se kojim prevozom se brze stize
            int vrsta = (minw == g[i][j].bus)? 0 : 1; // da li je u pitanju bus ili voz
            if(minw != INF && q[j])
                Relax(i, j, minw, d, p, vp, vrsta); // relaksacija veze
        }
    }
    
}

int main()
{
    Put **g;
    int n, A, B, C;

    scanf("%d", &n);

    g = CreateGraph(n);
    LoadGraph(g, 0);

    scanf("%d%d%d", &A, &B, &C);

    // Pronalazak najkraceg puta
    int *dAB = create(int, n);
    int *pAB = create(int, n);
    int *vAB = create(int, n);
    int *dBC = create(int, n);
    int *pBC = create(int, n);
    int *vBC = create(int, n);

    Dijkstra(g, dAB, pAB, vAB, n, A);
    Dijkstra(g, dBC, pBC, vBC, n, B);

    // Cuvanje pronadjenog puta
    int rn = 0, *r = create(int, n);
    int vn = 0, *v = create(int, n);
    
    // cuvanje dela puta, od B do C
    int i = C;
    while (i != B)
    {
        r[rn] = i;
        v[rn++] = vBC[i];
        i = pBC[i];
    }

    // cuvanje dela puta, od A do B
    while (i != NIL)
    {
        r[rn] = i;
        v[rn++] = vAB[i];
        i = pAB[i];
    }

    // ispis sacuvanog puta
    printf("\n%d -> ", r[rn-1]);
    for(i = rn-2; i > 0; i--)
        printf("%d (%d) -> ", r[i], v[i]);
    printf("%d (%d)\n", r[0], v[0]);
}

// author: dr460r