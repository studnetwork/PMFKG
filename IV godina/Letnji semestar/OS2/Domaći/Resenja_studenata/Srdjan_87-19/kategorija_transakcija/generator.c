#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BROJ_TRANSAKCIJA 1000000
#define BROJ_KOMPANIJA 1000
#define MAX_VREDNOST 10000.0
#define MIN_VREDNOST 1.0

int main()
{
	FILE *f;
	srand(time(NULL));
	long i;
	int j;
	double range = (MAX_VREDNOST - MIN_VREDNOST);
	double div = RAND_MAX / range;
	char file[13];

	for (j = 1; j < 5; j++)
	{
		sprintf(file, "kvartal%d.txt", j);
		f = fopen(file, "w");
		for (i = 0; i < BROJ_TRANSAKCIJA; i++)
		{
			long kid1 = rand() % BROJ_KOMPANIJA;
			long kid2 = rand() % BROJ_KOMPANIJA;
			while (kid1 == kid2)
				kid2 = rand() % BROJ_KOMPANIJA;
			double vrednost = MIN_VREDNOST + (rand() / div);
			fprintf(f, "%ld %ld %.2lf\n", kid1, kid2, vrednost);
		}
		fclose(f);
	}
}
