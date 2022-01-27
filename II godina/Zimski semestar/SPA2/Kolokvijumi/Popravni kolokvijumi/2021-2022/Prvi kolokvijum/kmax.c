//Resio: Ljubomir Matovic 58/2020
#include<stdio.h>
#include<stdlib.h>

typedef struct CVOR{
    int v;
    struct CVOR *levi,*desni;
}CVOR;


CVOR* alocirajCvor(int v){
    CVOR* temp=(CVOR*)malloc(sizeof(CVOR));
    if(temp==NULL){
        printf("GRESKA\n");
        exit(1);
    }
    temp->v=v;
    temp->levi=temp->desni=NULL;
    return temp;
} 

void dodaj(CVOR **root,int v){
    CVOR *temp=alocirajCvor(v);
    if(*root==NULL){
        *root=temp;
    }else{
        CVOR *pom=*root,*pom1;
        while(pom!=NULL){
            pom1=pom;
            if(pom->v<v){
                pom=pom->desni;
            }else{
                pom=pom->levi;
            }
        }
        if(pom1->v<v){
            pom1->desni=temp;
        }else{
            pom1->levi=temp;
        }
    }
}
int kmax(CVOR *root,int k,int *br){
    if(root==NULL)
    return 0;
    int p;
    if(*br<k && root->desni)
    p=kmax(root->desni,k,br);
    if(*br<k){
        (*br)++;
        p=0;
    }
    if(*br==k){
        p=root->v;
        (*br)++;
    }
    if(p==0 && root->levi)
    p=kmax(root->levi,k,br);
    //printf("%d\n",p);
    return p;
    
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
    printf ( "%d\n", root->v);
    ispis ( root->levi, level + 1 );
  }
}
int main(){
    int n;
    scanf("%d",&n);
    int i,k,p;
    CVOR *root=NULL;
    for(i=0;i<n;i++){
        scanf("%d",&p);
        dodaj(&root,p);
    }
    //ispis(root,0);
    scanf("%d",&k);
    int br=0;
    p=kmax(root,k,&br);
    printf("%d\n",p);
    return 0;
}