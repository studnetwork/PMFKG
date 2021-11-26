#include <stdio.h>
#include <string.h>
typedef enum {NE,DA} BOOLEAN;
typedef struct gost{
	char ime[10]; 
	int starost; 
	char pol; 
	BOOLEAN par; 
	BOOLEAN zaba; 
}GOST;
void stampajBool(BOOLEAN bul){
	if(bul == DA)
		printf("DA");
	else 
		printf("NE"); 
}
int ucitajGoste(char nazivFajla [], GOST gosti[]){
	int brGostiju,i; 
	FILE * ulaz; 
	
	ulaz = fopen(nazivFajla, "r"); 
	fscanf(ulaz,"%d", &brGostiju); 
	printf("Ucitan broj gostiju iz datoteke : %d\n", brGostiju);
	
	for(i=0;i<brGostiju; i++){
		fscanf(ulaz,"%s",gosti[i].ime); 
		fscanf(ulaz,"%d", &gosti[i].starost); 
		getc(ulaz); // pokupiti space izmedju godina i pola 
		fscanf(ulaz,"%c",&gosti[i].pol); 
		gosti[i].par = NE; 
	}
	
	return brGostiju; 
}
void ispisiGoste(GOST gosti[], int brGostiju){
	int i; 
	for(i=0;i<brGostiju; i++){
		printf("%s ", gosti[i].ime);
		printf("%d ", gosti[i].starost);
		printf("%c ",gosti[i].pol);
		stampajBool(gosti[i].par); 
		printf(" "); 
		stampajBool(gosti[i].zaba); 
		printf("\n"); 
	}
}
int podeliGoste(GOST gosti [], int brGosti, GOST gostiPol [], char pol){
	int i; 
	int brojac = 0; 
	for(i=0;i<brGosti;i++){
		if(gosti[i].pol == pol){
			gostiPol[brojac] = gosti[i]; 
			brojac++; 
		}
	}
	
	return brojac; 
}
void stampajParove(GOST muskarci[], int brMuskarci, GOST zene[], int brZene){
	int manje = brMuskarci; 
	int i,j; 
	if(manje>brZene)
		manje = brZene; 
	for(i=0;i<manje;i++){
		muskarci[i].par = DA; 
		zene[i].par = DA; 
		printf("%s - %s\n", muskarci[i].ime, zene[i].ime);
	}
}
void pretvoriUZabe(GOST gosti[], int brGostiju){
	int i; 
	for(i=0;i<brGostiju;i++)
		if((gosti[i].starost<18) || (gosti[i].starost>40))
			gosti[i].zaba = DA; 
}
void stampajSaZabama(GOST muskarci[], int brMuskarci, GOST zene[], int brZene){
	int i,j; 
	for(i=0;i<brMuskarci;i++){
		if(muskarci[i].zaba == DA)
			continue; 
	/*	-----------------------	*/
		for(j=0;j<brZene;j++){
			if(zene[j].zaba == DA)
				continue; 
			if(zene[j].par == DA)
				continue; 
			muskarci[i].par = DA; 
			zene[j].par = DA;
			printf("%s - %s\n", muskarci[i].ime, zene[j].ime);
			break; 
		}
		if(j==brZene)
			printf("%s nema para\n",muskarci[i].ime);		
	}
	
	for(i=0;i<brZene;i++){
		if(zene[i].zaba == DA)
			continue; 
		if(zene[i].par == DA)
			continue; 
		printf("%s nema para\n", zene[i].ime); 
	}
}
int pobegne(GOST zene[], int brZene){
	int i,j; 
	int poz; 
	for(i=0;i<brZene;i++){
		if(strcmp(zene[i].ime,"Pepeljuga")==0)
			break; 
	}
	poz = i; 
	for(i=poz;i<brZene-1;i++)
		zene[i] = zene[i+1];
	
	return brZene-1; 
}
void sortiraj(GOST gosti[], int brGostiju){
	int i; 
	int j; 
	GOST temp; 
	for(i=0;i<brGostiju-1;i++){
		for(j=i+1;j<brGostiju;j++){
			if(gosti[i].starost < gosti[j].starost){
				temp 	 = gosti[i]; 
				gosti[i] = gosti[j]; 
				gosti[j] = temp; 
			}
		}
	}
}
int main(){
	GOST gosti[50]; //lista gostiju
	GOST muskarci[50]; //lista muskarci 
	GOST zene[50]; // lista zena 
	int brGostiju, brMuskarci, brZene; //broj gostiju, broj muskaraca, broj zena
	
	brGostiju = ucitajGoste("bal.txt", gosti);
	ispisiGoste(gosti,brGostiju);  
	printf("===============================\n") ; 
	printf("Muskarci na balu: \n"); 
	brMuskarci = podeliGoste(gosti,brGostiju,muskarci,'M'); 
	ispisiGoste(muskarci,brMuskarci); 
	printf("===============================\n") ;
	printf("Zene na balu: \n"); 
	brZene = podeliGoste(gosti,brGostiju,zene,'Z'); 
	ispisiGoste(zene,brZene); 
	printf("===============================\n");
	//stampajParove(muskarci,brMuskarci,zene,brZene); 
	printf("===============================\n");
	pretvoriUZabe(muskarci, brMuskarci);
	ispisiGoste(muskarci,brMuskarci); 
	
	pretvoriUZabe(zene, brZene);
	ispisiGoste(zene,brZene); 
	
	printf("Nakon pretvaranja u zabe: \n"); 
	stampajSaZabama(muskarci, brMuskarci, zene, brZene); 
	printf("===============================\n");
	printf("Nakon sto Pepeljuga pobegne: \n"); 
	brZene = pobegne(zene, brZene); 
	ispisiGoste(zene,brZene); 
	printf("===============================\n");
	sortiraj(muskarci,brMuskarci); 
	sortiraj(zene,brZene);
	ispisiGoste(muskarci,brMuskarci); 
	ispisiGoste(zene,brZene); 
	printf("===============================\n");
	stampajParove(muskarci,brMuskarci,zene,brZene); 
}
