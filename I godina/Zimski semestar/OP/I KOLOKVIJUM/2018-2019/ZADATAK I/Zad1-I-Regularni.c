#include <stdio.h>

int main(){
	int n, kopija; 
	int brCifara = 0; 
	int i,j; 
	
	// promenljive za I slucaj 
	float suma = 0; 
	int sumaBrojilac = 0; 
	int sumaImenilac = 0; 
	int stepenN = 1; 
	int stepenI = 1; 
	int apsVr; 
	float clan = 0; 
	
	
	// promenljive za II slucaj 
	int cifra; 
	int cigla; 
	
	printf("Unesite n: "); 
	scanf("%d", &n);
	kopija = n; 
	
	while(kopija>0){
		cifra = kopija%10; 
		brCifara++; 
		kopija/=10; 
	}
	printf("Broj cifara unetog broja: %d\n", brCifara); 
	for(i=1;i<=n;i++)
		sumaImenilac += 2*i; 
	if(brCifara<3){
		for(i=1;i<=n;i++){
			sumaBrojilac += i; 
			
			stepenN *= n; 
			stepenI = 1; 
			for(j=1;j<=i;j++)
				stepenI*=i; 
			apsVr = stepenN - stepenI; 
			if(apsVr<0)
				apsVr*=-1; 
			
			clan = 	(apsVr*1.0)/sumaImenilac*sumaBrojilac; 
			suma += clan; 
			
			printf("Suma brojilac: %d\n", sumaBrojilac); 
			printf("Aps. vr. : %d\n", apsVr);
			printf("Suma imenilac: %d\n", sumaImenilac); 
			printf("Clan : %10.5f\n", clan); 
			printf("Suma: %10.5f\n", suma);
			printf("===================================\n");
		}
		printf("Suma: %10.5f\n", suma);
	}
	else{
		if(brCifara%2 == 0)
			cigla = cifra + n%10; 
		else
			cigla = brCifara; 
		printf("Cigla : %d\n", cigla); 
	}
}
