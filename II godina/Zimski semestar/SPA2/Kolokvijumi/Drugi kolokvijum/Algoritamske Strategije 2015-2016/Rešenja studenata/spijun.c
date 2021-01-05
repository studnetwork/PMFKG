#include <stdio.h>
#include <stdlib.h>

#define create(t, c) (t*)malloc(sizeof(t) * (c))

#define INF (-1) // koristi se kao beskonacna udaljenost (a u matrici povezanosti kada veza ne postoji)
#define UNDEF (-1) // koristi se umesto indeksa (id-a) elementa grafa kada treba naznaciti ne postojanje elementa (nesto kao NULL)

int Compare(int a, int b) // a>b -> 1, a=b -> 0, a<b -> -1
{
    if(a == b) return 0;
    else if(a == INF && b != INF) return 1;
    else if(a != INF && b == INF) return -1;
    else if(a > b) return 1;
    else if(a < b) return -1;
}

// vraca jos ne obradjeni element sa najmanjom distancom
int GetNextMin(int *Q, int *d, int nv)
{
    int i, x = 0; // x - id (indeks) elementa koji za sada ima najmanju distancu od pocetka
    while(x < nv && !Q[x]) x++; // trazi se prvi element koji je neobradjen (Q[i] == 1)
    
    if(x == nv) return UNDEF; // Q je prazan

    for(i = x+1; i < nv; i++) // trazi se element koji je neobradjen, a ima najmanju distancu
        if(Q[i] && Compare(d[i], d[x]) == -1)
            x = i;
    
    Q[x] = 0; // element x se sada posmatra kao obradjen element
    return x; // vraca se element x (onaj koji ima najmanju distancu)
}

void Relax(int u, int v, int **graph, int *d, int *p)
{
    // ukoliko je distanca od pocetka do elementa v preko elementa u ...
    // ... manja od one koja je trenutno zabelezena, onda se belezi ova ...
    // ... nova (preklo elementa u), kao i sam taj element u (belezi se kao prethodnik elementa v)
    if(Compare((d[u] == INF)?INF:d[u]+graph[u][v], d[v]) == -1) { // napomena: INF + broj = INF
        d[v] = d[u] + graph[u][v];
        p[v] = u;
    }
}

// Dijkstra's Shortest Path Algorithm
void FindShortestPaths(int s, int **graph, int nv, int **p, int **d)
{
    // alokacija memorije za pomocne nizove (Q je definisano ovde jer sluzi samo ovoj funkciji)
    int *Q = create(int, nv);
    *p = create(int, nv);
    *d = create(int, nv);

    // postavljanje pocetnih vrednosti za pomocne nizove
    int i;
    for(i = 0; i < nv; i++) {
        (*d)[i] = INF;
        (*p)[i] = UNDEF;
        Q[i] = 1;
    }
    (*d)[s] = 0;

    // uzimaju se elementi sa "reda" Q (to je zapravo niz, ali GetNextMin obezbedjuje da se elementi uzimaju kao sa nekog reda u kome su elementi sortirani po distanci d)
    int u, v;
    while((u = GetNextMin(Q, *d, nv)) != UNDEF)
        for (v = 0; v < nv; v++)
            if(graph[u][v] != INF && Q[v])
                Relax(u, v, graph, *d, *p);
}

// alocira memoriju za graf i ucitava ga sa standardnog ulaza
int** LoadGraph(int **graph, int nv, int ne)
{
    graph = create(int*, nv);

    int i, j;
    for (i = 0; i < nv; i++) {
        graph[i] = create(int, nv);
        for (j = 0; j < nv; j++)
            graph[i][j] = INF;
    }
    
    int v1, v2, w;
    for(i = 0; i < ne; i++) {
        scanf("%d%d%d", &v1, &v2, &w);
        graph[v1][v2] = graph[v2][v1] = w;
    }

    return graph;
}

int main()
{
    int **graph, nv, ne; // za graf, nv - num. of vertices (broj temena, tj. elemenata), ne - num. of edges (broj ivica, tj. veza)
    int S, *pS, *dS; // za spijuna, S - pocetna pozicija, pS - niz prethodnika, dS - niz distanci od pocetka
    int A, *pA, *dA; // za agenta, A - pocetna pozicija, pA - niz prethodnika, dA - niz distanci od pocetka
    int G; // pozicija granicnog prelaza

    scanf("%d%d", &nv, &ne);
    graph = LoadGraph(graph, nv, ne);
    
    scanf("%d%d%d", &A, &S, &G);
    
    FindShortestPaths(S, graph, nv, &pS, &dS); // racunanje minimalnih distanci za spijuna
    FindShortestPaths(A, graph, nv, &pA, &dA); // racunanje minimalnih distanci za agenta

    // ispitivanje da li agent moze presresti spijuna u nekoj tacki
    // ako na putu od G do S postoji tacka koja je bliza agentu nego spijunu to je tacka na kojoj ce agent presresti spijuna
    int x = G, P = -1;
    while(pS[x] != UNDEF) {
        if(dA[x] <= dS[x])
            P = x;
        x = pS[x];
    }

    if(P != -1) {
        printf("Agent ce uhvatiti Spijuna na lokaciji %d, u vremenskom trenutku %d\n", P, dS[P]);
    } else {
        printf("Agent ne moze uhvatiti spijuna\n");
    }
}

// author: dr460r