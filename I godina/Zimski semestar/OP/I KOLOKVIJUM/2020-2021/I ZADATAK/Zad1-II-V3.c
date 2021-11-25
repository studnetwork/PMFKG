#include <stdio.h>

void main(){
	int n,i,j; 
	int znak = -1; 
	float suma = 0; 
	float sumaBrojilac = 0; 
	float clan = 0; 
	float faktBrojilac = 1; 
	float faktImenilac = 1;
	int stepenImenilac = 1; 
	 
	printf("Unesite n: "); 
	scanf("%d", &n);
	if(n>0){
		// racunamo 4n!	
		for(i=1;i<=4*n;i++)
			faktBrojilac*=i; 
		for(i=1;i<=n;i++){
			faktImenilac = 1; 
			for(j=1;j<=(4*n-i);j++){
				faktImenilac*=j;
			}
			printf("i: %d\n", i);
			znak *=-1; 
			stepenImenilac = 1; 
			for(j=1;j<=4*i-1;j++)
				stepenImenilac*=i; 
			sumaBrojilac += (5*i + 2); 
			printf("Faktorijel brojilac: %d\n", faktBrojilac); 
			printf("Suma brojilac: %10.3f\n", sumaBrojilac);
			printf("Faktorijel imenilac: %d\n", faktImenilac); 
			printf("FaktBr/FaktIm : %f\n", faktBrojilac*1.0/faktImenilac); 
			printf("Stepen imenilac: %d\n", stepenImenilac); 
			clan = znak*faktBrojilac*1.0/(faktImenilac * stepenImenilac) * sumaBrojilac; 
			printf("Clan : %10.3f\n", clan); 
			suma+=clan;
			printf("Suma: %10.3f\n", suma);
			printf("===================================\n"); 
		}
		printf("Suma: %10.3f\n", suma);
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
