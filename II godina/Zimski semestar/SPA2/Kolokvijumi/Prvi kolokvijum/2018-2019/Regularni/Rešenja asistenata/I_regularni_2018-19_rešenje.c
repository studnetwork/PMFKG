#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define novi(x) x=(struct lista*)malloc(sizeof(struct lista))

struct lista
{
	int tip;
	char zona[10];
	int ogranicenje_min;
	int zauzetost;
	char tablice[20];	
	int vreme_h;
	int vreme_min;
	struct lista *sledeci;
};



void dodaj(struct lista **glava, int k)
{
	struct lista *temp, *pom;
	char s[20];
	novi(temp);
	if(temp==NULL)
	{
		printf("greska pri alokaciji memorije\n");
		exit(0);
	}
	
	temp->tip=k;
	if(k==1)
	{
		scanf("%d", &temp->zauzetost);
		getchar();
		if(temp->zauzetost==1)
		{
			fgets(s,20, stdin);
			s[strlen(s)-1]='\0';
			strcpy(temp->tablice, s);
		}
	}
	else
	{
		fgets(s,10,stdin);
		s[strlen(s)-1]='\0';
		strcpy(temp->zona,s);
		scanf("%d", &temp->ogranicenje_min);
		scanf("%d", &temp->zauzetost);
		getchar();
		if(temp->zauzetost==1)
		{
			fgets(s,20, stdin);
			s[strlen(s)-1]='\0';
			strcpy(temp->tablice, s);
			scanf("%d", &temp->vreme_h);
			scanf("%d", &temp->vreme_min);		
		}
	}
	
	
	temp->sledeci=NULL;
	
	if(*glava==NULL)
	{
		*glava=temp;
	}
	else
	{
		pom=*glava;
		while(pom->sledeci!=NULL) 	pom=pom->sledeci;
		
		pom->sledeci=temp;
	}
	
}



struct lista *form_list(struct lista **q, int n)
{
	struct lista *p;
	p=NULL;
	int i, k;
	
	for(i=0; i<n; i++)
	{
		scanf("%d", &k);
		getchar();
		if(k==1)
		{
			dodaj(q, k);
		}
		else
		{
			dodaj(&p, k);
		}
		
	}
	
	
	
	
	
	return (p);
}



void ispis(struct lista *glava)
{
	printf("\n");
	if(glava==NULL)
		printf("LISTA JE PRAZNA\n");
	else
	{
		while(glava!=NULL)
		{
			printf("Tip: %d\n", glava->tip);
			if(glava->tip==1)
			{
				printf("Zauzeto: %d\n", glava->zauzetost);
				if(glava->zauzetost==1)
				{
					printf("Tablice: %s \n", glava->tablice);
				}
			}
			else
			{
				printf("Zona: %s\n", glava->zona);
				printf("Vremensko ogranicenje: %d\n", glava->ogranicenje_min);
				printf("Zauzeto: %d\n", glava->zauzetost);
				if(glava->zauzetost==1)
				{
					printf("Tablice: %s \n", glava->tablice);
					printf("Vreme parkiranja u satima: %d\n", glava->vreme_h);
					printf("Vreme parkiranja u minutima: %d\n", glava->vreme_min);
				}
			}
			
			printf("\n");
			glava=glava->sledeci;
		}
	}
	
	printf("\n");
}


struct lista* reorganizuj(struct lista *glava)
{
	struct lista *pom1, *preth, *min, *pom2, *pom3, *temp, *pom4;
	int vreme_minimum, vreme;
	struct lista *q, *t;
	q=NULL;
	t=NULL;
	
	
	while(glava!=NULL)
	{
		pom1=glava;
		min=glava;
		vreme_minimum=min->vreme_h*60+min->vreme_min;
		preth=NULL;
		pom2=pom1->sledeci;
		if(min->zauzetost==1)
		{
			while(pom2!=NULL)
			{
				if(pom2->zauzetost==1)
				{
	
				vreme=pom2->vreme_h*60+pom2->vreme_min;
				if((strcmp(pom2->zona,min->zona)<0) || ((strcmp(pom2->zona, min->zona)==0) && (vreme<vreme_minimum)))
				{
					min=pom2;
					vreme_minimum=vreme;
					preth=pom1;
				}
				}
				pom1=pom2;
				pom2=pom2->sledeci;	
			}
			
			if(preth==NULL)
				glava=glava->sledeci;
			else
				preth->sledeci=min->sledeci;
			
			min->sledeci=NULL;
			
			if(q==NULL)
			{
				q=min;
			}
			else
			{
				pom3=q;
				while(pom3->sledeci!=NULL) pom3=pom3->sledeci;
				
				pom3->sledeci=min;
			}
				
			
		}
		else
		{
			temp=glava;
			glava=glava->sledeci;
			if(t==NULL)
			{
				temp->sledeci=NULL;
				t=temp;
			}
			else
			{
				pom4=t;
				while(pom4->sledeci!=NULL) pom4=pom4->sledeci;
				
				temp->sledeci=NULL;
				pom4->sledeci=temp;
				
			}
			
		}
	}
	
	while(t!=NULL)
	{
		temp=t;
		t=t->sledeci;
		
		pom3=q;
		while((pom3->sledeci) && (strcmp(pom3->sledeci->zona,temp->zona)!=0)) pom3=pom3->sledeci;
		while((pom3->sledeci) && ((strcmp(pom3->sledeci->zona,temp->zona)==0) && pom3->sledeci->zauzetost==1)) pom3=pom3->sledeci;
		
		if(pom3->sledeci!=NULL)
		{
			temp->sledeci=pom3->sledeci;		
			pom3->sledeci=temp;
		}
		else
		{
			temp->sledeci=NULL;
			pom3->sledeci=temp;
		}
		
		
	}
	
	
	return (q);
}


void prebaci(struct lista **grad, struct lista *javni, int vreme1)
{
	struct lista *pom, *preth, *pom2;
	
	preth=NULL;
	pom=*grad;
	int vreme2;
	int ind;
	
	while(pom!=NULL)
	{
		ind=0;
		if(pom->zauzetost==1)
		{
		vreme2=pom->vreme_h*60+pom->vreme_min+pom->ogranicenje_min;
		if(vreme2 < vreme1)
		{
			pom2=javni;
			while(pom2!=NULL)
			{
				if(pom2->zauzetost==0)
				{
					pom2->zauzetost=1;
					strcpy(pom2->tablice, pom->tablice);
					
					if(preth==NULL)
					{
						*grad=(*grad)->sledeci;
						pom=*grad;
					}
					else
					{
						preth->sledeci=pom->sledeci;
						pom=preth->sledeci;
					}
					
					
					ind=1;
					break;
				}
				
				
					pom2=pom2->sledeci;
			}	
			
			
			
		}
		
		}
		
		if(ind==0)
		{
			preth=pom;
			pom=pom->sledeci;
		}
		
	}
	
	
	
	
}



int main()
{
	struct lista *grad=NULL, *javni=NULL;
	
	int n;
	scanf("%d", &n);
	getchar();
	grad=form_list(&javni, n);
	printf("\n--------\n");
	printf("GRADSKI:\n");
	ispis(grad);
	printf("\n--------\n");
	printf("JAVNI:\n");
	ispis(javni);
	printf("\n--------\n");
	
	grad=reorganizuj(grad);
	ispis(grad);
	printf("\n--------\n");
	
	int h,m,vreme1;
	scanf("%d", &h);
	scanf("%d", &m);	
	vreme1=h*60+m;
	prebaci(&grad, javni, vreme1);
	
	printf("\n--------\n");
	printf("GRADSKI:\n");
	ispis(grad);
	printf("\n--------\n");
	printf("JAVNI:\n");
	ispis(javni);
	printf("\n--------\n");
	
}
