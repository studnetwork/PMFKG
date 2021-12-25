//kolokvijum 2009/2010
//link do postavke kolokvijuma: https://imi.pmf.kg.ac.rs/moodle/pluginfile.php/18107/mod_resource/content/2/II%20kolokvijum%202009.pdf
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TRUE 1
#define FALSE 0
#define INF -1
#define NEDEFINISANO -2
int jeManji(double i, double j)
{
    if (j == INF)
        return TRUE;
    if (i == INF)
        return FALSE;
    return i < j;
}
typedef struct
{
    int x, y;
} Cvor;
typedef struct
{
    int u;
    int v;
    int w;
} Veza;
double izracuajVezu(Cvor c1, Cvor c2)
{
    return sqrt((c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y));
}
int dajNajmanji(int *obidjeno, double *duzina, int n)
{
    int minCvor = NEDEFINISANO;
    double minDuzina = INF;
    int i;
    for (i = 0; i < n; i++)
    {
        if (!obidjeno[i] && jeManji(duzina[i], minDuzina))
        {
            minCvor = i;
            minDuzina = duzina[i];
        }
    }
    return minCvor;
}
Veza *prim(double **graf, int n, int *s)
{
    Veza *veze = (Veza *)malloc(n * sizeof(Veza));
    int *obidjeno = (int *)malloc(n * sizeof(int));
    int *prethodnik = (int *)malloc(n * sizeof(int));
    double *duzina = (double *)malloc(n * sizeof(double));
    int i, u, v;
    for (i = 0; i < n; i++)
    {
        obidjeno[i] = FALSE;
        duzina[i] = INF;
        prethodnik[i] = NEDEFINISANO;
    }
    duzina[0] = 0;
    int ind = 0;
    int suma = 0;
    u = 0;
    for (i = 0; i < n && u != NEDEFINISANO; i++)
    {
        u = dajNajmanji(obidjeno, duzina, n);
        suma += duzina[u];
        obidjeno[u] = TRUE;
        if (prethodnik[u] != NEDEFINISANO)
        {
            veze[ind].u = prethodnik[u];
            veze[ind].v = u;
            veze[ind].w = duzina[u];
            ind++;
        }
        for (v = 0; v < n; v++)
        {
            if (graf[u][v] != INF && !obidjeno[v] && jeManji(graf[u][v], duzina[v]))
            {
                duzina[v] = graf[u][v];
                prethodnik[v] = u;
            }
        }
    }
    *s = suma;
    return veze;
}
void dijkstra(int *vreme, double *d, int n, double **graf)
{
    int *obidjeno = (int *)malloc(n * sizeof(int));
    int i, u, v;
    for (i = 0; i < n; i++)
        obidjeno[i] = FALSE;
    for (i = 0; i < n; i++)
    {
        u = dajNajmanji(obidjeno, d, n);
        obidjeno[u] = TRUE;
        for (v = 0; v < n; v++)
        {
            if (graf[u][v] != INF && jeManji(graf[u][v] + d[u] + vreme[u], d[v]))
                d[v] = graf[u][v] + d[u] + vreme[u];
        }
    }
    d[u] += vreme[u];
}
int main()
{
    int n, i, j;
    scanf("%d", &n);
    Cvor *cvorovi = (Cvor *)malloc(n * sizeof(Cvor));
    int *vremeObrade = (int *)malloc(n * sizeof(int));
    double **graf = (double **)malloc(n * sizeof(double *));
    for (i = 0; i < n; i++)
    {
        scanf("%d %d %d", &cvorovi[i].x, &cvorovi[i].y, &vremeObrade[i]);
    }
    for (i = 0; i < n; i++)
    {
        graf[i] = (double *)malloc(n * sizeof(double));
        for (j = 0; j < n; j++)
        {
            if (i == j)
                graf[i][j] = INF;
            else
                graf[i][j] = izracuajVezu(cvorovi[i], cvorovi[j]);
        }
    }
    int suma;
    Veza *uvrsteneVeze = prim(graf, n, &suma);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            graf[i][j] = INF;
    double *d = (double *)malloc(n * sizeof(double));
    int brzina, start, end;
    scanf("%d %d %d", &brzina, &start, &end);
    printf("%d\n", suma);
    for (i = 0; i < n; i++)
    {
        d[i] = INF;
    }
    for (i = 0; i < n - 1; i++)
    {
        int x = uvrsteneVeze[i].u, y = uvrsteneVeze[i].v;
        graf[x][y] = graf[y][x] = 1.0 * uvrsteneVeze[i].w / brzina;
        printf("%d %d\n", x, y);
    }
    d[start] = 0;
    dijkstra(vremeObrade, d, n, graf);
    printf("%.0lf\n", d[end]);
    return 0;
}