#include <stdio.h>
#include <stdlib.h>

typedef struct el{
	char slovo;
	struct el *sl, *pre;
}el;

el *inicijalizacija(){
	el *lista = NULL;
	el *pom;
	el *novi;

	char c;

	while(((c = getc(stdin)) >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
		getc(stdin);
		//printf("%c", c);
		novi = (el *) malloc (sizeof(el));
		novi->slovo = c;
		if(lista == NULL){
			lista = novi;
			novi->sl = novi;
			novi->pre = novi;
		}
		else{
			pom->sl = novi;
			novi->pre = pom;
			novi->sl = lista;
			lista->pre = novi;
		}
		pom = novi;
	}
	return lista;
}

void ispis(el *lista){
	el *pom = lista;

	if(pom == NULL) return; // -IZMENA- ne ispisj praznu listu
	do{
		printf("%c ", pom->slovo);
		pom = pom->sl;
	}while(pom != lista);
	printf("\n");
}

el *ima_palindrom(el *lista, int k){
	int i, flag;
	el *pom = lista;
	el *pomp, *pomk;

	do{
		pomp = pomk = pom;
		flag = 1;
		for(i = 0 ; i < k - 1 ; i++)
			pomk = pomk->sl;
		for(i = 0 ; i < k / 2 ; i++){
			if(pomp->slovo != pomk->slovo){
				flag = 0; break;
			}
			pomp = pomp->sl;
			pomk = pomk->pre;
		}
		if(flag)
			return pom;
		pom = pom->sl;
	}while(pom != lista);

	return NULL;
}

void izbaci_palindrome(el **lista, int k){
	el *pal, *pom, *glava;
	int i;

	while((pal = ima_palindrom(*lista, k)) != NULL){
		pom = pal;
		for(i = 0 ; i < k - 1 && pom->sl != pal; i++){ // -IZMENA- dodat uslov koji ce biti ispunjen samo u slucaju da se brise ostatak liste
			pom = pom->sl;
		}
		pal->pre->sl = pom->sl;
		pom->sl->pre = pal->pre;
		glava = pom->sl;
		pom->sl = NULL;

		pom = pal;
		while(pom != NULL){
			if(pom == *lista){
                if(*lista == glava) *lista = NULL; // -IZMENA- ako je ovaj uslov ispunjen znaci da ce lista sigurno biti prazna
				else *lista = glava;
			}
			pom = pom->sl;
			free(pal);
			pal = pom;
		}
		ispis(*lista);
		printf("------------\n");
	}
}

int main(){
	el *lista, *palindrom;
	int k;

	lista = inicijalizacija();
	ispis(lista);

	scanf("%d", &k);
	palindrom = ima_palindrom(lista, k);
	int i;
	if(palindrom)
		for(i = 0 ; i < k ; i++){
			printf("%c ", palindrom->slovo);
			palindrom = palindrom->sl;
		}
	printf("\n");
	izbaci_palindrome(&lista, k);
	ispis(lista);
	return 0;
}
