#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 20

typedef struct cvor
{
	char *rec;
	int brPojavlj;
	int balans;
	struct cvor *levi;
	struct cvor *desni;
} cvor;

cvor *kreirajCvor( char *rec )
{
	cvor *novi = NULL;
	
	novi = (cvor *) malloc( sizeof( cvor ) );
	if( !novi )
	{
		printf("Neuspesno alociranje\n");
		exit(EXIT_FAILURE);
	}
	
	novi->rec = (char *) malloc( MAX_LEN );
	if( !novi )
	{
		printf("Neuspesno alociranje\n");
		exit(EXIT_FAILURE);
	}
	
	strcpy( novi->rec, rec );
	novi->brPojavlj = 1;
	novi->balans = 0;
	novi->levi = NULL;
	novi->desni = NULL;
	
	return novi;
}

int odredi( char *a, char *b )
{
	int i = 0;
	while( a[i] != '\0' && b[i] != '\0')
	{
		
		if( a[i] == b[i] )
		{
			i++;
		}
		else 
			return ( ( a[i] < b[i] )? -1 : 1 );
	}
		
	if( a[i] == '\0' )
		return -1;
	else
		return 1;
}

void lrotacija( cvor **c )
{
	if( *c != NULL )
	{
		cvor *poml, *pomd;
		
		poml = *c;
		pomd = poml->desni;
		
		poml->desni = pomd->levi;
		pomd->levi = poml;
		
		*c = pomd;
		
		poml->balans += -1 - ( ( pomd->balans <= 0 )? 0 : pomd->balans );
		pomd->balans += -1 + ( ( poml->balans >= 0 )? 0 : poml->balans );
	}
}

void drotacija( cvor **c )
{
	if( *c != NULL )
	{
		cvor *poml, *pomd;
		
		pomd = *c;
		poml = pomd->levi;
		
		pomd->levi = poml->desni;
		poml->desni = pomd;
		
		*c = poml;
		
		pomd->balans += 1 - ( ( poml->balans >= 0 )? 0 : poml->balans );
		poml->balans += 1 + ( ( pomd->balans <= 0 )? 0 : pomd->balans );
	}
}

int dodaj( cvor **koren, char *rec )
{
	int inkrement, rezultat;
	cvor *t;
	
	t = *koren;
	rezultat = 0;
	
	if( t == NULL )
	{
		t = kreirajCvor( rec );
		rezultat = 1;
	}
	else
	{
		if( odredi( rec, t->rec ) < 0 )
			inkrement = -dodaj( &(t->levi), rec );
		else
			inkrement = dodaj( &(t->desni), rec );
			
		t->balans += inkrement;
		
		if( inkrement != 0 && t->balans != 0 )
		{
			if( t->balans < -1 )
			{
				if( t->levi->balans < 0 )
					drotacija( &t );
				else
				{
					lrotacija( &(t->levi ) );
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

void stampajInOrder( cvor *t )
{
	if( t == NULL )
		return;
		
	if( t->levi != NULL )
		stampajInOrder( t->levi );
		
	printf("%s %d\n", t->rec, t->brPojavlj );
	
	if( t->desni != NULL )
		stampajInOrder( t->desni );
}

cvor *nadji( cvor *t, char *rec )
{
	while( t != NULL )
	{
		if( !strcmp( rec, t->rec ) )
			return t;
		else if( odredi( rec, t->rec ) < 0 )
			t = nadji( t->levi, rec );
		else
			t = nadji( t->desni, rec );
	}
	
	return NULL;
}

void izbaci( cvor **c, cvor **novi )
{
	int brPojavlj;
	cvor *t, *poml, *pomd, *temp;
	
	t = *c;
	
	if( t == NULL )
		return;
	
	poml = t->levi;
	pomd = t->desni;
		
	if( strlen( t->rec ) != 2 )
	{
		brPojavlj = t->brPojavlj;
		
		dodaj( novi, t->rec );
		
		temp = nadji( *novi, t->rec );
		temp->brPojavlj = brPojavlj;
			
		free(t->rec);
		free(t);
	}
	
	izbaci( &poml, novi );
	izbaci( &pomd, novi );
}

cvor *nadjiNajfrek( cvor *t )
{
	cvor *levi, *desni, *naj;
	
	if( t == NULL )
		return NULL;
	
	if( !t->levi && !t->desni )
		return t;
	else if( t->levi && t->desni )
	{
		levi = nadjiNajfrek( t->levi );
		desni = nadjiNajfrek( t->desni );

		if( levi->brPojavlj > desni->brPojavlj )
			naj = levi;
		else
			naj = desni;
	}
	else if( !t->levi )
		naj = t->desni;
	else
		naj = t->levi;

	if( t->brPojavlj > naj->brPojavlj )
			naj = t;

	return naj;
}

int main()
{
	int c, i;
	char buf[MAX_LEN];
	
	cvor *stablo, *temp, *novo;
	
	i = 0;
	stablo = NULL;
	novo = NULL;
	
	while( ( c = getchar() ) != EOF )
	{
		if( c >= 'a' && c <= 'z' )
			buf[i++] = c; 
		else if( c >= 'A' && c <= 'Z' )
			buf[i++] = c + 'a' - 'A'; 
		else if( i != 0 )
		{
			buf[i] = '\0';
			temp = nadji( stablo, buf );
			if( temp == NULL )
				dodaj( &stablo, buf );
			else
				temp->brPojavlj = temp->brPojavlj + 1;
				
			i = 0;
		}
	}
	
	stampajInOrder( stablo );
	printf("\n");

	izbaci( &stablo, &novo );
	stampajInOrder( novo );
	
	temp = nadjiNajfrek( novo );
	if( temp )
		printf("Najfrekventnija rec: %s %d\n", temp->rec, temp->brPojavlj );
	else
		printf("Stablo je prazno\n");
}
