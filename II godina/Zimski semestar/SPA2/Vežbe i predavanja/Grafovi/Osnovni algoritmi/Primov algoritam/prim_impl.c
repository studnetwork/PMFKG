#include <stdio.h>
#include <stdlib.h>

#define NUM_NODES 9
#define INFINITY (-1)

#define TRUE 1
#define NIL (-1)
#define NOT_CONNTECTED (-1)

void initialize( int key[], int p[], int finished[], int root ) {
	int i;
	
	for( i = 0; i < NUM_NODES; i++) {
		key[i] = INFINITY;
		p[i] = NIL;
		finished[i] = NIL;
	}
	
	key[root] = 0;
}

void formGraph( int (*connMatrix)[NUM_NODES] ) {
	int i, j, a, b, w;
	
	for( i = 0; i < NUM_NODES; i++) 
		for( j = 0; j < NUM_NODES; j++ )
			connMatrix[i][j] = NOT_CONNTECTED;
	
	i = 0;
	printf("Enter edges and their weight ( format: a b w ):\t\t\t-1 -1 -1 to stop\n");
	while( i++ < NUM_NODES * NUM_NODES ) {
		scanf("%d%d%d", &a, &b, &w);
		getchar();
		
		if( a == -1 || b == -1 || w == -1 )
			break;
		
		connMatrix[a][b] = w;
	} 
}

int isLeftLessRight( int left, int right ) {
	
	if( right == INFINITY ) {
		if( left == INFINITY )
			return 0;
		
		return 1;
	}
	
	if( left == INFINITY )
		return 0;
		
		
	return left < right;
}

int findMin( int key[], int finished[] ) {
	int i;
	int minInd = NIL;
	int min = INFINITY;
	
	for( i = 0; i < NUM_NODES; i++ ) {
		if( finished[i] == NIL && isLeftLessRight( key[i], min ) ) {
			minInd = i;
			min = key[minInd];
		}
	}
	
	
	return minInd;
}

void prim(  int (*connMatrix)[NUM_NODES], int key[], int p[], int finished[], int root ) {
	initialize( key, p, finished, root );
	
	int v, u;
	int isInfinityFlag;
	
	while( NIL != ( u = findMin( key, finished ) ) ) {
		finished[u] = TRUE;

		for( v = 0; v < NUM_NODES; v++ )
			/* check if 'v' is adjacent of 'u' which is not finished */
			if( connMatrix[u][v] != NOT_CONNTECTED && finished[v] != TRUE ) {
				isInfinityFlag = key[v] == INFINITY;
	
				/* check if there is a smaller value for key[v] */
				if( isInfinityFlag || connMatrix[u][v]  < key[v] ) {
					p[v] = u;
					key[v] = connMatrix[u][v];
				}
			}
	}
}

int main() {
	int root;
	int key[NUM_NODES];
	int p[NUM_NODES];
	int finished[NUM_NODES];
	int connMatrix[NUM_NODES][NUM_NODES];
	
	formGraph( connMatrix );
	
	while( 1 ) {
		printf("\nEnter index of the root node: \n");
		scanf("%d", &root );
		getchar();
		
		if( root < 0 || root > NUM_NODES - 1 )
			printf("Index of root node is not in the interval [0,%d]\n", NUM_NODES - 1);
		else
			break;
	}

	prim( connMatrix, key, p, finished, root );
	
	printf("\nc=2\tg=6\td=3\n");
	printf("p[i]=%d\tp[h]=%d\tp[e]=%d\n", p[8], p[7], p[4] );
	printf("p[i]=c\tp[h]=g\tp[e]=d\n");
}
