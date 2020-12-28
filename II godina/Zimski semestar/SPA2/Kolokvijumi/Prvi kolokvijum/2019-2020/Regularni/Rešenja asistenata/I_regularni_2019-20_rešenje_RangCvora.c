#include <stdio.h>
#include <stdlib.h>

typedef struct cvor{
	int broj;
	int br_clanova_l;
	int balans;
	struct cvor *levi;
	struct cvor *desni;
}cvor;

void padding ( char ch, int n )
{
	int i;
	for ( i = 0; i < n; i++ )
		putchar ( ch );
}
void structure ( struct cvor *root, int level )
{
  if ( root == NULL ) {
    padding ( '\t', level );
    puts ( "~" );
  }
  else {
    structure ( root->desni, level + 1 );
    padding ( '\t', level );
    printf ( "%d(%d) %d\n", root->broj, root->br_clanova_l, root->balans);
    structure ( root->levi, level + 1 );
  }
}

void lrotacija(cvor **s){
	cvor *p = (*s)->desni;

	(*s)->desni = p->levi;
	p->levi = *s;

	p->br_clanova_l = (*s)->br_clanova_l + p->br_clanova_l + 1;

	(*s)->balans = (*s)->balans - 1 - ((p->balans > 0)? p->balans : 0);
	p->balans = p->balans - 1 + (((*s)->balans < 0)? (*s)->balans : 0); // -IZMENA- pomesao sam formule za lrotaciju i drotaciju

	*s = p;
}
void drotacija(cvor **s){
	cvor *p = (*s)->levi;

	(*s)->levi = p->desni;
	p->desni = *s;

	(*s)->br_clanova_l = (*s)->br_clanova_l - p->br_clanova_l - 1;

	(*s)->balans = (*s)->balans + 1 - ((p->balans < 0)? p->balans : 0);
	p->balans = p->balans + 1 + (((*s)->balans > 0)? (*s)->balans : 0);

	*s = p;
}

int dodaj_u_stablo(cvor **stablo, cvor *novi){
	if(*stablo == NULL){
		*stablo = novi;
		return 1;
	}
	int ink;

	if(novi->broj < (*stablo)->broj){
        ink = - dodaj_u_stablo(&(*stablo)->levi, novi);
        (*stablo)->br_clanova_l += 1; // -IZMENA- svakako ako se doda levo povecava se broj levih za 1
	}
	else ink = dodaj_u_stablo(&(*stablo)->desni, novi);

	(*stablo)->balans += ink;

	if(!(*stablo)->balans || !ink)
		return 0;
	if((*stablo)->balans > 1){
		if((*stablo)->desni->balans < 0) drotacija(&(*stablo)->desni);
		lrotacija(stablo);
		return 0;
	}
	if((*stablo)->balans < -1){
		if((*stablo)->levi->balans > 0) lrotacija(&(*stablo)->levi);
		drotacija(stablo);
		return 0; // -IZMENA- zaboravio sam return 0; :(
	}
	return 1;
}

cvor *inicijalizacija_stabla(){
	cvor *stablo = NULL;
	cvor *novi;
	int n, i;

	scanf("%d", &n);

	for(i = 0 ; i < n ; i++){
		novi = (cvor *) malloc (sizeof(cvor));
		scanf("%d", &novi->broj);
		novi->balans = novi->br_clanova_l = 0;
		novi->levi = novi->desni = NULL;

		dodaj_u_stablo(&stablo, novi);
	}
	return stablo;

}

int rang_cvora(cvor *stablo, int k){
	if(stablo == NULL) return 0;
	if(stablo->broj == k)
		return stablo->br_clanova_l;
	if(k < stablo->broj){
		return rang_cvora(stablo->levi, k);
	}
	return stablo->br_clanova_l + 1 + rang_cvora(stablo->desni, k);
}

void rangovi(cvor *stablo, cvor *cv){
    if(cv == NULL) return; // -IZMENA- ako je stablo prazno ne stampaj nista
	printf("%d ", rang_cvora(stablo, cv->broj));
	rangovi(stablo, cv->levi);
	rangovi(stablo, cv->desni);
}

// -IZMENA- za ovu funkciju nisam imao vremena na kolokvijumu
// // // // // // // // // // // // // // // // // // // // // //
int azuriraj_stablo(cvor **stablo, int k){
    if(*stablo == NULL) return 0;

    cvor *tmp, *pom;
    int ink = 0;
    if(k < (*stablo)->broj) ink = azuriraj_stablo(&(*stablo)->levi, k);
    else if(k > (*stablo)->broj) ink = - azuriraj_stablo(&(*stablo)->desni, k);
    else{
        ink = azuriraj_stablo(&(*stablo)->desni, k);
        tmp = *stablo;
        if((*stablo)->desni == NULL)
            *stablo = (*stablo)->levi;
        else{
            if((*stablo)->desni->levi == NULL){
                (*stablo)->desni->levi = (*stablo)->levi;
                (*stablo)->desni->br_clanova_l = (*stablo)->br_clanova_l;
                (*stablo)->desni->balans = (*stablo)->balans - 1;
                *stablo = (*stablo)->desni;

            }
            else{
                tmp = (*stablo)->desni;
                for(pom = tmp ; pom->levi->levi != NULL ; pom = pom->levi){
                    pom->br_clanova_l--;
                    if(pom->balans >= 0) tmp = pom;
                }
                pom->br_clanova_l--;
                if(pom->balans >= 0) tmp = pom;
                while(tmp != pom->levi){
                    tmp->balans++;
                    if(tmp->balans > 1)
                        if(tmp->desni->balans < 0) drotacija(&tmp->desni);
                        lrotacija(&tmp);
                    tmp = tmp->levi;
                }
                (*stablo)->broj = pom->levi->broj;
                tmp = pom->levi;
                pom->levi = tmp->desni;
            }
        }
        free(tmp);
        return 1;
    }
    // popravljanje balansa
    if(ink > 0)
        (*stablo)->br_clanova_l--;
    if(ink*ink == 4 || ink == 0)
        return ink;
    (*stablo)->balans += ink;

    ink = (*stablo)->balans - ink;
	if((*stablo)->balans > 1){
		if((*stablo)->desni->balans < 0) drotacija(&(*stablo)->desni);
		lrotacija(stablo);
	}
	if((*stablo)->balans < -1){
		if((*stablo)->levi->balans > 0) lrotacija(&(*stablo)->levi);
		drotacija(stablo);
	}
	ink = (ink == 0 || (ink * ink) == (*stablo)->balans * (*stablo)->balans)? 2 : 1;
	return ink;
}
// // // // // // // // // // // // // // // // // // // // // //

int main(){
	cvor *stablo;

	stablo = inicijalizacija_stabla();

	structure(stablo, 0);
	rangovi(stablo, stablo);
	printf("\n"); // -IZMENA- cisto da bi pisalo lepse

	int n;
	scanf("%d", &n);
    azuriraj_stablo(&stablo, n); // -IZMENA- poziv funkcije i ispis promenjenog stabla
    structure(stablo, 0);

	return 0;
}
