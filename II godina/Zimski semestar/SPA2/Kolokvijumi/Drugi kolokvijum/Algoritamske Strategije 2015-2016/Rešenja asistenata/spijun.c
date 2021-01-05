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


int rekonstrukcija(int i, int polaziste, int *pret, int *dS, int *dA) {
	int rbr;
	if (i==polaziste) {
		return -1;
	}
	else  {
		rbr = rekonstrukcija(pret[i], polaziste, pret, dS, dA);
		if (rbr==-1 && dA[i]<=dS[i]) {
			return i;
		}
		else return rbr;
	}
}

int main() {
	int **graf;
	int *dS, *dA, *pretS, *pretA, *obidjenS, *obidjenA;
	int n, m, s, a, g;
	int i, j, u, v, t;
	int rbrLokacije, vremeHapsenja;
	scanf("%d%d", &n, &m);

	graf = (int **)malloc(n*sizeof(int *));
	dS = (int *)malloc(n*sizeof(int));
	dA = (int *)malloc(n*sizeof(int));
	pretS = (int *)malloc(n*sizeof(int));
	pretA = (int *)malloc(n*sizeof(int));
	obidjenS = (int *)malloc(n*sizeof(int));
	obidjenA = (int *)malloc(n*sizeof(int));

	for (i=0; i<n; i++) {
		graf[i] = (int *)malloc(n*sizeof(int));
		dS[i] = INF;
		dA[i] = INF;
		pretS[i] = NILL;
		pretA[i] = NILL;
		obidjenS[i] = FALSE;
		obidjenA[i] = FALSE;
	}

	for (i=0; i<n; i++)
		for (j=0; j<n; j++)
			graf[i][j] = INF;

	for (i=0; i<m; i++) {
		scanf("%d%d%d", &u, &v, &t);
		graf[u][v] = t;
		graf[v][u] = t;
	}

	scanf("%d%d%d", &a, &s, &g);
	dA[a] = 0;
	dS[s]=0;


	dijkstra(graf, obidjenS, dS, pretS, n);
	dijkstra(graf, obidjenA, dA, pretA, n);

	rbrLokacije = rekonstrukcija(g, s, pretS, dS, dA);
	if (rbrLokacije!=-1)
		vremeHapsenja = dS[rbrLokacije];
	else
		vremeHapsenja = -1;


	printf("%d\n%d\n", rbrLokacije, vremeHapsenja);
	/*
	printf("pretS\n");
	for (i=0; i<n; i++)
		printf("%d ", pretS[i]);
	printf("\n");

	printf("dA\n");
	for (i=0; i<n; i++)
		printf("%d ", dA[i]);
	printf("\n");
	* */
	return 0;

}

















