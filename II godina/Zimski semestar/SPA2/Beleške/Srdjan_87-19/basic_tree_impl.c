#include <stdio.h>
#include <stdlib.h>

typedef struct element {
	int val;
	struct element *left, *right;
} Element;

Element *create(int val) {
	Element *newElement = (Element*) malloc(sizeof(Element));
	if( !newElement ) {
		fprintf( stderr, "alloc error\n");
		exit(1);
	}
	
	newElement->val = val;
	newElement->left = newElement->right = NULL;
	
	return newElement;
}

Element *find( Element *root, Element **previous, int val ) {
	Element *tempPrevious = NULL;
	
	while( root ) {
		if( root->val == val ) 
			break;
			
		tempPrevious = root;
		
		if( root->val > val )
			root = root->left;
		else
			root = root->right;
			
	}
	
	if( previous )
		*previous = tempPrevious;
	return root;
}

int add( Element **root, int val ) {
	if( !root ) {
		fprintf(stderr, "NULL sent as a root address\n");
		return 1;
	}
	
	Element *new = create(val);
	Element *previous = NULL;
	Element *e = find( *root, &previous, val );
	
/* debug: printf("e=%p;\tprev=%p;\tval=%d\n", e, previous, val);*/

	/* check if element with given val already exists */
	if( e ) {
		new->right = e->right;
		e->right = new;
	}
	else {
		/* check if it's root */
		if( !previous )
			*root = new;
		else {
			if( val < previous->val ) 
				previous->left = new;
			else
				previous->right = new;
		}
	}
	
	return 0;
}
	
int deleteOneByValue( Element **root, int val ) {
	if( !root ) {
			fprintf(stderr, "deleteOneByValue: sent value for root's address is NULL\n");
			return 1;
	}
	
	Element *temp = NULL;
	Element *remainingTree = NULL;
	Element *previous = NULL;
	Element *elementToDelete = find(*root, &previous, val);
	
	/* check if element with given value exists */
	if( !elementToDelete ) {
		fprintf(stderr, "deleteOneByValue: element with value %d not found\n", val );
		return 1;
	}
	
	/* element has both left and right child */ 
	if( elementToDelete->left && elementToDelete->right ) {
		temp = elementToDelete->left;
		
		/* find right most element */
		while( temp->right ) temp = temp->right;
		
		/* connect right child of the element to it's left child */
		temp->right = elementToDelete->right;
		
		remainingTree = elementToDelete->left;
	}
	/* element has only left child */ 
	else if( elementToDelete->left && !elementToDelete->right ) {
		remainingTree = elementToDelete->left;
	}
	/* element has only right child */ 
	else if( !elementToDelete->left && elementToDelete->right ) {
		remainingTree = elementToDelete->right;
	}
	else {
		/* element doesn't have neither left nor right child */ 
		remainingTree = NULL;
	}
	
	/* check if root is going to be deleted */
	if( !previous ) 
		*root = remainingTree;
	/* check if remaining tree should be connected as left or as right child */
	else if( val < previous->val )
		previous->left = remainingTree;
	else
		previous->right = remainingTree;
		
	return 0;
}
	
void printTreeInOrder_( Element *root ) {
	if( root->left )
		printTreeInOrder_( root->left );
	
	printf("%d ", root->val);
	
	if( root->right )
		printTreeInOrder_( root->right );
}

void printTreeInOrder( Element *root ) {
	printf("\nValues: \n");
	if( root )
		printTreeInOrder_( root );
	printf("\n");
}

int main() {
	Element *root = NULL;

	printf("Input order: 8,3,5,7,1\n");

	add( &root, 8 );
	add( &root, 3 );
	add( &root, 5 );
	add( &root, 7 );
	add( &root, 1 );
	
	printTreeInOrder( root );
	printf("root=%d\n",root->val);
	
	deleteOneByValue(&root, 8);
	printTreeInOrder( root );
	printf("root=%d\n",root->val);
	
	
	deleteOneByValue(&root, 3);
	printTreeInOrder( root );
	printf("root=%d\n",root->val);
	
}


/*
 *                8
 *           3		
 * 	  1	  5
 * 					7
 * */
