#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum{CRVENA,CRNA};
typedef struct 
{
	int dan,m,god;
}Datum;

typedef struct drvo
{
	int id, boja, brGlasova,ukupno;
	Datum dat[20];
	char ime[20];
	struct drvo *levi,*desni,*roditelj;
}Drvo;

#define novi(x) x=(Drvo*)malloc(sizeof(Drvo))
//#define novid(y) y=(Datum*)malloc(sizeof(Datum))

int DatProv (Drvo *t1, Drvo *t2) // vraca 1 ako je prvi manji
{
	
	if(t1->dat[0].god < t2->dat[0].god) return 1;
	else if( t1->dat[0].god == t2->dat[0].god && t1->dat[0].m < t2->dat[0].m) return 1;
	else if (t1->dat[0].god == t2->dat[0].god && t1->dat[0].m == t2->dat[0].m && t1->dat[0].dan <t2->dat[0].dan) return 1;
	
	return 0;
}

void lrotacija(Drvo **p)
{
	Drvo *x,*y;
	x=*p;
	y=x->desni;
	x->desni=y->levi;
	if(y->levi) y->levi->roditelj=x;
	y->roditelj=x->roditelj;
	if(x->roditelj)
	{
		if(x== x->roditelj->levi) x->roditelj->levi=y;
		else x->roditelj->desni=y;
	}
	x->roditelj=y;
	y->levi=x;
	
	*p=y;
}

void drotacija(Drvo **p)
{
	Drvo *x,*y;
	y=*p;
	x=y->levi;
	y->levi=x->desni;
	if(x->desni) x->desni->roditelj=y;
	x->roditelj=y->roditelj;
	if(y->roditelj)
	{
		if(y==y->roditelj->levi) y->roditelj->levi=x;
		else y->roditelj->desni=x;
	}
	y->roditelj=x;
	x->desni=y;
	*p=x;
	
}

void bojefix(Drvo **p, Drvo *z)
{
	Drvo *y,*t;
	while (z->roditelj && z->roditelj->boja==CRVENA)
	{
		if(z->roditelj==z->roditelj->roditelj->levi)
		{
			y=z->roditelj->roditelj->desni;
			if((y) && y->boja==CRVENA)
			{
				y->boja=CRNA;
				z->roditelj->boja=CRNA;
				z->roditelj->roditelj->boja=CRVENA;
				z=z->roditelj->roditelj;
			}
			else
			{
				if(z==z->roditelj->desni)
				{
					z=z->roditelj;
					lrotacija(&z);
					if(!z->roditelj) *p=z;
					z=z->levi;
				}
				z->roditelj->boja=CRNA;
				z->roditelj->roditelj->boja=CRVENA;
				t=z->roditelj->roditelj;
				drotacija(&t);
				if(!t->roditelj) *p=t;
			}
		}
		else
		{
			y=z->roditelj->roditelj->levi;
			if((y) && y->boja==CRVENA)
			{
				y->boja=CRNA;
				z->roditelj->boja=CRNA;
				z->roditelj->roditelj->boja=CRVENA;
				z=z->roditelj->roditelj;
			}
			else
			{
				if(z==z->roditelj->levi)
				{
					z=z->roditelj;
					drotacija(&z);
					if(!z->roditelj) *p=z;
					z=z->desni;
				}
				z->roditelj->boja=CRNA;
				z->roditelj->roditelj->boja=CRVENA;
				t=z->roditelj->roditelj;
				lrotacija(&t);
				if(!t->roditelj) *p=t;
			}
			
		}
	}
	(*p)->boja=CRNA;
}


void Dodaj(Drvo **p, Drvo *temp)
{
	Drvo *x,*y;
	y=NULL;
	x=*p;
	while(x)
	{
		y=x;
		if( DatProv(temp,x) ) x=x->levi;
		else x=x->desni;
	}
	temp->roditelj=y;
	if(y==NULL) *p=temp;
	else
	{
		if( DatProv(temp,y)) y->levi=temp;
		else y->desni=temp;
	}
	bojefix(p,temp);
}


Drvo* Form ()
{
	int n,i,j;
	scanf("%d",&n);
	Drvo *p=NULL, *temp;
	for(i=0;i<n;i++)
	{
		novi(temp);
		if(!temp) {
					printf("Greska\n");
					exit(0);
		}
		
		scanf("%d%d",&temp->id,&temp->brGlasova);
		for(j=0;j<temp->brGlasova;j++)
		scanf("%d%d%d",&temp->dat[j].dan, &temp->dat[j].m, &temp->dat[j].god);
		scanf("%s",temp->ime);
		temp->ukupno=temp->brGlasova;
		temp->levi=temp->desni=NULL;
		temp->roditelj=NULL;
		temp->boja=CRVENA;
		Dodaj(&p,temp);
		
		
	}
	return p;
	
	
}

void Ispis (Drvo *p)
{
	if(p)
	{
		int i;
		if(p->levi) Ispis(p->levi);
		
		printf("id=%d br=%d %s\n",p->id,p->brGlasova,p->ime);
		//printf("%d %d %d ", p->dat[0].dan, p->dat[0].m, p->dat[0].god);
		for(i=0; i<p->brGlasova; i++)
		printf("%d %d %d |", p->dat[i].dan, p->dat[i].m, p->dat[i].god);
		if(p->boja ==CRVENA) printf("(CRVENA)\n");
		else printf("(CRNA)\n");
		
		if(p->desni) Ispis(p->desni);
	}
	else printf("Stablo je prazno\n");
}


  
void padding ( char ch, int n )
{
  int i;
  for ( i = 0; i < n; i++ )
    putchar ( ch );
}
void structure ( struct drvo *root, int level )
{
 
  if ( root == NULL ) {
    padding ( '\t', level );
    puts ( "~" );
  }
  else {
    structure ( root->desni, level + 1 );
    padding ( '\t', level );
    printf ( "%d\n", root->id );
    structure ( root->levi, level + 1 );
  }
}




void IzbaciDat(Drvo *p)
{
	int i,j,k,n,l,id=0;
	n=p->brGlasova;
	for(i=0;i<n-1;i++)
	{
		id=0;
		for(j=i+1;j<n;j++)
		{
			if(p->dat[i].god == p->dat[j].god && p->dat[i].m == p->dat[j].m && p->dat[i].dan == p->dat[j].dan)
			{
				id=1;
				for(k=j;k<n-1; k++)
				p->dat[k]=p->dat[k+1];
				p->brGlasova--;
				p->ukupno--;
				n--;
				j--;
				
			}
		}
		if(id==1)//izbaci i njega
		{
			for(l=i;l<n-1; l++)
			p->dat[l]=p->dat[l+1];
			
			n--;
			p->brGlasova--;
			p->ukupno--;
			i--;
		}
		
	}
}


void Provera(Drvo *p)
{
	if(p)
	{
		IzbaciDat(p);
		Provera(p->levi);
		Provera(p->desni);
	}
}

void SrediGlasove (Drvo *koren, Drvo *p)
{
	if(koren)
	{
		if(strcmp(p->ime,koren->ime)==0 && p->id!=koren->id)
		{
			p->ukupno = p->ukupno + koren->brGlasova;
			//koren->ukupno= koren->ukupno+ p->brGlasova;	
		}
		SrediGlasove(koren->levi,p);
		SrediGlasove(koren->desni,p);
	}
}

void Brisi (Drvo **p, Drvo *q)
{
	if(q)
	{
		Drvo *pom;
		int i;
		if (q->brGlasova>0)
		{
			novi(pom);
			pom->id=q->id;
			pom->brGlasova=q->brGlasova;
			for(i=0;i<q->brGlasova;i++)
			{
				pom->dat[i].dan=q->dat[i].dan;
				pom->dat[i].m=q->dat[i].m;
				pom->dat[i].god=q->dat[i].god;
			}
				strcpy(pom->ime,q->ime);
				pom->ukupno=q->ukupno;
				pom->levi=pom->desni=NULL;
				pom->roditelj=NULL;
				pom->boja=CRVENA;
				Dodaj(p,pom);
		}
			
			Brisi(p,q->levi);
			Brisi(p,q->desni);
		}
	}

void ProdjiKrozGlasove(Drvo *koren, Drvo *p, Drvo **max)
{
	if(p)
	{
		SrediGlasove(koren,p);
		if((*max)==NULL || p->ukupno > (*max)->ukupno)
		*max=p;
		ProdjiKrozGlasove(koren,p->levi, max);
		ProdjiKrozGlasove(koren, p->desni, max);
	}
}


int main()
{
	Drvo *p,*q=NULL, *naj=NULL;
	p=Form();
	Ispis(p);
	structure(p,1);
	Provera(p);
	Brisi(&q,p);
	Ispis(q);
	structure(q,1);
	ProdjiKrozGlasove(q,q,&naj);
	printf("Najbolji %s broj glasova=%d \n",naj->ime, naj->ukupno);
	
	return 0;
}

