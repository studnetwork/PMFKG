#include <stdio.h>
typedef struct Broj{
	int duzina; 
	int cifre[1000]; 
}BROJ;
void ucitajBrojeve(char nazivFajla[], BROJ brojevi[]){
	int j,i; 
	FILE * ulaz = fopen(nazivFajla, "r"); 

	for(i=0;i<2; i++){
		fscanf(ulaz,"%d",&brojevi[i].duzina); 
		for(j=0;j<brojevi[i].duzina;j++){
			fscanf(ulaz,"%d",&brojevi[i].cifre[j]); 
		}
	}
}
void stampajBroj(BROJ broj){
	int i;
	for(i=0;i<broj.duzina;i++){
		if((i==0)&&(broj.cifre[i]==0))
			continue; 
		
		printf("%d ",broj.cifre[i]); 
	}
	printf("\n"); 
}
void stampajBrojeve(BROJ brojevi[]){
	int j,i; 
	for(i=0;i<2;i++){
		stampajBroj(brojevi[i]); 
		printf("\n"); 
	}
}
BROJ saberi(BROJ brojevi[]){
	BROJ rezultat; 
	int prenos = 0; 
	int i, cifra1, cifra2; 
	int maxDuzina = brojevi[0].duzina; 
	int duzina1 = brojevi[0].duzina; 
	int duzina2 = brojevi[1].duzina; 
	
	
	if(maxDuzina<brojevi[1].duzina)
		maxDuzina = brojevi[1].duzina; 
	
	//inicijalizacija rezultata
	rezultat.duzina = maxDuzina+1; 
	for(i=0;i<maxDuzina+1;i++){
		rezultat.cifre[rezultat.duzina-1-i] = 0; 
	}

	for(i=0;i<rezultat.duzina;i++){
		/* Stavljale smo da je duzina == 0, ali sta ako sabiramo dvocifreni i cetvrocifreni broj?
		*  Mi smo se zastitile da samo u onom slucaju kada duzina1 ili duzina2 == 0 da vrati 0, a nama treba
		*  da vrati 0 sve dok se traje petlja */
		if(duzina1<=0) // pre je bilo if(duzina1==0)
			cifra1 = 0; 
		else
			cifra1 = brojevi[0].cifre[brojevi[0].duzina-1-i]; 
		
		if(duzina2<=0) // pre je bilo if(duzina2==0)
			cifra2 = 0; 
		else 
			cifra2 = brojevi[1].cifre[brojevi[1].duzina-1-i]; 
			
		rezultat.cifre[rezultat.duzina-1-i] = (cifra1+cifra2)%10+prenos;
		
		prenos = (cifra1+cifra2)/10; 
		duzina1--; 
		duzina2--; 
	}
	return rezultat; 
}
void stampajNegativanBroj(BROJ broj){ // ako je rezultat oduzimanja negativan, pozivacemo ovu funkciju 
	printf(" - "); 
	stampajBroj(broj);
}
BROJ oduzmi(BROJ brojevi[]){
	BROJ rezultat; 
	int ind = 1; 
	int i; 
	int cifra1,cifra2; 
	int duzina1 = brojevi[0].duzina; 
	int duzina2 = brojevi[1].duzina; 
		
	int maxDuzina = brojevi[0].duzina; 
	
	if(maxDuzina<brojevi[1].duzina)
		maxDuzina = brojevi[1].duzina; 
		
	for(i=0;i<rezultat.duzina;i++){
		if(duzina1<=0 && duzina2>0){ // isti slucaj kao i za sabiranje, moramo da se zastitimo da znamo da oduzimamo veci od manjeg broja i da treba da dodamo minus pri stampanju rezultata
			ind = -1; 
		}	
		if(duzina1<=0){ // stitimo se da nam se uvek vrati 0 i da ne bismo imale segmentation fault
			cifra1 = 0; 
		}
		else{
			cifra1 = brojevi[0].cifre[brojevi[0].duzina-i-1]; 
		}
		
		if(duzina2<=0) // stitimo se da nam se uvek vrati 0 i da ne bismo imale segmentation fault
			cifra2 = 0; 
		else 
			cifra2 = brojevi[1].cifre[brojevi[1].duzina-i-1]; 	
		if(cifra1<cifra2){
			rezultat.cifre[rezultat.duzina-1-i] = cifra2-cifra1;
		}
		else{
			rezultat.cifre[rezultat.duzina-1-i] = cifra1-cifra2;
		}
		
		duzina1--; 
		duzina2--; 
		
		if(duzina1==0 && duzina2==0)
			if(cifra1<cifra2)
				ind = -1;
	}
	if(ind == -1)
		stampajNegativanBroj(rezultat); 
	else
		stampajBroj(rezultat); 
	return rezultat;
}
int main(){
	BROJ brojevi[2]; 
	BROJ rezultat; 
	ucitajBrojeve("brojevi.txt",brojevi);
	stampajBrojeve(brojevi); 
	rezultat = saberi(brojevi);
	stampajBroj(rezultat);  
	rezultat = oduzmi(brojevi); 
}
