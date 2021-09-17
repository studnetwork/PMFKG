#include <stdio.h>
#include <stdlib.h>

#define STACK_SZ 20

typedef struct {
	int val;
} Item;

typedef struct {
	int top;
	Item **items;
} Stack;

Item *createItem(int val) {
	Item *item = NULL;
	
	item = (Item*) malloc(sizeof(Item));
	if( !item ) {
		fprintf(stderr, "error: malloc");
		exit(1);
	}
	
	item->val = val;
	
	return item;
}

void push(Stack *stack, Item *item) {
	if( stack->top >= STACK_SZ-1 ) 
		fprintf(stderr, "stack size exceeded\n");
	else {
		stack->top++;
		stack->items [stack->top] = item;
	}
}

Item *pull(Stack *stack) {
	Item *item = NULL;
	
	if( stack->top < 0 ) 
		fprintf(stderr, "pull failed: stack is empty\n");
	else {
		item = stack->items[stack->top];
		stack->items[stack->top] = NULL;
		stack->top--;
	}
	
	return item;
}

void printStack(Stack *stack) {
	if( !stack ||  !stack->items ) {
		fprintf(stderr, "stack is empty\n");
		return;
	}
	
	printf("Stack print:\n");
	
	Item **items = stack->items ;
	while( *items ) {
		printf("%d ", (*items)->val );
		items++;
	}
	printf("\n");
}

int main() {
	Stack stack;
	stack.top = -1;
	
	stack.items = (Item**) malloc(STACK_SZ * sizeof(Item*));
	if( !stack.items ) {
		fprintf(stderr, "error: malloc\n");
		exit(1);
	}
	
	printStack(&stack);
	
	int c;
	int broj;
	Item *item;
	do {
		printf("\n(u)nesi\t(i)zbaci\t\t(p)rikaz\n");
		printf("Izbor: ");
		
		c = getchar(); getchar();
		switch(c) {
			case 'u':
				printf("\nUnesite broj: ");
				scanf("%d", &broj); getchar();
				
				push(&stack, createItem(broj));
				break;
				
			case 'i':
				item = pull(&stack);
				if( item )
					printf("Izbacen: %d\n", item->val );
				break;
				
			case 'p':
				printStack(&stack);
				break;
			
			default:
				printf("Nepoznata opcija\n");
		}
				
	} while (1);
}
