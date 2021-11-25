#include <stdio.h>
/*
 * Ogranicenje: visina>160, godina>17 
 * M - maksimalan broj osoba u liftu
 * T - maksimalna nosivost lifta
 * NAPOMENA:
 * Svi pozivi printf-ova su cisto radi pracenja programa i debug-ovanja
 */
int main(){
	int M, T, N; 
	int i; 
	int brStudenata = 0; 
	int tezina = 0;
	float temperatura = 0; 
	float studentTemperatura;  
	int studentTezina; 
	
	printf("Unesite broj studenata: "); 
	scanf("%d", &N); 
	printf("Unesite broj osoba u liftu: "); 
	scanf("%d", &M); 
	printf("Unesite maksimalnu nosivost lifta: "); 
	scanf("%d", &T); 
	
	for(i=0;i<N;i++){
		printf("Unesi podatke o studentu: "); 
		scanf("%f%d", &studentTemperatura, &studentTezina);
		if(studentTemperatura<=37){
			if ((studentTezina+tezina<=T) && (brStudenata<M)){
				tezina 		+= studentTezina;
				temperatura += studentTemperatura; 
				brStudenata ++; 
				printf("============================\n"); 
				printf("Student je usao u lift: %.2f\t%d\n",studentTemperatura, studentTezina); 
				printf ("Trenutno stanje => brStudenata: %d\tTemperatura:%.2f\tTezina:%d\n", brStudenata, temperatura, tezina); 
				printf("============================\n"); 			
			}
			else {
				printf("============================\n"); 
				printf("============================\n"); 
				printf("Lift je pun...\nStanje:\n%5d\n%.2f\n",tezina, temperatura*1.0/brStudenata); 
				printf("Zapocinjem punjenje sledece ture...\n"); 
				temperatura  = studentTemperatura;
				tezina	 	 = studentTezina; 
				brStudenata  = 1; 		
				printf("============================\n"); 
			}	
		} 
	}
}
