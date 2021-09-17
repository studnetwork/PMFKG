/* bug: zeza kad se unese nesto sto nije broj */

#include <stdio.h>
#include <stdlib.h>

typedef struct element {
	int content;
	struct element *next;
} Element;

/*
 * */
void printList( Element *startingElement ) {
	printf("\nList values:\n");
	while( startingElement ) {
		printf("%d ", startingElement->content);
		startingElement = startingElement->next;
	}
	printf("\n");
}

/*
 * */
Element *createElement(int content) {
	Element *newEl = (Element*) malloc(sizeof(Element));
	if( !newEl ) {
		printf("alloc error\n");
		exit(1);
	}
	
	newEl->content = content;
	newEl->next = NULL;
	
	return newEl;
}

/* add: adds element to the end of the list
 * 
 * params:
 * 	head - a pointer that represents head of the list 
 * 	newEl - a pointer to the element which is going to be added
 * returns:
 * 	0 if addition was successful
 * 	1 otherwise 
 * */
int add( Element **head, Element *newEl ) {
	/* check if call as invalid value for the head */
	if( !head ) {
		fprintf(stderr, "add: sent address of the head is NULL\n");
		return 1;
	}
	
	/* check if the list is empty */
	if( !*head ) {
		*head = newEl;
	}
	else {
		/* go to the end of the list */
		Element *temp = *head;
		while( temp->next ) 
			temp = temp->next;
			
		temp->next = newEl;
	}
	
	return 0;
}

/* addValue: adds element of given value to the end of the list
 * 
 * params:
 * 	head - a pointer that represents head of the list 
 * 	content - a value of the new element which will be created and added to the end of the list
 * returns:
 * 	0 if addition was successful
 * 	1 otherwise 
 * */
int addValue( Element **head, int content ) {
	int failed;
	Element *newEl = createElement(content);
	
	failed = add( head, newEl );
	if(  failed )
		free( newEl );
	
	return failed;
} 

/* deleteAt: deletes element at given index 
 * 
 * params:
 * 	head - a pointer that represents head of the list 
 * 	index - a non-negative integer that represents index of element that should be deleted 
 * returns:
 * 	0 if deletion was successful
 * 	1 otherwise 
 * */
int deleteAt( Element **head, int index ) {
	/* check if call as invalid value for the head */
	if( !head ) {
		fprintf(stderr, "deleteAt: sent address of the head is NULL\n");
		return 1;
	}
	
	/* check if the list is empty */
	if( !*head ) {
		fprintf(stderr, "deleteAt: list is empty\n");
		return 1;
	}
	
	if( index < 0 ) {
		fprintf(stderr, "deleteAt: index can't be negative number\n");
		return 1;
	}
	
	/* find the element which is going to be deleted */
	int i = 0;
	Element *temp = *head;
	Element *previous = NULL;
	while( temp && i++ < index ) {
		previous = temp;
		temp = temp->next;
	}
	
	/* check if index is out of the range */
	if( temp == NULL ) {
		fprintf(stderr, "deleteAt: index is out of the range\n");
		return 1;
	}
		
	/* check if the head is going to be deleted or not */
	if( index == 0 ) 
		*head = temp->next;
	else
		previous->next = temp->next;

	free(temp);
	
	return 0;
}

/* revert: reverts order of the list 
 * 
 * params:
 * 	head - a pointer that represents head of the list 
 * returns:
 * 	0 if revert was successful
 * 	1 otherwise 
 * */
int revert( Element **head ) {
	/* check if call as invalid value for the head */
	if( !head ) {
		fprintf(stderr, "revert: sent address of the head is NULL\n");
		return 1;
	}
	
	/* check if the list is empty */
	if( !*head ) {
		fprintf(stderr, "revert: list is empty\n");
		return 1;
	}
	
	Element *current= *head;
	Element *previous = NULL;
	Element *temp;
	do {
		temp = current->next;
		current->next = previous;
		previous = current;
		current = temp;
	} while( current );
	
	*head = previous;
	
	return 0;
}

int main() {
	Element *head = NULL;
	
	int c;
	int broj;
	do {
		printf("\n(a)dd\t\t(d)elete\t\t(r)evert\t\t(p)rint\n");
		printf("Choise: ");
		
		c = getchar(); getchar();
		switch(c) {
			case 'a':
				printf("\nEnter a number: ");
				scanf("%d", &broj); getchar();
				
				if( addValue(&head, broj) )
					printf("Failed: element is not added to the end of the list\n");
				else
					printf("Succeed: element is added to the end of the list\n");
					
				break;
				
			case 'd':
				printf("\nEnter index of the element that you want to delete: ");
				scanf("%d", &broj); getchar();
				
				if( deleteAt( &head, broj ) )
					printf("Failed: element at index %d is not deleted\n", broj);
				else
					printf("Succeed: element at index %d is deleted\n", broj);
				break;
				
			case 'r':
				if( revert(&head) )
					printf("Failed: revert was not successful\n");
				else
					printf("Succeed: revert was successful\n");
				break;
				
			case 'p':
				printList(head);
				break;
			
			default:
				printf("Unknown choice \n");
		}
				
	} while (1);
}
