#include<stdio.h>
/*
 * Svi pozivi printf-ova su cisto radi pracenja programa i debug-ovanja 
 * umesto ove linije printf("Br. paketa: %d\tTezina: %d\n", brPaketa, tezina); 
 * treba ova printf("%d %d\n", brPaketa, tezina); da bi se dobio ispis kao u resenju
 */
int main(){
	int N;  // nosivost kolica 
	int paket; // tezina paketa 
	int tezina = 0; // ukupna tezina paketa na kolicima
	int brPaketa = 0; // broj paketa na kolicima 
	
	printf("Unesite nosivost kolica: "); 
	scanf("%d", &N); 
	printf("Unesite tezinu paketa: "); 
	scanf("%d", &paket); 
	while(paket != 0){
		// moramo da proverimo da li cemo prekoraciti ogranicenje ako bi
		// stavile paket na kolica 
		if(tezina+paket>N){
			// kada bismo stavile paket, presle bismo ogranicenje,
			// zato moramo da ispisemo stanje na kolicima i da
			// resetujemo brojace (tezina i broj paket) na vrednosti 
			// poslednjeg unetog paketa jer je sada on prvi paket koji 
			// smo stavile na kolica 
			printf("============================\n"); 
			printf("============================\n"); 
			printf("Kolica su napunjena....\n");
			printf ("Stanje:\t"); 
			printf("Br. paketa: %d\tTezina: %d\n", brPaketa, tezina); 
			tezina = paket; 
			brPaketa = 1; 
			printf("============================\n"); 
			printf("============================\n"); 
		}
		else{
			brPaketa++; 
			tezina+=paket; 
			printf("============================\n"); 
			printf("Dodajem paket...\n"); 
			printf("Trenutno stanje:...\nBr.paketa: %d\tTezina: %d\n", brPaketa, tezina); 
			printf("============================\n"); 
		}
		printf("Unesite tezinu paketa: "); 
		scanf("%d", &paket); 
	}
	// kada unesemo 0, izaci cemo iz petlje, ali necemo odstampati poslednju
	// tezinu koja se nalazi na kolicima 
	if(tezina>0)
		printf("Br. paketa: %d\tTezina: %d\n", brPaketa, tezina); 
		
}
