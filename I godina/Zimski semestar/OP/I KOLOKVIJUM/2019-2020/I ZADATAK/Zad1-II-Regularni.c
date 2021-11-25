#include <stdio.h>
int main(){
	int n,i,j; 
	float suma = 0;
	float clan; 
	int sumaBrojilac = 0; 
	float faktBrojilac = 1; 
	float faktI = 1; 
	float faktRazlika = 1;  
	
	printf("Unesite n: "); 
	scanf("%d", &n);
	if(n>0){
		for(i=1; i<=2*n; i++)
			faktBrojilac*=i; 
		printf("Brojilac: %.2f\n", faktBrojilac);
		for(i=1; i<=n; i++){
			faktI = 1;
			for(j=1;j<=2*i;j++)
				faktI*=j; 
				
			faktRazlika = 1; 	
			for(j=1;j<=(2*n-i);j++)
				faktRazlika*=j; 
				
			sumaBrojilac+=2*i; 
			
			printf("Faktorijel brojilac: %f\n", faktBrojilac); 
			printf("Suma brojilac: %d\n", sumaBrojilac);
			printf("Faktorijel I: %f\n", faktI); 
			printf("Faktorijel razlika: %f\n", faktRazlika); 
			clan = faktBrojilac/(faktI*faktRazlika)+sumaBrojilac; 
			suma+=clan;
			printf("Clan : %f\n", clan); 
			printf("Suma: %f\n", suma);
			printf("===================================\n");
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
