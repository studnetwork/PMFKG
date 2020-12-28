#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct drvo
{
	char naziv[30];
	struct drvo *levi , *desni;
}Drvo;

#define novi(x)x=(Drvo*)malloc(sizeof(Drvo))

void Dodaj(Drvo **p, Drvo *temp)
{
	Drvo *pom,*pom2=NULL;
	pom=*p;
	if(pom==NULL) *p=temp;
	else
	{
		pom=*p;
		while(pom)
		{
			pom2=pom;
			if(strcmp(pom->naziv,temp->naziv)<0) pom=pom->desni;
			else pom=pom->levi;
		}
		if(strcmp(pom2->naziv,temp->naziv)<0) pom2->desni=temp;
			else pom2->levi=temp;
		
	}
}


Drvo* Form()
{
	int n,i;
	//char naz[30];
	Drvo *temp,*p=NULL;
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		novi(temp);
		if(!temp)
		{
			printf("Greska pri alokaciji");
			exit(0);
		}
		
		//scanf("%s",naz);
		//temp->naziv=(char*)malloc(strlen(naz)+1);
		//strcpy(temp->naziv,naz);
		scanf("%s",temp->naziv);
		temp->levi=temp->desni=NULL;
		Dodaj(&p,temp);
	}
	
	return p;
}

void Ispis(Drvo *p)
{
	if(p)
	{
		if(p->levi) Ispis(p->levi);
		printf("%s \n",p->naziv);
		if(p->desni) Ispis(p->desni);
	}
	else printf("Stablo je prazno");
}

int NaKojojDubini(Drvo *p, char *ime)
{
	int n=0;
	if(p)
	{
		if(strcmp(p->naziv,ime)==0) return 1;
		else
		{
			if(strcmp(p->naziv,ime)<0) n=NaKojojDubini(p->desni,ime );
			else n=NaKojojDubini(p->levi,ime);
		}
		
	}
		if(n) return ++n;
		else return 0;
}



void Listovi(Drvo *poc, Drvo *p, int *niz, int *i)
{
	int br;
	if(p)
	{
		if(p->levi==NULL && p->desni==NULL)
		{
		br=NaKojojDubini(poc,p->naziv);
		niz[(*i)++]=br;
		//printf("%d  ",br) ;
		}
		else
		{
		Listovi(poc,p->levi, niz, i);
		Listovi(poc,p->desni, niz, i);
		}
		
	}
	else return; 
	
	
}

int main()
{
	Drvo *p;
	int niz[50],i=0,j,k,id=0;
	//int vr;
	p=Form();
	Ispis(p);
	//vr=NaKojojDubini(p,"lazar");
	//printf("n=%d\n",vr);
	// prosledim niz i indeks
	Listovi(p,p, niz, &i);
	for(j=0;j<i;j++)
	{
		printf("%d  ",niz[j]) ;
	}
	
	
	printf("\n");
	
	j=i-1;
	for(k=0 ;k<j; k++, j--)
	{
		if(niz[k] != niz[j]) id=1;
		
	}
	
	
	if(id) printf("Nije palindrom\n");
	else printf("Jeste palindrom\n");
	return 0;
}
