#include <stdio.h>
#include <stdlib.h>

#define POVEZANI 1
#define NEPOVEZANI 0

#define NEDEFINISANO (-1)

struct Element
{
	int indeksCvora;
	struct Element *sled;
};

void inicijalizacija( int **graf, int *d, int *preth, int n )
{
	int i, j;

	for(i = 0; i < n; i++)
	{
		/* inicijalizacija grafa */
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


		/* inicijalizacija pomocnih nizova */
		d[i] = NEDEFINISANO;
		preth[i] = NEDEFINISANO; 
	}
}

void dodajURed( struct Element **glava, struct Element **rep, int indeksCvora )
{
	struct Element *novi = (struct Element *) malloc( sizeof( struct Element ) );
	if( !novi )
	{
		printf("Neuspesno alociranje memorije\n");
		exit(EXIT_FAILURE);
	}

	novi->indeksCvora = indeksCvora;
	novi->sled = NULL;
	
	if( *glava == NULL )											/* proverava da li je red prazan								*/
	{
		*glava = novi;
		*rep = novi;
	}
	else 															/* dodaje element na kraj reda									*/
	{
		(*rep)->sled = novi;										/* na poslednji el. povezuje novi								*/
		*rep = novi;												/* posto je novi povezan na kraj, sada on postaje poslednji		*/
	}
}

int skiniSaRed( struct Element **glava, struct Element **rep )
{
	int indeksCvora;
	struct Element *temp;

	if( *glava == NULL ) 											/* proveri da li je red prazan 									*/
		return NEDEFINISANO;
	else
	{
		indeksCvora = (*glava)->indeksCvora;						/* cuva indeks cvora koji ce se izbaciti iz reda		       	*/
		
		if( *glava == *rep )										/* proveri da li je u redu ostao sam jedan element				*/
			*rep = NULL;											/* sprecava pojavu dangling pointera							*/

		temp = *glava;												/* sacuvaj adresu el. koji ce biti obrisan						*/
		*glava = (*glava)->sled;									/* postavi glavu na sledeci element; ako ima samo 1. bice NULL	*/
		free(temp);													/* oslobodi memoriju koji je zauzimao prvi element				*/

		return indeksCvora;											/* vrati indeks cvora koji se nalazio na prvom mestu u redu		*/
	}
}

void stampajMatricuPovezanosti( int **graf, int n )
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
			if( graf[i][j] == NEPOVEZANI )
				printf("INF ");
			else
				printf("%3d ", graf[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void bfs( int **graf, int *d, int *preth, struct Element **glava, struct Element **rep, int n )
{
	int u, v;
	/* prolazi kroz graf sve dok svi cvorovi kojima je predak cvor s
	 * ne obidju sve svoje susede                                                             										*/
	while( ( u = skiniSaRed( glava, rep ) ) != NEDEFINISANO )	
	{
		for( v = 0; v < n; v++ )
		{
			if( graf[u][v] == POVEZANI && d[v] == NEDEFINISANO )
			{		
				d[v] = d[u] + 1;
				preth[v] = u;
				dodajURed( glava, rep, v );
			}
		}
	}
}

void stampajPutanju( int *preth, int pocetniCvor, int indeksCvora )
{
	if( indeksCvora == pocetniCvor )
		printf("%d ", indeksCvora );

	else if( preth[indeksCvora] == NEDEFINISANO )
		printf("Nije moguce doci od cvora %d do cvora %d\n", pocetniCvor, indeksCvora );

	else
	{
		stampajPutanju( preth, pocetniCvor, preth[indeksCvora] );
		printf("%d ", indeksCvora );
	}
}

int main()
{
	int i, n, l;
	int u, v, s;

	/* deklaracija pointera na pocetak i kraj reda */
	struct Element *glava, *rep;

	/* inicijalizacija pointera na el. reda*/
	glava = rep = NULL;

	printf("Unesite broj cvorova i veza:\n");
	scanf("%d%d", &n, &l );

	int **graf = (int**) malloc( n * sizeof( int* ) );
	int *d = (int*) malloc( n * sizeof( int ) );
	int *preth = (int*) malloc( n * sizeof( int ) );

	/* provera da li je sve ispravno alocirano */
	if( !graf || !d || !preth ) 
	{
		printf("Neuspesno alociranje memorije\n");
		exit(EXIT_FAILURE);
	}

	/* inicijalizacija grafa i potrebnih nizova */
	inicijalizacija( graf, d, preth, n );
	
	/* unos podataka o vezama */
	printf("Unesite veze:\n");
	for(i = 0; i < l; i++)
	{
		scanf("%d%d", &u, &v );
		graf[u][v] = POVEZANI;
	}
	
	printf("Unesite indeks pocetnog cvora (zero-based):\n");
	scanf("%d", &s );

	/* prvom cvoru je potrebno 0 koraka da dodje do samog sebe */
	d[s] = 0;

	/* posto znamo "daljinu" cvora s od pocetka (njega samog)
	 * dodajemo ga u red za cvorove cije susete treba ispitati */
	dodajURed( &glava, &rep, s );

	/* odredjivanje potrebnih koraka od cvora s do svakog drugo cvora */
	bfs( graf, d, preth, &glava, &rep, n );


	/* ispisivanje putanje od cvora s to svakog cvora u grafu, ukoliko postoji */
	for(i = 0; i < n; i++)
	{
		printf("Putanja od %d do %d:\n", s, i );
		stampajPutanju( preth, s, i );
		printf("\n");
	}

	/* ispis matrice povezanosti */
	stampajMatricuPovezanosti( graf, n );
}
