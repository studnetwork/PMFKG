#include<stdio.h>
#include <math.h>
/*
 * Svi pozivi printf-ova su cisto radi pracenja programa i debug-ovanja 
 */
int main(){
	int n;                         // broj poteza 
	int karta1, karta2, karta3;    // trenutne karte 
	int tKarta1, tKarta2, tKarta3; // karte koje odabere racunar 
	int mPropPotezi = 0; 		   // brojac propustenih poteza kod mike
	int pPropPotezi = 0;           // brojac propustenih poteza kod pere
	int temp,i; 				   // pomocne promenljive 
	
	int mKarta1; 
	int mKarta2; 
	int mKarta3; 
	
	int vKarta1; 
	int vKarta2; 
	int vKarta3; 
	
	printf("Unesite broj poteza: "); 
	scanf("%d", &n); 
	printf("RACUNAR => Unesite pocetne karte: "); 
	scanf("%d%d%d",&tKarta1,&tKarta2,&tKarta3); 	
	
	// sortiramo karte koje je odabrao racunar 
	if (tKarta1 > tKarta2){
		temp = tKarta2; 
		tKarta2 = tKarta1;
		tKarta1 = temp; 
	}
	if (tKarta1 > tKarta3){
		temp = tKarta3; 
		tKarta3 = tKarta1;
		tKarta1 = temp; 
	}
	if (tKarta2 > tKarta3){
		temp = tKarta3; 
		tKarta3 = tKarta2;
		tKarta2 = temp; 
	}
	
	// setujemo i manje i vece karte na karte koje je uneo racunar 
	mKarta1 = tKarta1; 
	mKarta2 = tKarta2; 
	mKarta3 = tKarta3; 
	
	vKarta1 = tKarta1; 
	vKarta2 = tKarta2; 
	vKarta3 = tKarta3; 
	
	// imamo dva igraca, dakle unosimo karte 2*n puta 
	for(i=1;i<=2*n;i++){
		// Mika igra kada je i neparno jer igra prvi 
		// Ovaj IF i ELSE su zbog debagovanja, moze da se zakomentarise (POCETAK i KRAJ)
		/*POCETAK*/
		if(i%2 == 1)
			printf("MIKA => Unesite karte: "); 
		else
			printf("PERA => Unesite karte: "); 
		/* KRAJ */
		scanf("%d%d%d",&karta1,&karta2,&karta3);
		// sortiramo unete karte 
		if (karta1 > karta2){
			temp   = karta2; 
			karta2 = karta1;
			karta1 = temp; 
		}
		if (karta1 > karta3){
			temp   = karta3; 
			karta3 = karta1;
			karta1 = temp; 
		}
		if (karta2 > karta3){
			temp   = karta3; 
			karta3 = karta2;
			karta2 = temp; 
		}
		// proveravamo da li mozemo da stavimo ispod talona 
		if((karta1<mKarta1) && (karta2<mKarta2) && (karta3<mKarta3)){
			printf("Stavio sam karte ispod...\n"); 
			mKarta1 = karta1; 
			mKarta2 = karta2; 
			mKarta3 = karta3; 
		}
		// proveravamo da li mozemo da stavimo iznad talona 
		else if ((karta1>vKarta1) && (karta2>vKarta2) && (karta3>vKarta3)){
			printf("Stavio sam karte iznad...\n"); 
			vKarta1 = karta1; 
			vKarta2 = karta2; 
			vKarta3 = karta3; 
		}
		// igrac je propustio potez 
		else {
			if(i%2 == 1){
				printf("MIKA => Propustio sam potez...\n"); 
				mPropPotezi++; 
			}	
			else{
				printf("PERA => Propustio sam potez...\n"); 
				pPropPotezi++; 
			}
		}
	}
	printf("===========================\n"); 
	printf("KRAJ IGRE....\n"); 
	printf("Pobednik je ");
	if(mPropPotezi < pPropPotezi)
		printf("Mika\n%d\n", mPropPotezi); 
	else if(mPropPotezi > pPropPotezi)
		printf("Pera\n%d\n", pPropPotezi); 
	else 
		printf("Nereseno\n%d\n", pPropPotezi); 
}
