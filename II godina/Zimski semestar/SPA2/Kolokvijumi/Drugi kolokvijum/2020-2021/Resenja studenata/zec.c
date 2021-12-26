//kolokvijum 2020/2021
//Resio: Ljubomir Matovic 58/2020
//testirano je test primerima za 26 poena
//uradjen je i slucaj sa pomeranjem ali nije testiran
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define INF -1
#define NEDEFINISANO -2
#define STARTNI_CVOR -3
#define create(t, n) (t *)malloc(n * sizeof(t))
#define VUK 1
#define ZEC 2
#define PRAZNO 3

int jeManji(int i, int j)
{
    if (i == INF)
        return FALSE;
    if (j == INF)
        return TRUE;
    return i < j;
}
int dajNajmanji(int *d, int *obidjeno, int n)
{
    int i;
    int minCvor = NEDEFINISANO;
    int minRast = INF;
    for (i = 0; i < n; i++)
    {
        if (!obidjeno[i] && jeManji(d[i], minRast))
        {
            minCvor = i;
            minRast = d[i];
        }
    }
    return minCvor;
}
void kopirajNiz(int *izvor, int *odrediste, int duzina)
{
    for (int i = 0; i < duzina; i++)
        odrediste[i] = izvor[i];
}
void pomeriVukove(int **graf, int *zbunovi, int n, int brPomeranja)
{
    int i, j, k;
    for (k = 0; k < brPomeranja; k++)
    {
        for (i = 0; i < n; i++)
        {
            if (zbunovi[i] == VUK)
            {
                for (j = 0; j < n; j++)
                {
                    if (graf[i][j] != INF && zbunovi[j] == PRAZNO)
                    {
                        zbunovi[i] = PRAZNO;
                        zbunovi[j] = VUK;
                        break;
                    }
                }
            }
        }
    }
}
int povezanSaVukom(int **graf, int *zbunovi, int n, int cvor)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (graf[cvor][i] != INF && zbunovi[i] == VUK)
        {
            return TRUE;
        }
    }
    return FALSE;
}
void dijkstraSaPomeranjem(int **graf, int *d, int *zbunovi, int *pret, int *skokovi, int n)
{
    int *obidjeno = create(int, n);
    int *zbunoviKopija = create(int, n);
    int i, u, v;
    for (i = 0; i < n; i++)
    {
        obidjeno[i] = FALSE;
        skokovi[i] = 0;
    }

    for (i = 0, u = dajNajmanji(d, obidjeno, n); i < n && u != NEDEFINISANO; i++, u = dajNajmanji(d, obidjeno, n))
    {
        obidjeno[u] = TRUE;
        kopirajNiz(zbunovi, zbunoviKopija, n);
        if (skokovi[u] > 2)
            pomeriVukove(graf, zbunoviKopija, n, skokovi[u] / 3);
        if (zbunoviKopija[u] == VUK || povezanSaVukom(graf, zbunoviKopija, n, u))
            continue;
        for (v = 0; v < n; v++)
        {
            if (!povezanSaVukom(graf, zbunoviKopija, n, v) && graf[u][v] != INF && !obidjeno[v])
            {
                //relaksacija
                if (jeManji(graf[u][v] + d[u], d[v]))
                {
                    d[v] = graf[u][v] + d[u];
                    pret[v] = u;
                    skokovi[v] = skokovi[u] + 1;
                }
            }
        }
    }
}
void dijkstraBezPomeranja(int **graf, int *d, int *zbunovi, int *pret, int *skokovi, int n)
{
    int *obidjeno = create(int, n);
    int i, u, v;
    for (i = 0; i < n; i++)
    {
        obidjeno[i] = FALSE;
        skokovi[i] = 0;
    }

    for (i = 0, u = dajNajmanji(d, obidjeno, n); i < n && u != NEDEFINISANO; i++, u = dajNajmanji(d, obidjeno, n))
    {
        obidjeno[u] = TRUE;
        if (zbunovi[u] == VUK || povezanSaVukom(graf, zbunovi, n, u))
            continue;
        for (v = 0; v < n; v++)
        {
            if (!povezanSaVukom(graf, zbunovi, n, v) && graf[u][v] != INF && !obidjeno[v])
            {
                //relaksacija
                if (jeManji(graf[u][v] + d[u], d[v]))
                {
                    d[v] = graf[u][v] + d[u];
                    pret[v] = u;
                    skokovi[v] = skokovi[u] + 1;
                }
            }
        }
    }
}
void rekonstrukcija(int *pret, int cilj, int start)
{
    if (cilj == start)
    {
        printf("%d ", cilj);
    }
    else if (pret[start] == NEDEFINISANO)
    {
        printf("Ne moze se stici do cilja od cvora %d ", start);
    }
    else
    {
        rekonstrukcija(pret, cilj, pret[start]);
        printf("%d ", start);
    }
}
int main()
{
    int n, l, m, i, j, u, v;
    scanf("%d%d%d", &n, &l, &m);
    int **graf = create(int *, n);
    int *d = create(int, n);
    int *zbunovi = create(int, n);
    int *skokovi = create(int, n);
    int *pret = create(int, n);
    for (i = 0; i < n; i++)
    {
        d[i] = INF;
        zbunovi[i] = PRAZNO;
        pret[i] = NEDEFINISANO;
        graf[i] = create(int, n);
        for (j = 0; j < n; j++)
        {
            graf[i][j] = INF;
        }
    }
    for (i = 0; i < l; i++)
    {
        scanf("%d%d", &u, &v);
        graf[u][v] = graf[v][u] = 1;
    }
    for (i = 0; i < m; i++)
    {
        scanf("%d", &u);
        zbunovi[u] = VUK;
    }
    int start, end;
    scanf("%d%d", &start, &end);
    zbunovi[start] = zbunovi[end] = ZEC;
    d[start] = 0;
    pret[start] = STARTNI_CVOR;
    dijkstraBezPomeranja(graf, d, zbunovi, pret, skokovi, n);
    if (d[end] != INF)
    {
        printf("uspeo je\n%d\n", skokovi[end]);
        rekonstrukcija(pret, start, end);
        putchar('\n');
    }
    else
    {
        printf("nije uspeo\n");
    }
    return 0;
}