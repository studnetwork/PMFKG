#include <stdio.h>

int main(){
	int n, kopija;
	int i,j;  
	
	// promenljive za slucaj da je m != 0
	int novBroj = 0; 
	int dek = 1; 
	int cifra; 
	
	// promenljive za slucaj da je m = 0
	float suma = 0; 
	int sumaBrojilac = 0; 
	int znak = -1; 
	int stepenI = 1; 
	int faktN = 1; 
	int stepenPetice = 1;
	int sumaPetice = 0;  
	float clan;
	
	printf("Unesite n: "); 
	scanf("%d", &n);
	kopija = n; 
	
	while(kopija>0){
		// neparni ce se pretvoriti u parne i dace 0 pri % 2
		// parni ce preci u neparne i tako dati 1 pri % 2
		/*cifra = kopija%10; 
		if(cifra %2 == 0)
			cifra = 1; 
		else
			cifra = 0; */
			
		cifra = (kopija%10+1)%2; 
		printf("Sifra: %d\n", cifra); 
		
		novBroj += dek*cifra; 
		dek*=10; 
		kopija/=10; 
	}
	if(novBroj == 0){
		for(i=1;i<=n;i++)
			faktN *= i; 
		for(i=1;i<=n;i++){

			stepenI = 1; 
			for(j=1; j<=i;j++)
				stepenI *= i; 

			sumaBrojilac+=(3*i); 
			
			stepenPetice *= 5; 
			sumaPetice += stepenPetice; 
			clan = sumaBrojilac*1.0*(znak*stepenI+faktN)/sumaPetice; 
			suma += clan; 
			
			printf("Suma brojilac: %d\n", sumaBrojilac); 
			printf("Stepen I : %d\n", stepenI);
			printf("Fakt n:  %d\n", faktN); 
			printf("Imenilac (suma petice):  %d\n", sumaPetice); 
			printf("Clan : %10.5f\n", clan); 
			printf("Suma: %10.5f\n", suma);
			printf("===================================\n");
			znak *= -1; 
		}
		printf("Suma: %10.5f\n", suma); 
	}
	else
		printf("m = %10d\n", novBroj); 
}
