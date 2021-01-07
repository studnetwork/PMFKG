#include <stdio.h>
#include <stdlib.h>

#define POVEZANI 1
#define NEPOVEZANI 0

#define NEDEFINISANO (-1)

#define POSTOJI 1
#define NE_POSTOJI 0

int time = 0;
int ciklicnaVeza = NE_POSTOJI;

void inicijalizuj( int **graf, int *d, int *f/*, int *pred*/, int n )
{
	int i, j;

	for(i = 0; i < n; i++)
	{
		graf[i] = (int*) malloc( n * sizeof( int ) );
		if( !graf[i] )
		{
			printf("Neuspesno alociranje memorije\n");
			exit(EXIT_FAILURE);
		}

		for(j = 0; j < n; j++)
		{
			graf[i][j] = NEPOVEZANI;
		}

		d[i] = f[i] = NEDEFINISANO;
		/*pred[i] = NEDEFINISANO;*/
	}
}

void dfsVisit( int **graf, int *d, int *f, /*int *pred,*/ int *topoSort, int *indeks, int s, int n )
{
	int v;

	d[s] = ++time;
	
	for( v = 0; v < n; v++ )
	{
		if( graf[s][v] == POVEZANI )
		{
			if( d[v] == NEDEFINISANO )
			{
				/*pred[v] = s;*/
				dfsVisit( graf, d, f/*, pred*/, topoSort, indeks, v, n );
			}
			else if( f[v] == NEDEFINISANO )
			{
				ciklicnaVeza = POSTOJI;
				printf("Postoji ciklicna veza izmedju cvorova %d i %d\n", s, v );
			}
		}
	}

	f[s] = ++time;

	if( ciklicnaVeza == NE_POSTOJI )
	{				
		topoSort[*indeks] = s;
		*indeks = *indeks -1 ;
	}
}

void dfs( int **graf, int *d, int *f, /*int *pred,*/ int *topoSort, int *indeks, int n )
{
	int i;
	for(i = 0; i < n; i++)
	{
		if( d[i] == NEDEFINISANO )
			dfsVisit( graf, d, f, /*pred,*/ topoSort, indeks, i, n );
	}
}

int main()
{
	int n, l;
	int i, indeksTS;
	int u, v;
	
	printf("Unesite broj cvorova i veza:\n");
	scanf("%d%d", &n, &l );

	int **graf = (int**) malloc( n * sizeof( int* ) );
	/*int *pred = (int*) malloc( n * sizeof( int ) );*/
	int *topoSort = (int*) malloc( n * sizeof( int ) );
	int *d = (int*) malloc( n * sizeof( int ) );
	int *f = (int*) malloc( n * sizeof( int ) );

	/* proveri da li je sve ispravno alocirano */
	if( !graf /*|| !pred*/ || !topoSort || !d || !f )
	{
		printf("Neuspesno alociranje memorije\n");
		exit(EXIT_FAILURE);
	}

	inicijalizuj( graf, d, f/*, pred*/, n );

	printf("Unesite veze:\n");
	for(i = 0; i < l; i++)
	{
		scanf("%d%d", &u, &v );
		graf[u][v] = POVEZANI;
	}

	indeksTS = n-1;

	dfs( graf, d, f, /*pred,*/ topoSort, &indeksTS, n );

	printf("\nUlazna vremena:\n");
	for(i = 0; i < n; i++)
	{
		printf("%d ", d[i] );
	}

	printf("\n\nIzlazna vremena:\n");
	for(i = 0; i < n; i++)
	{
		printf("%d ", f[i] );
	}
	printf("\n\n");

	if( ciklicnaVeza == NE_POSTOJI )
	{
		printf("Topolosko sortiranje:\n");
		for(i = 0; i < n; i++)
		{
			printf("%d ", topoSort[i] );
		}
		printf("\n");
	}
	else
		printf("Grafik je ciklican\n");
}
