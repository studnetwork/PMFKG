#include <stdio.h>
int main(){
	int n,i,j; 
	float suma = 0;
	float clan; 
	float sumaBrojilac = 0; 
	float faktBrojilac = 1; 
	float faktI = 1; 
	float faktRazlika = 1;  
	
	printf("Unesite n: "); 
	scanf("%d", &n);
	if(n>0){
		faktBrojilac = n; 
		for(i=1; i<=n; i++){
			faktI*=i; 	
			sumaBrojilac+=3*i; 	
			printf("Faktorijel brojilac: %10.0f\n", faktBrojilac); 
			printf("Suma brojilac: %10.0f\n", sumaBrojilac);
			printf("Faktorijel I: %10.0f\n", faktI); 
			clan = faktBrojilac/faktI + sumaBrojilac; 
			suma+=clan;
			printf("Clan : %10.0f\n", clan); 
			printf("Suma: %10.0f\n", suma);
			printf("===================================\n");
			faktBrojilac *= (n-i);  
		}
		printf("Suma: %10.0f\n", suma);
	}
	else {
		int noviBroj = 0; 
		int dek = 1; 
		int cifra;
		n*=-1; 
		while(n>0){
			cifra = n%10;
			if(cifra%2==1){
				noviBroj*=10;
				noviBroj+=cifra; 
			}
			n/=10; 
		}
		printf("Novi broj je : %10d", noviBroj); 
	}
}
