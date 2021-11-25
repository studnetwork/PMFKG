#include <stdio.h>

main(){
	int n; 
	int i,j; 
	int suma = 0; 
	float rezultat = 0; 
	int faktImen = 1; 
	int faktBroj = 1; 
	int stepenIm = 1; 
	float clan; 
	float brojilac; 
	float imenilac; 
	float znak = -1; 
	
	scanf("%d", &n);
	if(n>0){
		for(i=1;i<=3*n;i++)
			faktBroj*=i; 
		for(i=1; i<=n;i++){
			faktImen = 1; 
			for(j=1;j<=(3*n-i);j++){
				faktImen *= j; 
			}
			stepenIm = 1; 
			for(j=1;j<=2*i-1;j++){
				stepenIm *=i; 
			}
			suma = suma + (4*i+1); 
			clan = suma * znak * faktBroj/(faktImen*stepenIm); 
			rezultat+=clan; 
			znak*=-1; 
		}
		printf("%.3f",rezultat);
	}
	else{
		n*=-1; 
		int cifra; 
		int noviBroj=0; 
		int dek = 1; 
		while(n>0){
			cifra = n%10; 
			if(cifra!=9){
				cifra+=1; 
				noviBroj+=cifra*dek; 
			}
			dek*=10;
			n/=10; 
		}
		noviBroj*=-1; 
		printf("%d",noviBroj);
	}	 
}
