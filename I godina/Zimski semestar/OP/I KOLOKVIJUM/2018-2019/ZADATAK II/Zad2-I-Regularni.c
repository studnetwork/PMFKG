#include<stdio.h>
#include <math.h>
/*
 * Svi pozivi printf-ova su cisto radi pracenja programa i debug-ovanja 
 */
int main(){
	int brKutija = 0; // broj nespakovanih kutija 
	int i; 
	int n; 
	int tKutDuzina, tKutSirina, tKutVisina; // dimenzije trenutne kutije 
	int mKutDuzina, mKutSirina, mKutVisina; // dimenzije najmanje kutije
	int vKutDuzina, vKutSirina, vKutVisina; // dimenzije najvece kutije 

	printf("Unesite broj kutija: "); 
	scanf("%d", &n); 
	
	//moramo da setujemo dimenzije vece i manje kutije na prvu kutiju 
	printf("Unesite dimenzije kutija: "); 
	scanf("%d%d%d", &tKutDuzina,&tKutSirina,&tKutVisina); 
	
	mKutDuzina = tKutDuzina; 
	mKutSirina = tKutSirina;
	mKutVisina = tKutVisina;
	
	vKutDuzina = tKutDuzina; 
	vKutSirina = tKutSirina;
	vKutVisina = tKutVisina;
	
	// posto smo vec unele jednu kutiju, smanjujemo broj kutija za 1 
	for(i=0;i<n-1;i++){
		printf("Unesite dimenzije kutija: "); 
		scanf("%d%d%d", &tKutDuzina,&tKutSirina,&tKutVisina); 
		// prvo cemo da proverimo kutije po visinama jer ne mozemo da okrenemo kutiju po visini 
		if(tKutVisina>vKutVisina){
			// prvi uslov ((tKutDuzina>vKutDuzina) && (tKutSirina>vKutSirina)) ako mozemo da ubacimo sve kutije u kutiju bez okretanja
			// drugi uslov ((tKutDuzina>vKutSirina) && (tKutSirina>vKutDuzina)) ako mozemo da ubacimo sve kutije u kutiju sa okretanjem 
			if(((tKutDuzina>vKutDuzina) && (tKutSirina>vKutSirina)) || ((tKutDuzina>vKutSirina) && (tKutSirina>vKutDuzina)))
			{
				printf("=========================================\n"); 
				printf("Spakovane sve kutije u trenutnu kutiju\n"); 
				vKutDuzina = tKutDuzina; 
				vKutSirina = tKutSirina; 
				vKutVisina = tKutVisina; 
			}	
			else{
				brKutija++; 
				printf("=========================================\n"); 
				printf("Kutija nije spakovana...\nBroj nespakovanih kutija do sad: %d\n", brKutija); 
			}	
		}
		// prvo cemo da proverimo kutije po visinama jer ne mozemo da okrenemo kutiju po visini 
		else if(tKutVisina<mKutVisina)
		{
			// prvi uslov ((tKutDuzina<mKutDuzina) && (tKutSirina<mKutSirina)) ako mozemo da ubacimo kutiju u najmanju kutiju na vrhu bez okretanja 
			// drugi uslov ((tKutDuzina<mKutSirina) && (tKutSirina<mKutDuzina)) ako mozemo da ubacimo kutiju u najmanju kutiju na vrhu sa okretanjem 
			if(((tKutDuzina<mKutDuzina) && (tKutSirina<mKutSirina)) || ((tKutDuzina<mKutSirina) && (tKutSirina<mKutDuzina)))
			{
				printf("=========================================\n"); 
				printf("Trenutna kutija je spakovana u kutije \n"); 
				mKutDuzina = tKutDuzina; 
				mKutSirina = tKutSirina; 
				mKutVisina = tKutVisina; 
			}
			else{
				brKutija++; 
				printf("=========================================\n"); 
				printf("Kutija nije spakovana...\nBroj nespakovanih kutija do sad: %d\n", brKutija); 
			}		
		}
		else{
			brKutija++; 
			printf("=========================================\n"); 
			printf("Kutija nije spakovana...\nBroj nespakovanih kutija do sad: %d\n", brKutija); 
		}	
	}
	printf("Broj nespakovanih kutija: %d\n", brKutija); 
}
