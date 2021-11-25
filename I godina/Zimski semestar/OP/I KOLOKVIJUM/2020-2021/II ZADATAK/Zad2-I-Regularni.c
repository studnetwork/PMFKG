#include <stdio.h>
/*
 * Ogranicenje: visina>160, godina>17 
 * M - maksimalan broj putnika 
 * T - maksimalna ukupna tezina
 * NAPOMENA:
 * Svi pozivi printf-ova su cisto radi pracenja programa i debug-ovanja 
 */
int main(){
	int M, T, N; 
	int i; 
	int brPutnika = 0; 
	int tezina = 0; 
	int visina = 0; 
	int putnikGod; 
	int putnikVisina; 
	int putnikTezina; 
	printf("Unesite broj putnika: "); 
	scanf("%d", &N); 
	printf("Unesite maksimalan broj putnika: "); 
	scanf("%d", &M); 
	printf("Unesite maksimalnu tezinu: "); 
	scanf("%d", &T); 
	
	
	for(i=0;i<N;i++){
		printf("Unesi podatke o putniku: "); 
		scanf("%d%d%d", &putnikGod, &putnikVisina, &putnikTezina);
		if((putnikGod>=18) && (putnikVisina>=160)){
			if ((putnikTezina+tezina<=T) && (brPutnika<M)){
				tezina += putnikTezina;
				visina += putnikVisina; 
				brPutnika ++; 
				printf("============================\n"); 
				printf("Putnik je ukrcan: %d %d %d\n", putnikGod, putnikVisina, putnikTezina); 
				printf ("Trenutno stanje => brPutnika: %d\tVisina:%d\tTezina:%d\n", brPutnika, visina, tezina); 
				printf("============================\n"); 			
			}
			else{
				printf("============================\n"); 
				printf("============================\n"); 
				printf("Kapaciteti su popunjeni...\nStanje na rolerkosteru:\n"); 
				printf("%5d\n%.2f\n",tezina, visina*1.0/brPutnika); 
				printf("Zapocinjem novu turu...\n"); 
				tezina	  = putnikTezina;  
				brPutnika = 1; 		
				visina	  = putnikVisina; 
				printf("============================\n"); 
			}	
		} 
	}
}
