#include <stdio.h>
int main(){
	int n,i,j; 
	float suma = 0;
	float clan; 
	int sumaBrojilac = 0; 
	float faktBrojilac = 1; 
	float faktI = 1; 
	
	printf("Unesite n: "); 
	scanf("%d", &n);
	if(n>0){
		faktBrojilac = 2*n; 
		printf("Brojilac: %.2f\n", faktBrojilac);
		for(i=1; i<=n; i++){
			faktI*=(2*i-1)*(2*i); 
			sumaBrojilac+=2*i; 
			
			printf("Faktorijel brojilac: %f\n", faktBrojilac); 
			printf("Suma brojilac: %d\n", sumaBrojilac);
			printf("Faktorijel I: %f\n", faktI); 
			clan = faktBrojilac/faktI + sumaBrojilac; 
			suma+=clan;
			printf("Clan : %f\n", clan); 
			printf("Suma: %f\n", suma);
			printf("===================================\n");
			
			faktBrojilac *= (2*n-i); 
		}
		printf("Suma: %10.5f\n", suma);
	}
	else {
		int noviBroj = 0; 
		int dek = 1; 
		int cifra;
		n*=-1; 
		while(n>0){
			cifra = n%10;
			if(cifra%2==0){
				noviBroj*=10;
				noviBroj+=cifra; 
			}
			n/=10; 
		}
		printf("Novi broj je : %d", noviBroj); 
	}
}
