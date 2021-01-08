#include <stdio.h>
#include <stdlib.h>

#define create(t, x) (t*)malloc(sizeof(t) * (x))

#define UNDEF -1 // nedefinisano
#define INF -2 // + beskonacnost


int DistAdd(int a, int b)
{
    if(a == INF || b == INF)
        return INF;
    return a + b;
}

int DistMin(int a, int b) // => UNDEF 
{
    if(a == INF && b != INF)
        return b;
    if(a != INF && b == INF)
        return a;

    return (a <= b)? a : b;
}


int AllPairsShortestPaths(int **W, int **D, int **P, int n)
{
    int i, j, k;

    // Inicijalizacija
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            D[i][j] = W[i][j];
            P[i][j] = (W[i][j] == INF || i == j)? UNDEF : i;
        }
        D[i][i] = 0;
    }

    // Glavni deo
    for(k = 0; k < n; k++)
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++) {
                int oldD = D[i][j];
                int newD = DistMin(D[i][j], DistAdd(D[i][k], D[k][j]));
                D[i][j] = newD;
                P[i][j] = (oldD == newD)? P[i][j] : P[k][j];
            }


}

int **CreateMatrix(int n)
{
    int **M = create(int*, n);
    int i;
    for(i = 0; i < n; i++)
        M[i] = create(int, n);
    
    return M;
}

void LoadGraph(int **g, int vn, int en, int isDirected)
{
    int i, j;
    for(i = 0; i < vn; i++)
        for(j = 0; j < vn; j++)
            g[i][j] = INF;

    int a, b, w;
    for(i = 0; i < en; i++) {
        scanf("%d%d%d", &a, &b, &w);
        g[a][b] = w;
        if(!isDirected) g[b][a] = w;
    }
}

void PrintMat(int **g, int n)
{
    int i, j;
    printf("    ");
    for(i = 0; i < n; i++)
        printf("%3d", i);
    printf("\n    ");

    for(i = 0; i < n; i++)
        printf(" __");
    printf("\n");

    for(i = 0; i < n; i++) {
        printf("%2d |", i);
        for(j = 0; j < n; j++) {
            if(g[i][j] != INF && g[i][j] != UNDEF) printf("%3d", g[i][j]);
            else printf("  -");
        }
        printf("\n");
    }
    
    printf("\n");
}

int main()
{
    int vn, en;
    scanf("%d%d", &vn, &en);

    int **g = CreateMatrix(vn);
    int **D = CreateMatrix(vn);
    int **P = CreateMatrix(vn);

    LoadGraph(g, vn, en, 0);
    AllPairsShortestPaths(g, D, P, vn);

    printf("Graf:\n");
    PrintMat(g, vn);
    printf("D:\n");
    PrintMat(D, vn);
    printf("P:\n");
    PrintMat(P, vn);
}
