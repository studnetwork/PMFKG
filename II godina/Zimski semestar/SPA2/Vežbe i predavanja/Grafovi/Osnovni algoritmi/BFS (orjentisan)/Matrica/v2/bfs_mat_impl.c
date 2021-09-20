/*
0 1
1 2
2 3
0 4
4 3
3 1
-1 -1
*/

#include <stdio.h>
#include <stdlib.h>

#define GRAPH_N_NODES 5
#define INFINITY (-1)
#define NIL (-1)

#define NOT_CONNTECTED 0
#define CONNECTED 1

typedef struct element_ {
	int index;
	struct element_ *next;
} Element;

typedef struct queue_ {
	Element *head;
	Element *tail;
} Queue;

Element *create( int index ) {
	Element *new = (Element*) malloc( sizeof(Element) );
	if( !new ) {
		fprintf(stderr, "malloc error\n");
		exit(1);
	}
	
	new->index = index;
	new->next = NULL;
	
	return new;
}

void enqueue( Queue *queue, int index ) {
	if( !queue )
		return;
	
	Element *new = create(index);
	
	/* check if there is no element in the queue */
	if( !queue->head && !queue->tail ) 
		queue->head= queue->tail = new;
	/* check if there is any element in the queue */	
	else if( queue->head && queue->tail ) {
		queue->tail->next = new;
		queue->tail = new;
	}
	/* queue does not have proper form */
	else {
		fprintf(stderr, "malformed queue\n");
		printf("%p %p\n", queue->head, queue->tail );
		exit(1);
	}
}

int dequeue( Queue *queue ) {
	if( !queue )
		return NIL;
		
	if( (queue->head && !queue->tail)
			|| (!queue->head && queue->tail) ) {
		fprintf(stderr, "malformed queue\n");
		exit(1);
	}
		
	Element *head = queue->head;
	int index = NIL;
	
	if( !head ) 
		printf("queue is empty\n");
	else {
		if( head == queue->tail )
			queue->tail = NULL;
			
		queue->head = queue->head->next;
		index = head->index;
		free( head );
	}
	
	return index;
}

void initialize( int (*connMatrix)[GRAPH_N_NODES], int d[], int p[] ) {
	int i, j;
	
	for( i = 0; i < GRAPH_N_NODES; i++) {
		d[i] = INFINITY;
		p[i] = NIL;
		
		for( j = 0; j < GRAPH_N_NODES; j++ )
			connMatrix[i][j] = NOT_CONNTECTED;
	}
}

void formGraph( int (*connMatrix)[GRAPH_N_NODES] ) {
	int i, a, b;
	
	i = 0;
	printf("Enter edges ( format: a b ):\t\t\t-1 -1 to stop\n");
	while( i++ < GRAPH_N_NODES*GRAPH_N_NODES ) {
		scanf("%d%d", &a, &b);
		getchar();
		
		if( a == -1 || b == -1 )
			break;
		
		connMatrix[a][b] = CONNECTED;
	} 
}

void bfs( int (*connMatrix)[GRAPH_N_NODES], int d[], int p[], Queue *queue,  int start ) {
	int u, v;
	
	d[start] = 0;
	enqueue( queue, start );
	
	while( NIL != ( u = dequeue( queue ) ) ) {
		for( v=0; v < GRAPH_N_NODES; v++ ){
			if( CONNECTED == connMatrix[u][v]
				&& d[v] == INFINITY ) {
					d[v] = d[u] + 1;
					p[v] = u;
					enqueue( queue, v );
				}
		}
	}
}

void printPathRec( int s, int d, int p[] ) {
	if( !p ) {
		fprintf(stderr, "Address of the predecessor array is empty\n");
		exit(1);
	}
	
	if( d == s )
		printf("%d", s );
	else if( p[d] == NIL ) 
		printf("There is not path from %d to %d\n", s, d);
	else {
		printPathRec( s, p[d], p );
		printf(" %d", d);
	}
}

int main() {
	Queue queue;
	int start, dest;
	int d[GRAPH_N_NODES];
	int p[GRAPH_N_NODES];
	int connMatrix[GRAPH_N_NODES][GRAPH_N_NODES];
	
	initialize( connMatrix, d, p );
	formGraph( connMatrix );
	
	queue.head = queue.tail = NULL;
	
	while( 1 ) {
		printf("\nEnter index of the starting node: \n");
		scanf("%d", &start );
		getchar();
		
		if( start < 0 || start > GRAPH_N_NODES - 1 )
			printf("Index of starting node is not in the interval [0,%d]\n", GRAPH_N_NODES - 1);
		else
			break;
	}
	
	while( 1 ) {
		printf("\nEnter index of the destination node: \n");
		scanf("%d", &dest );
		getchar();
		
		if( start < 0 || start > GRAPH_N_NODES - 1 )
			printf("Index of destination node is not in the interval [0,%d]\n", GRAPH_N_NODES - 1);
		else
			break;
	}
	
	bfs( connMatrix, d, p, &queue, start );
	printPathRec( start, dest, p );
	
}
