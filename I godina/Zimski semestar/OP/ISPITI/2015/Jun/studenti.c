#include <stdio.h>
#include <string.h>
typedef struct PIVO{
	float zapremina; // zapremina jedne flase
	int brKomada;  // broj flasa
}PIVO;
typedef struct Ranac{
	PIVO pivo; 
	int vrsta;  // prvo,drugo,trece
	float zapremina; // maksimalna zapremina
}RANAC;
typedef struct student{
	char ime[10]; 
	RANAC ranac; 
}STUDENT;
int ucitajStudenteIPiva(char nazivFajla [], STUDENT studenti[], PIVO piva[]){
	int brStudenata,i; 
	FILE * ulaz; 
	
	ulaz = fopen(nazivFajla, "r"); 
	fscanf(ulaz,"%d", &brStudenata); 
	printf("Ucitan broj studenata iz datoteke : %d\n", brStudenata);
	
	for(i=0;i<brStudenata; i++){
		fscanf(ulaz,"%s",studenti[i].ime); 
		fscanf(ulaz,"%f", &studenti[i].ranac.zapremina); 
		studenti[i].ranac.vrsta = 0;
		studenti[i].ranac.pivo.brKomada = 0;
		studenti[i].ranac.pivo.zapremina = 0; 
	}
	
	float zapremina = 0.5; 
	for(i=0;i<3;i++){
		fscanf(ulaz, "%d",&piva[i].brKomada); 
		piva[i].zapremina = zapremina;
		zapremina*=2;  
	}
	return brStudenata; 
}
void ispisiPiva(PIVO piva[], int brPiva){
	int i; 
	if(brPiva == 0){
		printf("Nema piva\n");
		return; 
	}
	for(i=0;i<brPiva;i++)
		printf("Zapremina: %3.2f\t Br. komada: %d\n",piva[i].zapremina, piva[i].brKomada);
}
void ispisiStudente(STUDENT studenti[], int brStudenata){
	int i,j; 
	for(i=0;i<brStudenata; i++){
		printf("%s\t", studenti[i].ime);
		printf("%2.2f\n", studenti[i].ranac.zapremina);
		printf("Piva u rancu: "); 
		printf("%d %d\n", studenti[i].ranac.vrsta, studenti[i].ranac.pivo.brKomada); 
	}
}
void sortiraj(STUDENT studenti[], int brStudenata){
	int i; 
	int j; 
	STUDENT temp; 
	for(i=0;i<brStudenata-1;i++){
		for(j=i+1;j<brStudenata;j++){
			if(studenti[i].ranac.zapremina < studenti[j].ranac.zapremina){
				temp 	 = studenti[i]; 
				studenti[i] = studenti[j]; 
				studenti[j] = temp; 
			}
		}
	}
}
void podeliPivo(STUDENT studenti[],int brStudenata, PIVO vrste[]){
	int i; 
	int spakovano = 0;
	int ukupnoPiva = 0;
	int brVrste = 1; 
	int ind = 0;
	float ukupnaKolicina = 0;

	for(i=0;(i<3)&&(ind<brStudenata);i++){
		ukupnaKolicina = vrste[i].brKomada*vrste[i].zapremina;
		while((ind<brStudenata) && (ukupnaKolicina>0)){
			studenti[ind].ranac.vrsta = i; 
			studenti[ind].ranac.pivo.zapremina = vrste[i].zapremina;
			int trenutnaZapremina = studenti[ind].ranac.pivo.brKomada *  studenti[ind].ranac.pivo.zapremina; 
			while ((ukupnaKolicina>0)&&(studenti[ind].ranac.zapremina>=(trenutnaZapremina+vrste[i].zapremina))){
				studenti[ind].ranac.pivo.brKomada ++; 
				ukupnaKolicina-=vrste[i].zapremina; 
				trenutnaZapremina = studenti[ind].ranac.pivo.brKomada *  studenti[ind].ranac.pivo.zapremina;
			}
			ind++; 
		}
		if(ukupnaKolicina > 0){
			printf("Nisu mogla da se spakuju sva piva\n"); 
			break; 
		}
	}
	

}
int odrediRanac(STUDENT studenti[], int brStudenata){
	int index = 0;
	int i;  
	int maxProstor = 0; 
	for(i=0;i<brStudenata;i++){
		float trenProstor = studenti[i].ranac.zapremina - (studenti[i].ranac.pivo.brKomada*studenti[i].ranac.pivo.zapremina); 
		printf("%.2f - %.2f\n", trenProstor, maxProstor); 
		if(trenProstor > maxProstor){
			maxProstor = trenProstor; 
			index = i; 
		}		
	}
	
	return index; 
}
void prepakovati(STUDENT studenti[], int brStudenata, int proizvodjac, float zapremina){
	int i; 
	int brRanaca = 0;
	int brFlasa = 0; 
	float minZap = -1; 
	for(i=0;i<brStudenata;i++){
		if(studenti[i].ranac.vrsta == proizvodjac){
			brRanaca++; 
			brFlasa += studenti[i].ranac.pivo.brKomada;
			if(minZap==-1)
				minZap = studenti[i].ranac.zapremina; 
			else{
				float trenZap = studenti[i].ranac.zapremina;
				if(minZap>trenZap){
					minZap = trenZap;
				}
			}
		}
	}
	int brFlasaPoRancu = brFlasa/brRanaca; 
	printf("%d / %d = %d\n", brFlasa, brRanaca,brFlasaPoRancu);
	printf("Min kol: %.2f\n",minZap);  
	if((brFlasaPoRancu*zapremina) > minZap)
		printf("Ne moze da se prepakuje\n"); 
	else
		printf("Moze da se prepakuje"); 
}
int main(){
	int brStudenata; 
	STUDENT studenti[50]; //niz studenata
	PIVO piva[3]; 
	brStudenata = ucitajStudenteIPiva("studenti.txt", studenti, piva);
	ispisiStudente(studenti, brStudenata); 
	printf("\n====================================\n") ; 
	ispisiPiva(piva,3); 
	printf("\n====================================\n") ;
	printf("Sortirana lista: \n"); 
	sortiraj(studenti, brStudenata);
	podeliPivo(studenti, brStudenata, piva); 
	ispisiStudente(studenti, brStudenata);
	printf("\n====================================\n");
	int prostorIndex = odrediRanac(studenti, brStudenata); 
	printf("Ranac studenta koji ima najvise prostora: %s\n",studenti[prostorIndex].ime); 
	printf("\n====================================\n") ;
	prepakovati(studenti, brStudenata, studenti[prostorIndex].ranac.vrsta, studenti[prostorIndex].ranac.pivo.zapremina); 
}
