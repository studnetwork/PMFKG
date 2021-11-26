#include <stdio.h>
#include <string.h>
typedef struct zivotinja{
	char naziv[10]; 
	int tezina; 
}ZIVOTINJA;
typedef struct vrsta{ 
	char naziv [50];  
	int brPrimeraka; 
	ZIVOTINJA zivotinje[50];
}VRSTA;
typedef struct prostorija{
	char naziv[10]; 
	int trenutnaTezina; 
	int brZivotinja; 
}PROSTORIJA;
int ucitajZivotinje(char nazivFajla [], ZIVOTINJA zivotinje[]){
	int brZivotinja,i; 
	FILE * ulaz; 
	
	ulaz = fopen(nazivFajla, "r"); 
	fscanf(ulaz,"%d", &brZivotinja); 
	printf("Ucitan broj zivotinja iz datoteke : %d\n", brZivotinja);
	
	for(i=0;i<brZivotinja; i++){
		fscanf(ulaz,"%s",zivotinje[i].naziv); 
		fscanf(ulaz,"%d", &zivotinje[i].tezina); 
	}
	
	return brZivotinja; 
}
void ispisiZivotinje(ZIVOTINJA zivotinje[], int brZivotinja){
	int i; 
	for(i=0;i<brZivotinja; i++){
		printf("%s ",zivotinje[i].naziv);
		printf("%d\n",zivotinje[i].tezina);
	}
}
int odrediVrste(ZIVOTINJA zivotinje[], int brZivotinja, VRSTA vrste[]){
	int i,j; 
	int brVrsta = 0; 
	for(i=0;i<brZivotinja;i++){
		for(j=0;j<brVrsta;j++){
			if(strcmp(zivotinje[i].naziv,vrste[j].naziv)==0)
				break;
		}
		if(j==brVrsta){
			strcpy(vrste[brVrsta].naziv,zivotinje[i].naziv);
			vrste[brVrsta].brPrimeraka = 0; 
			brVrsta++;
		}
	}
	return brVrsta;
}
void ispisiVrste(VRSTA vrste[], int brVrsta){
	int i; 
	for(i=0;i<brVrsta;i++){
		printf("NAZIV: %s BR. PRIMERAKA: %d\n",vrste[i].naziv, vrste[i].brPrimeraka); 
		ispisiZivotinje(vrste[i].zivotinje, vrste[i].brPrimeraka); 
		printf("-----------------\n"); 
	}
}
void odrediPrimerke(ZIVOTINJA zivotinje[], int brZivotinja, VRSTA vrste[],int brVrsta){
	int i,j; 
	for(i=0;i<brZivotinja;i++){
		for(j=0;j<brVrsta;j++){
			if(strcmp(zivotinje[i].naziv,vrste[j].naziv)==0){
				vrste[j].zivotinje[vrste[j].brPrimeraka] = zivotinje[i]; 
				vrste[j].brPrimeraka++; 
			}
		}
	}			
}
int odrediProstorije(VRSTA vrste [], int brVrsta, PROSTORIJA prostorije[], int maxTezina){
	int brProstorija = 0; 
	int brProstorijaPoVrsti=0; 
	int i,j; 
	
	for(i=0;i<brVrsta;i++){
		strcpy(prostorije[brProstorija].naziv,vrste[i].zivotinje[0].naziv);
		for(j=0;j<vrste[i].brPrimeraka;j++){
			if(maxTezina >= (vrste[i].zivotinje[j].tezina + prostorije[brProstorija].trenutnaTezina)){
				prostorije[brProstorija].trenutnaTezina += vrste[i].zivotinje[j].tezina; 
			}
			else{
				brProstorija++;
				strcpy(prostorije[brProstorija].naziv,vrste[i].zivotinje[0].naziv);
			}	
			prostorije[brProstorija].brZivotinja++; 
		}
		brProstorija++; 
	}
	
	return brProstorija; 
}
void stampajProstorije(PROSTORIJA prostorije[], int brProstorija){
	int i; 
	for(i=0;i<brProstorija;i++){
		printf("PROSTORIJA br. %d | ",i+1); 
		printf("%s | %5d |\n",prostorije[i].naziv, prostorije[i].brZivotinja); 
	}
}
int main(){
	ZIVOTINJA zivotinje[50]; //lista dece
	int brZivotinja, brVrsta, brProstorija; 
	int maxTezina; 
	VRSTA vrste[50];
	PROSTORIJA prostorije[50];  
	
	
	brZivotinja = ucitajZivotinje("farma.txt", zivotinje);
	ispisiZivotinje(zivotinje, brZivotinja);  
	printf("==================================\n"); 
	printf("Unesite maksimalnu kolicinu: "); 
	scanf("%d",&maxTezina); 
	brVrsta = odrediVrste(zivotinje, brZivotinja, vrste); 
	printf("VRSTE: \n"); 
	ispisiVrste(vrste,brVrsta); 
	printf("==================================\n"); 
	odrediPrimerke(zivotinje, brZivotinja, vrste, brVrsta); 
	ispisiVrste(vrste,brVrsta);
	brProstorija = odrediProstorije(vrste, brVrsta, prostorije, maxTezina);
	stampajProstorije(prostorije, brProstorija); 
}
