#include<stdio.h>
#include<stdlib.h>

typedef struct cvor
{
    int broj;
    struct cvor *levi, *desni;
} Cvor;

Cvor* napraviStablo( int k, FILE *f)
{
    if( k==1)
    {
        int x;
        Cvor* list = (Cvor*)malloc(sizeof(Cvor));
        fscanf( f,"%d", &x);
        list->broj = x;
        list->levi = list->desni = NULL;
        return(list);
    }
    else
    {
        Cvor* cvor = (Cvor*)malloc(sizeof(Cvor));
        cvor->levi = napraviStablo(k-1,f);
        cvor->desni = napraviStablo(k-1,f);
        cvor->broj = cvor->levi->broj + cvor->desni->broj;
        return(cvor);
    }
}

int main()
{
    int k;
    char link[64];
    Cvor *koren = NULL;

    scanf("%s", link);
    scanf("%d", &k);

    FILE *f = fopen( link, "r");
    koren = napraviStablo(k,f);
    fclose(f);
}
