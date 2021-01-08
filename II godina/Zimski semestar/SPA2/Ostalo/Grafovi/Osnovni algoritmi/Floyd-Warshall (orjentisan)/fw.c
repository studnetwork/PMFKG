#include <stdio.h>
#include <stdlib.h>

#define INF (-1)
#define NILL (-1)

#define TRUE 1
#define FALSE 0

void inicijalizuj( int **graf, int **d, int **pi, int n )
{
	int i, j;

	for(i = 0; i < n; i++)
	{
		graf[i] = (int*) malloc( n * sizeof( int ) );
		d[i] = (int*) malloc( n * sizeof( int ) );
		pi[i] = (int*) malloc( n * sizeof( int ) );

		if( !graf[i] || !d[i] || !pi[i] )
		{
			printf("Neuspesno alociranje memorije\n");
			exit(EXIT_FAILURE);	
		}

		for(j = 0; j < n; j++)
		{
			graf[i][j] = INF;
			d[i][j] = INF;
			pi[i][j] = NILL;
		}

		/*graf[i][i] = 0;																	   ????																						*/
	}
}

int saberi( int a, int b )
{
	if( a == INF || b == INF )
		return INF;
	else
		return ( a + b );
}

int jeManji( int broj, int trenMin )
{
	if( broj == INF )
		return FALSE;

	else if( trenMin == INF )
		return TRUE;

	else
		return broj < trenMin;
}

void fw( int **graf, int **d, int **pi, int n )
{
	int i, j, k;

	/* Kopiranje tezinske matrice u matricu rastojanja za k=0 */
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			d[i][j] = graf[i][j];
		}
		
		d[i][i] = 0;																		/* rastojanje svakog cvora do samog sebe je 0												*/
	}

	for( k = 0; k < n; k++ )
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				if( i != j && j != k && i != k )											/* ne proverava put od nekog cvora do samog sebe jer je on uvek 0			*/
				{
					if( d[i][k] != INF && d[k][j] != INF )									/* proverava da li je moguce doci iz 'i' do 'j' preko 'k'					*/
					{
						if( jeManji( d[i][k] + d[k][j], d[i][j] ) )							/* proveri da li je put kraci ukoliko se ide preko 'k'						*/
						{
							d[i][j] = d[i][k] + d[k][j];
							pi[i][j] = pi[k][j];
						}
					}
				}
}

void stampajKvadMatricu( int **matrica, int n )
{
	int i, j;

	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			if( matrica[i][j] == INF )
				printf("INF ");
			else
				printf("%3d ", matrica[i][j] );
		}
		printf("\n");
	}
	printf("\n");
}

void stampajPutanju( int *pi, int s, int v, int n )
{
	if( s == v )
		printf("%d ", s );

	else if( pi[v] == NILL )
		printf("Ne postoji putanja od %d do %d\n", s, v );

	else
	{
		stampajPutanju( pi, s, pi[v], n );
		printf("%d ", v );
	}
}

void stampajSvePutanje( int ** pi, int n )
{
	int i, j;

	for(i = 0; i < n; i++)
	{
		printf("\n\"Najkrace\" putanje koje krecu iz cvora %d:\n", i );
		for(j = 0; j < n; j++)
		{
			printf("Od %d do %d\n", i, j );
			printf("===========\n");
			stampajPutanju( pi[i], i, j, n );
			printf("\n\n");
		}
	}
}

int main()
{
	int i, n, l;
	int u, v, t;

	printf("Unesite broj cvorova i veza:\n");
	scanf("%d%d", &n, &l );

	int **graf = (int**) malloc( n * sizeof( int* ) );
	int **d = (int**) malloc( n * sizeof( int* ) );
	int **pi = (int**) malloc( n * sizeof( int* ) );

	if( !graf || !d || !pi )
	{
		printf("Neuspesno alociranje memorije\n");
		exit(EXIT_FAILURE);
	}

	inicijalizuj( graf, d, pi, n );

	printf("Unesi veze:\n");
	for(i = 0; i < l; i++)
	{
		scanf("%d%d%d", &u, &v, &t );
		graf[u][v] = t;
		d[u][v] = t;
		pi[u][v] = u;
	}

	/* odredi "najkracu" putanju od svakog cvora do svakog drugog cvora */
	fw( graf, d, pi, n );

	/* stampaj tezinsku matricu */
	printf("Tezinska matrica:\n");
	stampajKvadMatricu( graf, n );

	/* stampaj "duzinu najkrace" putanje za svaki cvor*/
	printf("Matrica d:\n");
	stampajKvadMatricu( d, n );

	/* stampaj predaka od svakog cvora */
	printf("Matrica predaka:\n");
	stampajKvadMatricu( pi, n );

	/* stampaj "najkracu" putanju od svakog cvora do svakog drugog cvora */
	stampajSvePutanje( pi, n );
}
