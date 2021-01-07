#include <stdio.h>
#include <stdlib.h>


#define INF (-1)
#define NEDEFINISANO (-1)

#define TRUE 1
#define FALSE 0

void inicijalizuj( int **graf, int *d, int *pred, int *obidjeni, int n )
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
			graf[i][j] = INF;
		}

		d[i] = INF;
		pred[i] = NEDEFINISANO;
		obidjeni[i] = FALSE;
	}
}

int jeManji( int key, int min )
{
	if( key == INF )
		return FALSE;

	else if( min == INF )
		return TRUE;

	else
		return key < min;
}

int saberi( int x, int y )
{
	if( x == INF || y == INF )
		return INF;
	
	else
		return x+y;
}

int nadjiNajmanjeD( int *d, int *obidjeni, int n )
{
	int i, vredNajmanjeg, indeksNajmanjeg;

	vredNajmanjeg = INF;
	indeksNajmanjeg = NEDEFINISANO;

	for(i = 0; i < n; i++)
	{
		if( obidjeni[i] == FALSE && jeManji( d[i],  vredNajmanjeg ) )
		{
			vredNajmanjeg = d[i];
			indeksNajmanjeg = i;
		}
	}

	return indeksNajmanjeg;
}

void relex( int *d, int *pred, int u, int v, int t )
{
	int prekoDrugogCvora = saberi( d[u], t );									

	if( jeManji( prekoDrugogCvora, d[v] ) )
	{
		d[v] = prekoDrugogCvora;
		pred[v] = u;
	}
}

void dijkstra( int **graf, int *d, int *pred, int *obidjeni, int s, int n )
{
	int v, u;

	d[s] = 0;

	while( ( u = nadjiNajmanjeD( d, obidjeni, n )) != NEDEFINISANO )
	{
		/* za njega sigurno nece postojati kraci put */
		obidjeni[u] = TRUE;
															
		for( v = 0; v < n; v++ )
		{
			if( graf[u][v] != INF && obidjeni[v] == FALSE )						/* proverava da li 'v' njegov sused i da li je obidjen	*/
			{
				relex( d, pred, u, v, graf[u][v] );								/* proveri da li je bolji put preko cvora 'u'			*/
			}
		}
	}
}

void stampajPutanju( int *pred, int pocetak, int kraj )
{
	if( pocetak == kraj )
		printf("%d ", pocetak);

	else if( pred[kraj] == NEDEFINISANO )
		printf("Ne postoji putaja od %d do %d\n", pocetak, kraj );

	else
	{
		stampajPutanju( pred, pocetak, pred[kraj] );
		printf("%d ", kraj );
	}
}

/*void stampajMatricuPovezanosti( int **graf, int n )
{
	int i, j;

	printf("  ");
	for(i = 0; i < n; i++)
		printf("%3d ", i );
	printf("\n");


	for(i = 0; i < n; i++)
	{
		printf("%3d ", i );
		for(j = 0; j < n; j++)
		{
			if( graf[i][j] == INF )
				printf("INF ");
			else
				printf("%3d ", graf[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}*/

int main()
{
	int i, n, l;
	int s, u, v, t;

	printf("Unesite broj cvorova i veza:\n");
	scanf("%d%d", &n, &l );

	int **graf = (int**) malloc( n * sizeof( int* ) );
	int *d = (int*) malloc( n * sizeof( int ) );
	int *pred = (int*) malloc( n * sizeof( int ) );
	int *obidjeni = (int*) malloc( n * sizeof( int ) );

	if( !graf || !d || !pred || !obidjeni )
	{
		printf("Neuspesno alociranje memorije\n");
		exit(EXIT_FAILURE);
	}

	inicijalizuj( graf, d, pred, obidjeni, n );

	printf("Unesi veze:\n");
	for(i = 0; i < l; i++)
	{
		scanf("%d%d%d", &u, &v, &t );
		graf[u][v] = t;
	}

	printf("Unesi pocetni element:\n");
	scanf("%d", &s );

	/* odredi "najkrace" putanje od s do svakog cvora posebno */
	dijkstra( graf, d, pred, obidjeni, s, n );

	/* za svaki cvor stampaj putanju od pocetnog cvora do tog cvora */
	for(i = 0; i < n; i++)
	{
		printf("Putanja od %d do %d:\n", s, i );
		stampajPutanju( pred, s, i );
		printf("\n\n");
	}

//	stampajMatricuPovezanosti( graf, n );

	/* Stampaj predaka svakog cvora 
	for(i = 0; i < n; i++)
	{
		printf("%d pred: %d\n", i, pred[i] );
	}*/
}
