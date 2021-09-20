#include <stdio.h>
#include <stdlib.h>

#define NIL (-1)
#define INFINITY (-1)
#define GRAPH_N_NODES 5

typedef struct node_ {
	int id;
	int data;
} Node;

Node *createNode( int id, int data ) {
	Node *new = (Node*) malloc( sizeof(Node) );
	if( !new ) {
		fprintf(stderr, "malloc err\n");
		exit(1);
	}
	
	new->id = id;
	new->data = data;
	
	return new;
}

/* QUEUE - BEGIN */
typedef struct element_ {
	int id;
	struct element_ *next;
} Element;

Element *queHead = NULL;
Element *queTail = NULL;

Element *createElement( int id ) {
	Element *new = (Element*) malloc( sizeof(Element) );
	if( !new ) {
		fprintf(stderr, "malloc err\n");
		exit(1);
	}
	
	new->id = id;
	new->next = NULL;
	
	return new;
}

void enqueue(  int id ) {
	Element *new = createElement( id );
	if( queHead == NULL )
		queHead = queTail = new;
	else 
		queTail->next = new;
}

int dequeue( void ) {
	int result = NIL;
	Element *temp;
	
	if( queHead && queTail ) {
		temp = queHead;
		result = temp->id;
		
		queHead = queHead->next;
		free(temp);
		
		if( queHead == queTail )
				queTail = NULL;
	}
	
	return result;
}
/* QUEUE - END*/
	
		
void addAdj( Element *connMatrix[], int i, Element *adj ) {
	if( !connMatrix || !adj )
		return;
		
	if( !connMatrix[i] )
		connMatrix[i] = adj;
	else {
		adj->next = connMatrix[i];
		connMatrix[i] = adj;
	}
} 
	
void formGraph( Node *nodes[], Element *connMatrix[] ) {
	int i, data;
	int a, b;
	
	for( i=0; i < GRAPH_N_NODES; i++ ) {
		printf("\nEnter data of the node#%d: \n", i);
		scanf("%d", &data );
		getchar();
		
		nodes[i] = createNode( i, data );
	}
	
	printf("\n\nEnter edges ( format: a b ):\t\t\t-1 -1 to stop\n");
	for( i=0; i < GRAPH_N_NODES*GRAPH_N_NODES; i++ ) {
		scanf("%d%d", &a, &b );
		getchar();
		if( a == -1 || b == -1 )
			break;
			
		addAdj( connMatrix, a, createElement( b ) );
	}
}
		
void bfs( Element *connMatrix[], int d[], int p[], int start ) {
	int i;
	int idBase, idAdj;
	Element *currAdj;
	
	/* initialization */
	for(i = 0; i < GRAPH_N_NODES; i++) {
		d[i] = INFINITY;
		p[i] = NIL;
	}
	d[start] = 0;
	enqueue( start );
	
	while( NIL != ( idBase = dequeue() ) ) {
		currAdj = connMatrix[idBase];
				
		/* check each adjacent node*/
		while( currAdj ) {
			idAdj = currAdj->id;
			
			/* check if BFS already entered adjecent node */
			if( d[idAdj] == INFINITY ) {
				d[idAdj] = d[idBase] + 1;
				p[idAdj] = idBase;
				enqueue( idAdj );
			}
			
			currAdj = currAdj->next;	
		}
	}	
}

int *printPath( int s, int d, int p[], int pathLen ) {
	printf("\nPath from %d to %d:\n", s, d );
	
	if( p[d] == NIL ) {
		printf("There is not path from %d to %d\n", s, d );
		return NULL;
	}
	
	int i = pathLen;
	
	int *path = (int*) malloc( pathLen * sizeof(int) );
	if( !path ) {
		fprintf( stderr, "malloc error\n");
		exit(1);
	}
	
	while( p[d] != NIL ) {
		path[--i] = d;
		d = p[d];
	}
	path[--i] = d;
	
	for(i=0; i<pathLen; i++)
		printf("%d ", path[i]);
	printf("\n");
	
	return path;
}

void printPathRec( int s, int d, int p[] ) {
	if( !p ) return;
	
	if( d == s ) {
		printf("%d", s );
	}
	else if( p[d] == NIL ) {
		printf("There is not path from %d to %d\n", s, d );
	}
	else {
		printPathRec( s, p[d], p );
		printf(" %d", d );
	}	
}

int main() {
	int start, dest;
	int p[GRAPH_N_NODES];
	int d[GRAPH_N_NODES];
	Node *nodes[GRAPH_N_NODES];
	Element *connMatrix[GRAPH_N_NODES];
	
	formGraph( nodes, connMatrix );
	
	printf("\nEnter id of the starting node: \n");
	scanf("%d", &start);
	getchar();
	
	printf("\nEnter id of the destination node: \n");
	scanf("%d", &dest);
	getchar();
	
	bfs( connMatrix, d, p, start );
	
	printf("\nPath from %d to %d:\n", start, dest );
	printPathRec( start, dest, p );
	printf("\n");
	
	printPath( start, dest, p, d[dest] + 1 );
	
	return 0;
}
