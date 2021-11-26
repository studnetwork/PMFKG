#include <stdio.h>
#include <string.h>
typedef struct kupac{
	char ime[20]; 
	int starost; 
	char pol; 
	int zeljeniRed; 
}KUPAC;
typedef struct red{
	int brKupaca; 
	KUPAC kupci[100]; 
}RED;
void stampajRed(RED red){
	int i; 
	if(red.brKupaca==0){
		printf("Ovaj red je prazan\n"); 
		printf("==========================\n"); 
		return; 
	}
	for(i=0;i<red.brKupaca;i++){
		KUPAC temp = red.kupci[i]; 
		printf("%s %d %c %d\n",temp.ime, temp.starost, temp.pol, temp.zeljeniRed); 
	}
	printf("==========================\n"); 
}
void stampajRedBezZelje(RED red){
	int i; 
	if(red.brKupaca==0){
		printf("Ovaj red je prazan\n"); 
		printf("==========================\n"); 
		return; 
	}
	for(i=0;i<red.brKupaca;i++){
		KUPAC temp = red.kupci[i]; 
		printf("%s %d %c\n",temp.ime, temp.starost, temp.pol); 
	}
	printf("==========================\n"); 
}
void ucitajRedove(char nazivDatoteke [], RED redovi[]){
	int i,j; 
	FILE * ulaz; 
	ulaz = fopen(nazivDatoteke,"r"); 
	
	for(i=0;i<10;i++){
		fscanf(ulaz,"%d",&redovi[i].brKupaca); 
		int brKupaca = redovi[i].brKupaca; 
		for(j=0;j<redovi[i].brKupaca;j++){
			fscanf(ulaz,"%s",redovi[i].kupci[j].ime); 
			fscanf(ulaz,"%d",&redovi[i].kupci[j].starost); 
			getc(ulaz); 
			fscanf(ulaz,"%c",&redovi[i].kupci[j].pol);
			fscanf(ulaz,"%d",&redovi[i].kupci[j].zeljeniRed);  
		}
	}
	
	fclose(ulaz); 
}
void ucitajRedoveBezZelje(char nazivDatoteke [], RED redovi[]){
	int i,j; 
	FILE * ulaz; 
	ulaz = fopen(nazivDatoteke,"r"); 
	
	for(i=0;i<10;i++){
		fscanf(ulaz,"%d",&redovi[i].brKupaca); 
		int brKupaca = redovi[i].brKupaca; 
		for(j=0;j<redovi[i].brKupaca;j++){
			fscanf(ulaz,"%s",redovi[i].kupci[j].ime); 
			fscanf(ulaz,"%d",&redovi[i].kupci[j].starost); 
			getc(ulaz); 
			fscanf(ulaz,"%c",&redovi[i].kupci[j].pol);   
		}
	}
	
	fclose(ulaz); 
}
int odrediMesto(RED red, KUPAC kupac){
	int i; 
	int mesto = 0; 
	
	for(i=0;i<red.brKupaca;i++)
		if((red.kupci[i].starost>kupac.starost)&&(red.kupci[i].pol == kupac.pol))
			mesto = i; 
	mesto++; 
	return mesto; 
}
int odrediNajkraciRed(RED redovi[]){
	int indeks = 0; 
	int minDuzina = redovi[0].brKupaca; 
	int i; 
	
	for(i=0;i<10;i++){
		if(redovi[i].brKupaca<minDuzina){
			minDuzina = redovi[i].brKupaca; 
			indeks = i; 
		}
	}
	 
	return indeks; 
}
RED postaviKupca(RED red, KUPAC kupac, int pozicija){
	int i; 
 
	if(pozicija >= red.brKupaca){
		red.kupci[red.brKupaca] = kupac; 
	}
	else if(red.brKupaca == 0){
		red.kupci[0] = kupac; 
	}
	else{
		for(i=red.brKupaca;i>pozicija;i--)
			red.kupci[i] = red.kupci[i-1]; 
		red.kupci[pozicija] = kupac; 
	}
	red.brKupaca++; 

	return red; 
}
RED obrisiKupca(RED red,int pozicija){
	int i; 
	if(pozicija>=red.brKupaca){
		pozicija = red.brKupaca-1; 
	}
	for(i=pozicija;i<red.brKupaca;i++){
		red.kupci[i] = red.kupci[i+1]; 
	}
	red.brKupaca--; 
	return red; 
}
void prepakuj(RED redovi[]){
	int i,j; 
	for(i=0;i<10;i++){
		RED red = redovi[i];
		for(j=0;j<redovi[i].brKupaca;j++){
		int zeljeniRed = redovi[i].kupci[j].zeljeniRed; 
			int starost = redovi[i].kupci[j].starost;  
			if((zeljeniRed == 0) || (zeljeniRed != (i+1))){
				if(zeljeniRed == 0){
					int minRed = odrediNajkraciRed(redovi);
					if(starost<50)
						redovi[minRed] = postaviKupca(redovi[minRed],redovi[i].kupci[j],redovi[minRed].brKupaca); 
					else{
						int pozicija = odrediMesto(redovi[minRed],redovi[i].kupci[j]); 
						redovi[minRed] = postaviKupca(redovi[minRed],redovi[i].kupci[j],pozicija); 
					}
				}
				else {
					if(starost<50)
						redovi[zeljeniRed-1] = postaviKupca(redovi[zeljeniRed-1],redovi[i].kupci[j],redovi[zeljeniRed-1].brKupaca); 
					else{
						int pozicija = odrediMesto(redovi[zeljeniRed],redovi[i].kupci[j]); 
						redovi[zeljeniRed-1] = postaviKupca(redovi[zeljeniRed-1],redovi[i].kupci[j],pozicija); 
					}
				}
				redovi[i] = obrisiKupca(redovi[i],j);
			}
			
		}
	}
}
int main(){
	RED redovi[10];
	KUPAC kupci[100]; 
	int brKupaca, i; 
	/*ucitajRedove("hipermarket2.txt", redovi); 
	for(i=0;i<10;i++){
		printf("Ucitava se %d.red:\n",i+1); 
		stampajRed(redovi[i]); 
	}*/
	
	ucitajRedove("hipermarket.txt", redovi); 
	for(i=0;i<10;i++){
		printf("Ucitava se %d.red:\n",i+1); 
		stampajRed(redovi[i]); 
	}
	
	int najkraciRed = odrediNajkraciRed(redovi); 
	printf("Najkraci red je %d.red\n",najkraciRed+1);
	printf("==========================\n"); 
	
	KUPAC temp; 
	strcpy(temp.ime,"Teodora"); 
	temp.starost = 25; 
	temp.pol = 'Z'; 
	temp.zeljeniRed = 8; 
	redovi[5] = postaviKupca(redovi[5],temp,5); 
	stampajRed(redovi[5]);
	
	int mesto = odrediMesto(redovi[7],temp); 
	redovi[7] = postaviKupca(redovi[7],temp,mesto); 
	stampajRed(redovi[7]); 
	
	stampajRed(redovi[5]); 
	redovi[5] = obrisiKupca(redovi[5],1); 
	stampajRed(redovi[5]); 
	
	printf("Prepakuj kupce: \n"); 
	prepakuj(redovi); 
	for(i=0;i<10;i++){
		printf("Ucitava se %d.red:\n",i+1); 
		stampajRed(redovi[i]); 
	}
 
}
