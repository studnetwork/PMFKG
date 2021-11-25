#include<stdio.h>
#include <math.h>
/*
 * Svi pozivi printf-ova su cisto radi pracenja programa i debug-ovanja 
 */
int main(){
	
	int n;      // broj kruznih prstenova 
	float d;    // sirina prstena 
	int m;      // broj parova 
	float x, y; // koordinate trenutne tacke 
	float i; 
	float rastojanje; // rastojanje tacke od koordinatnog pocetka
	int zona;  
	printf("Unesite broj kruznih prstenova: "); 
	scanf("%d", &n); 
	printf("Unesite rastojanje: "); 
	scanf("%f", &d);
	printf("Unesite broj tacaka: "); 
	scanf("%d", &m); 
	
	for(i=0;i<m;i++){
		printf("Unesite koordinate tacke: "); 
		scanf("%f%f", &x, &y); 
		// rastojanje tacke od neke druge racunamo preko formule
		// d = sqrt((x1-x2)^2+(y1-y2)^2);
		// posto je u pitanju koordinatni pocetak, onda je x2 = y2 = 0
		// pa je d = sqrt(x1^2+y1^2);
		rastojanje = sqrt(pow(x,2)+pow(y,2));
		printf("Rastojanje : %.2f\n", rastojanje); 
		// zona je tipa int jer imamo deljenje float/float, a nama treba
		// ceo broj jer je to zapravo indeks zone  
		zona = rastojanje/d; 
		printf("Zona : %d\n", zona);
		if(zona>=n)
			printf("Izvan\n"); 
		else
			printf("%d\n", zona); 	
	}
}
