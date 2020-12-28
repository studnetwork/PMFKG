#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista
{
	char *reg;
	int pozicija;
	int izlaz;
	struct lista *sled;
}Lista;

#define novi(x)x=(Lista*)malloc(sizeof(Lista))


void Dodaj(Lista **p, Lista *temp)
{
	Lista *pom,*pom3,*pom2;
	pom=*p;
	if(pom==NULL)
	{
		temp->sled=temp;
		*p=temp;
	}
	else
	{
		pom=*p;
		if(pom->pozicija> temp->pozicija)//pomeramo glavu
		{
			temp->sled=pom;
			pom3=pom;
			while(pom3->sled!=pom) pom3=pom3->sled;
			pom3->sled=temp;
			*p=temp;
		}
		
		else{
		pom2=(*p);
		pom=(*p)->sled;
		while(pom!=*p && pom->pozicija<temp->pozicija) 
		{
			pom2=pom;
			pom=pom->sled;
			
		}
		
		temp->sled=pom2->sled;
		pom2->sled=temp;
	}
		
	}
}

Lista* Form()
{
	int n,i;
	Lista *p=NULL, *temp;
	char rec[20];
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
			novi(temp);
		if(!temp)
		{
			printf("Greska pri alokaciji");
			exit(0);
		}
		
		scanf("%s",rec);
		temp->reg=(char*)malloc(strlen(rec)+1);
		strcpy(temp->reg,rec);
		scanf("%d",&temp->pozicija);
		scanf("%d",&temp->izlaz);
		temp->sled=NULL;
		Dodaj(&p,temp);
		
		
	}
	
	return p;
}

void Ispis(Lista *p)
{
	Lista *pom=p;
	if(p)
	{
		do{
			printf("tablica:%s  poz:%d  izlaz:%d \n", pom->reg, pom->pozicija, pom->izlaz);
			pom=pom->sled;
		}while(pom!=p);
	}
	else printf("Lista je prazna\n");
}

int DodajNov(Lista **p, Lista *temp )
{
	if((*p))
	{
		int prov=0 , vrednost1, vrednost2;
		vrednost1=temp->pozicija -5;
		vrednost2=temp->pozicija+5;
		Lista *pom;
		pom=*p;
		do
		{
			if(pom->pozicija >= vrednost1 && pom->pozicija <= vrednost2) prov=1; 
			
			pom=pom->sled;
		}while(pom!=(*p));
		
		if(prov==0) // moze da udje u kruzni tok
		{
			 Dodaj(p,temp);
			 return 1;
		}
		else return 0;
	
	}
	else return -1;
}

Lista* Izbaci(Lista **p, Lista *temp)
{
	Lista *pom,*preth=NULL, *vrati, *pom3;
	int prov=1;

	pom=*p;
	if(pom)
	{
			if(pom==temp)// izbacujemo prvi
			{
				pom3=pom;
				while(pom3->sled != pom) pom3=pom3->sled;
				if(pom3->sled==pom3) *p=NULL;
				else
				{
					pom3->sled=pom->sled;
					(*p)=(*p)->sled;
					
				}
				free(temp);
				vrati=*p;
			}
			else
			{
				preth=*p;
				pom=(*p)->sled;
				prov=1;
				while(pom!=(*p) && prov)
				{
					if(pom==temp)
					{
						prov=0;
						preth->sled=pom->sled;
						vrati=preth->sled;
						free(temp);
						
					}
					
					else{
						preth=pom;
						pom=pom->sled;
					}
					
				}
			}
			
			return vrati;
	}
	else return NULL;
}

void NovaVozila (Lista **p)
{
	int m, id=1,prov;
	Lista *temp, *pom;
	char rec[30];
	scanf("%d",&m);
	while ((*p))
	{
		if(id==1 && m>0)
		{
			m--;
			if(m==0)id=0;
			novi(temp);
		if(!temp)
		{
			printf("Greska pri alokaciji");
			exit(0);
		}
		
		scanf("%s",rec);
		temp->reg=(char*)malloc(strlen(rec)+1);
		strcpy(temp->reg,rec);
		scanf("%d",&temp->pozicija);
		scanf("%d",&temp->izlaz);
		}
		
	
		if(m>0 || (m==0 && id==0)) id=DodajNov(p,temp);
		if (m<0)id=0;
		if (m==0 && id==1)m=-1;
		
		// sve pomeramo za 3
		pom=*p;
		if(pom && id==0)
		{
			do{
				prov=0;
				pom->pozicija += 3; 
				if(pom->pozicija >= 360) pom->pozicija= pom->pozicija%10;
				if(pom->izlaz<=pom->pozicija && pom->pozicija<(pom->izlaz+3)){  if(pom==(*p))prov=1; pom=Izbaci(p,pom);}
				
				else pom=pom->sled;
			}while((pom && prov) || (pom && pom!=(*p)));
		
		}
		if((*p))
		{
		printf("------------------------------\n");
		Ispis(*p);
		}
		else printf("Zavrseno\n");
			
	}
		
		
	
}


int main()
{
	Lista *p;
	p=Form();
	Ispis(p);
	NovaVozila(&p);


	return 0;
}
