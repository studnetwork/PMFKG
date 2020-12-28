#include <stdio.h>
#include <stdlib.h>

#define INF (-1)
#define NILL (-1)
#define TRUE 1
#define FALSE 0

int jeManji(int i, int j) {
	if (i==INF)
		return FALSE;
	if (j==INF)
		return TRUE;
	return i<j;
}

int minimum(int a, int b)
{
    if(a < b)
        return a;
    return b;
}

int nadjiMinimum(int *obidjen, int *d, int n) {
	int i;
	int min = INF, minCvor=NILL;
	for (i=0; i<n; i++) {
		if (obidjen[i]==FALSE && jeManji(d[i], min)) {
			min = d[i];
			minCvor = i;
		}
	}
	return minCvor;
}

void relax(int **graf, int *d, int *pret, int u, int v) {
	if (jeManji(d[u]+graf[u][v], d[v])) {
		d[v] = d[u]+graf[u][v];
		pret[v] = u;
	}
}

void dijkstra(int **graf, int *obidjen, int *d, int *pret, int n)
{
	int u, i, v;
	for (i=0; i<n; i++) {
		u = nadjiMinimum(obidjen, d, n);
		obidjen[u] = TRUE;
		for (v=0; v<n; v++) {
			if (graf[u][v]!=INF && obidjen[v]==FALSE)
				relax(graf, d, pret, u, v);
		}
	}
}


void rekonstrukcija(int i, int polaziste, int *pret, int flag) {
	int rbr;
	if (i==polaziste) {
		if (flag)
            return;
        printf("%d ", i);
	}
	else  {
		rekonstrukcija(pret[i], polaziste, pret, flag);
		printf("%d ", i);
	}
}


int main() 
{
	int **graf;
	int *dB, *dA, *pretB, *pretA, *obidjenB, *obidjenA;
	int n, m, s, a, g, b, c;
	int i, j, u, v, t1, t2;
	int rbrLokacije, vremeHapsenja;

	scanf("%d%d", &n, &m);

	graf = (int **)malloc(n*sizeof(int *));
	dB = (int *)malloc(n*sizeof(int));
	dA = (int *)malloc(n*sizeof(int));
	pretB = (int *)malloc(n*sizeof(int));
	pretA = (int *)malloc(n*sizeof(int));
	obidjenB = (int *)malloc(n*sizeof(int));
	obidjenA = (int *)malloc(n*sizeof(int));
    
	for (i=0; i<n; i++) {
		graf[i] = (int *)malloc(n*sizeof(int));
		dB[i] = INF;
		dA[i] = INF;
		pretB[i] = NILL;
		pretA[i] = NILL;
		obidjenB[i] = FALSE;
		obidjenA[i] = FALSE;
	}
    
	for (i=0; i<n; i++)
		for (j=0; j<n; j++)
			graf[i][j] = INF;

	for (i=0; i<m; i++) {
		scanf("%d%d%d%d", &u, &v, &t1, &t2);
		graf[u][v] = minimum(t1, t2);
	}
    
	scanf("%d%d%d", &a, &b, &c);
	dA[a] = 0;
	dB[b] = 0;

    dijkstra(graf, obidjenA, dA, pretA, n);
	dijkstra(graf, obidjenB, dB, pretB, n);
	
    rekonstrukcija(b, a, pretA, 0);
    rekonstrukcija(c, b, pretB, 1);
	
    printf("\n%d\n", dA[b] + dB[c]);

	return 0;

}

















