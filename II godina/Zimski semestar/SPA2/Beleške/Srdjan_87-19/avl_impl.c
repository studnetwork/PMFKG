#include <stdio.h>
#include <stdlib.h>

/* extra parenthesis are NEEDED */
#define MIN( a, b ) ( (a) < (b) ) ? (a) : (b)
#define MAX( a, b ) ( (a) > (b) ) ? (a) : (b)

typedef struct node {
	int val;
	int balance;
	struct node *left, *right;
} Node;

void printInOrder_( Node *tree ) {
	if( tree->left )
		printInOrder_( tree->left );
		
	printf("%d ", tree->val );
	
	if( tree->right )
		printInOrder_( tree->right );
}

void printInOrder( Node *tree ) {
	if( !tree ) {
		printf("List is empty\n");
		return;
	}
	printf("List data:\n");
	printInOrder_(tree);
	printf("\n\n");
}


void printPreOrder_( Node *tree ) {
	printf("%d ", tree->val );
	
	if( tree->left )
		printPreOrder_( tree->left );
		
	if( tree->right )
		printPreOrder_( tree->right );
}

/* used for debugging */
void printPreOrder( Node *tree ) {
	if( !tree ) {
		printf("List is empty\n");
		return;
	}
	printf("List data:\n");
	printPreOrder_(tree);
	printf("\n\n");
}


Node *create( int val ) {
	Node *new = (Node*) malloc( sizeof( Node ) );
	
	if( !new ) {
		fprintf(stderr, "alloc error\n");
		exit(1);
	}
	
	new->val = val;
	new->balance = 0;
	new->left = new->right = NULL;
	
	return new;
}

/* left rotation */
void lrotation( Node **tree ) {
	if( tree && *tree && (*tree)->right ) {
		Node *left, *right;
		
		left = *tree;
		right = left->right;
		
		left->right = right->left;
		right->left = left;
		*tree = right;
		
		/* leftNewBalance = leftOldBalance + min( 0, - rightOldBalance ) - 1 */
		left->balance += MIN( -1,  -1 - right->balance );
		
		/* rightNewBalance = rightOldBalance + max( 0, leftNewBalance ) + 1 */
		right->balance += MAX( 1, 1 + left->balance );
	}
}

/* right rotation */
void rrotation( Node **tree ) {
	if( tree && *tree && (*tree)->left ) {
		Node *left, *right;
		
		right = *tree;
		left = right->left;
		
		right->left = left->right;
		left->right = right;
		*tree = left;
		
		/* rightNewBalance = rightOldBalance + min( 0, - leftOldBalance ) + 1 */
		right->balance += MIN( 1, 1 - left->balance ) ;
		
		/* leftNewBalance = leftOldBalance + max( 0, rightNewBalance ) + 1 */
		left->balance += MAX( 1, 1 + right->balance );
	}
}

int add( Node **tree, int val ) {
	if( !tree ) {
		fprintf( stderr, "add: address of the tree cannot be NULL\n");
		return 0;
	}
	
	int inc;
	int result = 0;
	Node *t = *tree;

	/* add new node if tree is empty */
	if( !t ) {
		t = create( val );
		result = 1;
	}
	else {
		
		/* add element to appropriate subtree */
		if( val < t->val ) 
			inc = - add( &t->left, val );
		else 
			inc = add( &t->right, val );
			
		/* update balance of the current node */
		t->balance += inc;
		
		if( inc != 0 && t->balance != 0 ) {
			/*  check if tree is too much inclined to the left  */
			if( t->balance < -1 ) {
				/*  check if subtree is inclined to the left or the right */
				if( t->left->balance < 0 ) 
					rrotation( &t );
				else {
					lrotation( &t->left );
					rrotation( &t );
				}
			}
			/*  check if tree is too much inclined to the right  */
			else if( t->balance > 1 ) {
				/*  check if subtree is inclined to the left or the right */
				if( t->right->balance > 0 ) 
					lrotation( &t );
				else {
					rrotation( &t->right );
					lrotation( &t );
				}
			}
			else
				result = 1;
		}
	}
	
	*tree = t;
	
	return result;
}

int main() {
	Node *root = NULL;
	int i = 10;
	while( i-- ) 
		add( &root, i );
	
//	add( &root, -1); // debug
//	add( &root, -2); // debug
	printInOrder( root );
	printPreOrder( root );
	
	printf("root=%d\n%d-%d\n", root->val,root->left->val,root->right->val);
}
