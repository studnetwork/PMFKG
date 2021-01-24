#include <stdio.h>
#include <stdlib.h>

typedef struct cvor
{
	int suma;
	int brPojav;
	int balans;
	struct cvor *levi;
	struct cvor *desni;
} cvor;

cvor *kreirajCvor( int suma )
{
	cvor *novi = NULL;
	
	novi = (cvor *) malloc( sizeof(cvor) );
	
	if( !novi )
	{
		printf("malloc: Neuspesno alociranje\n");
		exit(EXIT_FAILURE);
	}
	
	novi->suma = suma;
	novi->brPojav = 1;
	novi->balans = 0;
	novi->levi = novi->desni = NULL;
	
	return novi;
}

cvor *trazi( cvor *stablo, cvor **pret, int key ) /* drugi argument nije neophodan */
{
	*pret = NULL;
	while( stablo != NULL )
	{
		if( key == stablo->suma )
		{
			return stablo;
		}
		else
		{
			*pret = stablo;
			if( key < stablo->suma )
				stablo = stablo->levi;
			else
				stablo = stablo->desni;
		}
	}
	
	return NULL;
}

void lrotacija( cvor **c )
{
	cvor *poml, *pomd;
	if( *c != NULL )
	{
		
		poml = *c;
		pomd = poml->desni;
		
		poml->desni = pomd->levi;
		pomd->levi = poml;
		
		*c = pomd;

		poml->balans += - 1 - ( ( pomd->balans <= 0 )? 0 : pomd->balans ); // max
		pomd->balans += - 1 + ( ( poml->balans >= 0 )? 0 : poml->balans ); // min
	}
}

void drotacija( cvor **c )
{
	cvor *poml, *pomd;
	if( *c != NULL )
	{
		pomd = *c;
		poml = pomd->levi;
		
		pomd->levi = poml->desni;
		poml->desni = pomd;
		
		*c = poml;

		pomd->balans += 1 - ( ( poml->balans >= 0 )? 0 : poml->balans );
		poml->balans += 1 + ( ( pomd->balans <= 0 )? 0 : pomd->balans );
	}
}


int dodaj( cvor **koren, int suma )
{
	int inkrement, rezultat;
	cvor *t;

	rezultat = 0;
	t = *koren;
	
	if( t == NULL )
	{
		t = kreirajCvor( suma );
		rezultat = 1;
	}
	else
	{
		if( suma < t->suma )
			inkrement = - dodaj( &(t->levi), suma );
		else
			inkrement = dodaj( &(t->desni), suma );

		t->balans += inkrement;
		
		if( inkrement != 0 && t->balans != 0 )
		{
			if( t->balans < -1 )
			{
				if( t->levi->balans < 0 )
					drotacija( &t );
				else
				{
					lrotacija( &(t->levi) );
					drotacija( &t );
				}
			}
			else if( t->balans > 1 )
			{
				if( t->desni->balans > 0 )
					lrotacija( &t );
				else
				{
					drotacija( &(t->desni) );
					lrotacija( &t );
				}
			}
			else
				rezultat = 1;
		}
	}
	
	*koren = t;
	
	return rezultat;
}

void stampaj( cvor *c )
{
	if( c == NULL )
		return;
		
	if( c->levi != NULL )
		stampaj( c->levi );

												/* za ispravku: printf("%d ", c->suma );*/
	printf("%d(%d) ", c->suma, c->brPojav );	/* testiranje */
	
	if( c->desni != NULL )
		stampaj( c->desni );
}

cvor *najcesca( cvor *c )
{
	if( c == NULL )
		return NULL;
	else if( c->levi == NULL && c->desni == NULL )
	{
		return c;
	}
	else 
	{
		cvor *levi, *desni;
		
		levi = najcesca( c->levi );
		desni = najcesca( c->desni );
		
		if( c->brPojav > levi->brPojav )
		{
			if( c->brPojav > desni->brPojav )
				return c;
			else
				return desni;
		}
		else
		{
			if( levi->brPojav > desni->brPojav )
				return levi;
			else
				return desni;
		}
	}
}

int main()
{
	/*
	 * kada se ucita suma, proverava da li postoji u stablu sa 
	 * funkcijom trazi. Ukoliko trazi vrati null onda se ta suma dodaje
	 * u stablo, u suprotnom samo se povecava broj pojavljivanja
	 * sume u tom vracenom cvoru*/
	 
	int suma;
	cvor *c, *pret, *stablo;
	 
	stablo = NULL;
	 
	while( scanf("%d", &suma ) == 1 )
	{
		c = trazi( stablo, &pret, suma );
		
		if( c == NULL )
			dodaj( &stablo, suma );
		else
			c->brPojav += 1;
	}
	 stampaj( stablo );
	 printf("\n");

	 pret = najcesca( stablo );
	 printf("Najcesca suma %d sa %d pojavljivanja\n", pret->suma, pret->brPojav );
}
