#include <stdio.h>

int main(){
	int n,i,j; 
	int suma = 0;
	int clan; 
	int sumaBrojilac = 0; 
	int faktBrojilac = 1; 
	int faktI = 1; 
	int faktRazlika = 1;  
	
	printf("Unesite n: "); 
	scanf("%d", &n);
	if(n>0){
		for(i=1; i<=n; i++)
			faktBrojilac*=i; 
		for(i=1; i<=n; i++){
			faktI = 1;
			for(j=1;j<=i;j++)
				faktI*=j; 
			
			faktRazlika = 1; 	
			for(j=1;j<=n-i;j++)
				faktRazlika*=j; 
				
			sumaBrojilac+=3*i; 
			/*printf("Faktorijel brojilac: %10.0f\n", faktBrojilac); 
			printf("Suma brojilac: %10.0f\n", sumaBrojilac);
			printf("Faktorijel I: %10.0f\n", faktI); 
			printf("Faktorijel razlika: %10.0f\n", faktRazlika); 
			clan = faktBrojilac/(faktI*faktRazlika)+sumaBrojilac; 
			suma+=clan;
			printf("Clan : %10.0f\n", clan); 
			printf("Suma: %10.0f\n", suma);
			printf("===================================\n"); */
			
			printf("Faktorijel brojilac: %d\n", faktBrojilac); 
			printf("Suma brojilac: %d\n", sumaBrojilac);
			printf("Faktorijel I: %d\n", faktI); 
			printf("Faktorijel razlika: %d\n", faktRazlika); 
			clan = faktBrojilac/(faktI*faktRazlika)+sumaBrojilac; 
			suma+=clan;
			printf("Clan : %d\n", clan); 
			printf("Suma: %d\n", suma);
			printf("===================================\n");
		}
		printf("Suma: %10d\n", suma);
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
		printf("Novi broj je : %d", noviBroj); 
	}
}
