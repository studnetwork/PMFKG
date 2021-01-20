#include<stdio.h>
#include<stdlib.h>

#define COUNT 10

struct stablo 
{
	int cvor;
	int levo_br;
	struct stablo *levi,*desni;
};

void ispis_2d(struct stablo *koren, int space) 
{ 
    if (koren == NULL) return; // Prazno stablo
  
    space += COUNT; // Povecavanje distance izmedju svakog nivoa
   
    ispis_2d(koren->desni, space); 
  
    printf("\n"); 
    for (int i = COUNT; i < space; i++) printf(" "); 
    
    printf("%d(%d)\n", koren->cvor,koren->levo_br); 
  
    ispis_2d(koren->levi, space); 
}

struct stablo* kreiraj_novi(int val)
{
	struct stablo *novi = malloc(sizeof(struct stablo));
	
	novi->cvor = val;
	novi->levo_br = 0;
	novi->levi = novi->desni = NULL;
	
	return novi;
}

void dodaj(struct stablo **koren, int val)
{
	struct stablo *novi;
	
	novi = kreiraj_novi(val);
	
	if(*koren == NULL) *koren = novi;
	
	else
	{
		struct stablo *p,*pret;
		p = *koren;
		
		while(p)
		{
			if(p->cvor > val)
			{
				p->levo_br++;
				pret = p;
				p = p->levi;
			}
			
			else
			{
				pret = p;
				p = p->desni;
			}
		}
		
		if(pret->cvor > val) pret->levi = novi;
		else pret->desni = novi;
	}
}

void formiraj(struct stablo **koren, int n)
{
	int val;
	
	for(int i = 0; i < n; i++)
	{
		scanf("%d",&val);
		dodaj(koren,val);
	}
}

int rang_cvora(struct stablo *p, int val)
{
	if(p == NULL) return 0;
	
	if(p->cvor == val) return p->levo_br;
	if(val < p->cvor) return rang_cvora(p->levi, val);

	return p->levo_br + 1 + rang_cvora(p->desni, val);
}

void stampaj_rang(struct stablo *koren, struct stablo *p)
{
	if(p->desni) stampaj_rang(koren, p->desni);
	printf("%d -> %d\n",p->cvor,rang_cvora(koren,p->cvor));
	if(p->levi) stampaj_rang(koren, p->levi);
}

struct stablo* pronadji(struct stablo *p, struct stablo **prethodni, int val)
{
	if(p == NULL) return NULL;
	
	*prethodni = NULL;
	
	while(p)
	{
		if(p->cvor == val) return p;
		
		else
		{
			*prethodni = p;
			
			if(p->cvor > val) 
			{
				p->levo_br--; // Smanjuje se broj levih potomaka samo kada ide kroz leve grane
				p = p->levi;
			}
			
			else p = p->desni;
		}
	}
	
	return NULL;
}

struct stablo* azuriraj(struct stablo *koren, int val)
{
	struct stablo *trazeni, *pret, *pom, *pom1;
	
	trazeni = pronadji(koren,&pret,val);
	
	if(trazeni== NULL)
	{
		printf("Cvor ne postoji.\n");
		return(koren);
	}
	
	if(trazeni->levi != NULL && trazeni->desni != NULL)  //brisanje cvora koji ima oba potomka 
	{
		pom1 = trazeni->levi;
		while(pom1->desni != NULL) pom1 = pom1->desni;
		pom1->desni=trazeni->desni;
		
		pom = trazeni->levi;
	}
	
	else if(trazeni->levi == NULL && trazeni->desni != NULL) //brisanje cvora koji ima samo desnog potomka
	{
		pom = trazeni->desni; 
	}
	
	else if( trazeni->levi != NULL && trazeni->desni == NULL) //brisanje cvora koji ima samo levog potomka
	{
		pom = trazeni->levi;
	}
	
	else if(trazeni->levi == NULL && trazeni->desni == NULL) //brisanje cvora koji nema ni jednog potomka
	{
		pom= NULL;
	}
	
	if(pret != NULL)
	{
		if(pret->levi == trazeni) pret->levi = pom;
		else pret->desni = pom;
	}
	
	else
	{
		koren = pom;
	}
	
	free(trazeni);
	return koren;
}

int main()
{
	struct stablo *koren = NULL;
	int n;
	
	scanf("%d",&n);
	
	formiraj(&koren,n);
	ispis_2d(koren,0);
	
	printf("\nRangovi svih cvorova stabla u formatu (cvor -> rang):\n");
	stampaj_rang(koren,koren);
	
	koren = azuriraj(koren,4);
	ispis_2d(koren,0);
	
	return 0;
}
