//Resio: Ljubomir Matovic 58/2020
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define KOMBI "KOMBI"
#define KAMION "KAMION"
#define GRESKA 0.000001

typedef struct CVOR{
    int id;
    int x,y;
    float tezina;
    char tip[7];
    int balans;
    struct CVOR *levi,*desni;
}CVOR;

typedef struct LISTA{
    int v;
    float rastojanje;
    char tip[7];
    struct LISTA *sledeci;
}LISTA;

LISTA* alocirajListu(int v,float r,char tip[7]){
    LISTA *temp=(LISTA*)malloc(sizeof(LISTA));
    if(temp==NULL){
        printf("GRESKA\n");
        exit(1);
    }
    temp->v=v;
    temp->rastojanje=r;
    strcpy(temp->tip,tip);
    temp->sledeci=NULL;
    return temp;
}
void dodajUListu(LISTA **pocetak,LISTA **kraj,int v,float rastojanje,char tip[7]){
    LISTA *temp=alocirajListu(v,rastojanje,tip);
    if(*pocetak==NULL){
        *pocetak=*kraj=temp;
    }else{
        (*kraj)->sledeci=temp;
        *kraj=temp;
    }
}
float odrediTezinu(int x,int y){
    return sqrt(pow(x,2)+pow(y,2));
}

CVOR* alocirajCvor(int id,int x,int y,char tip[7]){
    CVOR *temp=(CVOR*)malloc(sizeof(CVOR));
    if(temp==NULL){
        printf("GRESKA\n");
        exit(1);
    }
    temp->id=id;
    temp->x=x;
    temp->y=y;
    temp->tezina=odrediTezinu(x,y);
    strcpy(temp->tip,tip);
    temp->balans=0;
    temp->levi=temp->desni=NULL;
    return temp;
}

int dubina(CVOR *root){
    if(root==NULL)
    return 0;
    if(root->levi==NULL && root->desni==NULL){
        return 1;
    }
    int dl=dubina(root->levi),dd=dubina(root->desni);
    if(dl>dd)
    return dl+1;
    return dd+1;
}

void odrediBalans(CVOR **root){
    CVOR *p=*root;
    p->balans=dubina(p->desni)-dubina(p->levi);
    *root=p;
}

void lrotacija(CVOR **root){
    CVOR *l=*root;
    CVOR *d=l->desni;
    l->desni=d->levi;
    d->levi=l;
    odrediBalans(&l);
    odrediBalans(&d);
    *root=d;
}
void drotacija(CVOR **root){
    CVOR *d=*root;
    CVOR *l=d->levi;
    d->levi=l->desni;
    l->desni=d;
    odrediBalans(&l);
    odrediBalans(&d);
    *root=l;
}

int sredi(CVOR **root){
    CVOR *p=*root;
    int rezlutat=0;
    if(p){
        if(p->balans<-1){
            if(p->levi->balans>=0){
                lrotacija(&(p->levi));
            }
            drotacija(&p);
        }else if(p->balans>1){
            if(p->desni->balans<=0){
                drotacija(&(p->desni));
            }
            lrotacija(&p);
        }else rezlutat=1;
    }
    *root=p;
    return rezlutat;
}

void padding ( char ch, int n )
{
  int i;
  for ( i = 0; i < n; i++ )
    putchar ( ch );
}
void ispis ( CVOR *root, int level )
{
  int i;
  if ( root == NULL ) {
    padding ( '\t', level );
    puts ( "~" );
  }
  else {
    ispis ( root->desni, level + 1 );
    padding ( '\t', level );
    printf ( "%d %s %.6f\n", root->id, root->tip,root->tezina);
    ispis ( root->levi, level + 1 );
  }
}
float apsolutna(float a){
    if(a<0)return -a;
    return a;
}

int dodaj(CVOR **root,int id,int x,int y,char tip[20]){//ispravka
    if((*root)==NULL){
        CVOR *temp=alocirajCvor(id,x,y,tip);
        *root=temp;
        return 1;
    }else{
        int rezlutat=0,inkrement;
        CVOR *p=*root;
        float t=odrediTezinu(x,y);
        if(p->tezina-t>GRESKA|| (apsolutna(p->tezina - t)<=GRESKA && strcmp(p->tip,KAMION)==0 && strcmp(tip,KOMBI)==0))//abs(p->tezina-t)<0.0001 <=> p->tezina==t
        inkrement=-dodaj(&(p->levi),id,x,y,tip);
        else inkrement=dodaj(&(p->desni),id,x,y,tip);
        p->balans+=inkrement;
        if(inkrement!=0 && p->balans!=0)
        rezlutat=sredi(&p);
        *root=p;
        return rezlutat;
    }
}

void nadjiZaBrisanje(CVOR *root,char tip[7],float rastojanje,LISTA **pocetak,LISTA **kraj){
    if(root==NULL)
    return;
    if(strcmp(root->tip,tip) || root->tezina>rastojanje)
        dodajUListu(pocetak,kraj,root->id,root->tezina,root->tip);
    if(root->levi)
        nadjiZaBrisanje(root->levi,tip,rastojanje,pocetak,kraj);
    if(root->desni)
        nadjiZaBrisanje(root->desni,tip,rastojanje,pocetak,kraj);
}

CVOR *nadjiLevi(CVOR **root){
    CVOR *t=NULL;
    CVOR *p=*root;
    if(p->levi)
    t=nadjiLevi(&(p->levi));
    else{
        t=p;
        p=p->desni;
    }
    if(p){
        odrediBalans(&p);
        sredi(&p);
    }
    *root=p;
    return t;
}


CVOR* obrisi(CVOR *root,int id,float rastojanje,char tip[7]){//ispravka
    if(root==NULL)
    return NULL;
    if(root->id==id){
        if(root->levi==NULL && root->desni==NULL){
            free(root);
            return NULL;
        }else if(root->levi && root->desni==NULL){
            CVOR *temp=root->levi;
            free(root);
            return temp;
        }else if(root->levi==NULL && root->desni){
            CVOR *temp=root->desni;
            free(root);
            return temp;
        }else{
            CVOR *temp=nadjiLevi(&(root->desni));
            root->id=temp->id;
            strcpy(root->tip,temp->tip);
            root->x=temp->x;
            root->y=temp->y;
            root->tezina=temp->tezina;
            free(temp);
        }
    }else if(root->tezina-rastojanje<-GRESKA || (apsolutna(root->tezina - rastojanje)<=GRESKA && strcmp(root->tip,KOMBI)==0 && strcmp(tip,KAMION)==0) )root->desni=obrisi(root->desni,id,rastojanje,tip);
    else root->levi=obrisi(root->levi,id,rastojanje,tip);
    odrediBalans(&root);
    sredi(&root);
    return root;
}
CVOR* najblizi(CVOR *root){
    CVOR *t=NULL;
    if(root->levi)
    t=najblizi(root->levi);
    else{
        t=root;
    }
    return t;
}
int main(){
    int n;
    int id,x,y,i;
    char tip[7];
    float rastojanje;
    CVOR *root=NULL;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%d %d %d %s",&id,&x,&y,tip);
        dodaj(&root,id,x,y,tip);
    }
    scanf("%f %s",&rastojanje,tip);//premestio sam ovaj scanf ovde samo da mi nista ne bi ispisivalo dok ne ucitam sve 
    ispis(root,0);
    printf("------------------------------------\n");
    LISTA *pocetak=NULL,*kraj=NULL;
    nadjiZaBrisanje(root,tip,rastojanje,&pocetak,&kraj);
    for(kraj=pocetak;kraj!=NULL;kraj=kraj->sledeci){
        root=obrisi(root,kraj->v,kraj->rastojanje,kraj->tip);
    }
    ispis(root,0);
    printf("------------------------------------\n");
    if(root==NULL)
    printf("NE POSTOJI\n");
    else{
        printf("Najblize vozilo\n");
        CVOR *t=najblizi(root);
        printf("ID: %d\nUdaljenost: %.6f\n",t->id,t->tezina);
    }
    return 0;
}