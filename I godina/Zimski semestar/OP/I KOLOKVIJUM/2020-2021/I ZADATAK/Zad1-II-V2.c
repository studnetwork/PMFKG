#include <stdio.h>

void main(){
	int n,i,j; 
	float brojilac = 1; 
	int stepenImenilac = 1;
	float sumaBrojilac = 0;  
	float clan;
	float suma; 
	int znak = -1; 
	
	printf("Unesite n: "); 
	scanf("%d", &n);
	brojilac = 4*n; 
	if(n>0){
		for(i=1;i<=n;i++){
			znak *=-1; 
			stepenImenilac = 1; 
			for(j=1;j<=4*i-1;j++)
				stepenImenilac*=i; 
			sumaBrojilac += (5*i + 2); 
			
			printf("Faktorijel brojilac: %f\n", brojilac); 
			printf("Suma brojilac: %f\n", sumaBrojilac);
			printf("Stepen imenilac: %d\n", stepenImenilac); 
			clan = znak*brojilac/stepenImenilac * sumaBrojilac; 
			printf("Clan : %10.3f\n", clan); 
			suma+=clan;
			printf("Suma: %10.3f\n", suma);
			printf("===================================\n"); 
			brojilac *= (4*n-i); 
		} 
	}
	else{
		n*=-1; 
		int cifra; 
		int noviBroj=0; 
		int dek = 1; 
		while(n>0){
			cifra = n%10; 
			if(cifra!=0)
				cifra-=1; 
			else 
				cifra = 9; 
			noviBroj+=cifra*dek; 
			dek*=10;
			n/=10; 
		}
		noviBroj*=-1; 
		printf("%d",noviBroj);
	}
}
