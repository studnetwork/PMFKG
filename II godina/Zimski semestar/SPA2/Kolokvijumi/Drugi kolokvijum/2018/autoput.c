//Resio: Ljubomir Matovic 58/2020

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define kreirajNiz(t, n) (t *)malloc((n) * sizeof(t))

#define REGIONALNI 0
#define AUTOPUT 1
typedef struct
{
    int u, v;
    int duzinaPuta;
    int tipPuta;
} Veza;

void zameniVeze(Veza *v1, Veza *v2)
{
    Veza t = *v1;
    *v1 = *v2;
    *v2 = t;
}
void bojeFix(int *boje, int n, int u, int v)
{
    int bojaV = boje[v];
    for (int i = 0; i < n; i++)
    {
        if (boje[i] == bojaV)
            boje[i] = boje[u];
    }
}
int main()
{
    int n, l, i, j, brUvrstenih;
    scanf("%d%d", &n, &l);
    int saldo, cenaIzgradnje, novacOdRusenja;
    Veza *veze = kreirajNiz(Veza, n);
    int *uvrsteneVeze = kreirajNiz(int, n);
    int *boje = kreirajNiz(int, n);
    for (i = 0; i < l; i++)
    {
        scanf("%d %d %d %d", &veze[i].u, &veze[i].v, &veze[i].duzinaPuta, &veze[i].tipPuta);
        uvrsteneVeze[i] = FALSE;
    }
    scanf("%d%d%d", &cenaIzgradnje, &novacOdRusenja, &saldo);
    for (i = 0; i < n; i++)
    {
        boje[i] = i;
    }
    for (i = 0; i < l; i++)
    {
        for (j = i + 1; j < l - 1; j++)
        {
            if (veze[i].duzinaPuta > veze[j].duzinaPuta)
                zameniVeze(&veze[i], &veze[j]);
        }
    }
    for (i = 0; i < l; i++)
    {
        if (veze[i].tipPuta == AUTOPUT)
            saldo += veze[i].duzinaPuta * novacOdRusenja;
    }
    int u, v;
    for (i = 0, brUvrstenih = 0; i < l && brUvrstenih < n - 1; i++)
    {
        u = veze[i].u;
        v = veze[i].v;
        if (boje[u] != boje[v])
        {
            bojeFix(boje, n, u, v);
            uvrsteneVeze[i] = TRUE;
            brUvrstenih++;
            saldo -= veze[i].duzinaPuta * ((veze[i].tipPuta == AUTOPUT) ? novacOdRusenja : cenaIzgradnje);
        }
    }
    printf("%d\n", (saldo > -1) ? saldo : -1);
    return 0;
}