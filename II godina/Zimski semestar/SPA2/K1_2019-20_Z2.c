#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    int value;
    int numLeft;
    struct _Node *left, *right;
} Node;

// Kreira novi cvor (i vraca pointer na njega) i setuje podrazumevane vrednosti
Node *NewNode(int x)
{
    Node *node = (Node*)malloc(sizeof(Node));
    
    node->value = x;
    node->left = node->right = NULL;
    node->numLeft = 0;

    return node;
}

// Dodaje novi cvor u stablo
int AddNode(Node **pRoot, int x)
{
    if(*pRoot == NULL)
        *pRoot = NewNode(x);
    else
        if(x > (*pRoot)->value)
            AddNode(&((*pRoot)->right), x);
        else
            (*pRoot)->numLeft += AddNode(&((*pRoot)->left), x);
    
    return 1;
}

// Racuna i vraca rang cvora cija je vrednost x 
int NodeRang(Node *p, int x)
{
    while (p != NULL && p->value != x)
        p = (x > p->value)? p->right : p->left;

    if(p == NULL) return -1; // ne postoji takav clan
    
    p = p->left;

    if(p == NULL) return 0;

    int numLeft = 0;
    while(p != NULL){
        numLeft += p->numLeft + 1;
        p = p->right;
    }
    
    return numLeft;
}

// Formira stablo od n elemenata koji se unose na stdin
Node *FormTree(int n)
{
    Node *root = NULL;

    int x;
    while(n > 0)
    {
        scanf("%d", &x);
        AddNode(&root, x);
        n--;
    }

    return root;
}

// Stampa stablo u trazenom formatu
void PrintTree(Node *p)
{
    if(p == NULL) return;

    PrintTree(p->left);
    printf("%d(%d) ", p->value, p->numLeft);
    PrintTree(p->right);
}

// Brise iz stabla cvor cije je vrednost x
// (ako taj cvor ima 2 podstabla, levo se kaci na ostatak stabla, a desno na najdesniji cvor levog podstabla) 
void Delete(Node **pRoot, int x)
{
	Node *p = *pRoot, **pr = pRoot;
	
    // Nalazenje cvora za brisanje
    while(p != NULL && x != p->value)
	{
		pr = (x > p->value)? &(p->right) : &(p->left);
		p = *pr;
	}

    // Ako ne postoji trazeni cvor
	if(p == NULL) return;

    // Brisanje cvora (4 slucaja)
	if(p->right && p->left) // ako cvor ima 2 podstabla
	{
		Node *mostRight = p->left;
		while(mostRight->right)
			mostRight = mostRight->right;
		
		mostRight->right = p->right;

		*pr = p->left;
	}
	else if(p->right) *pr = p->right; // ako ima samo desno podstablo
	else if(p->left) *pr = p->left; // ako ima samo levo podstablo
	else *pr = NULL; // ako nema podstabla

	free(p); // u svakom slucaju prostor se oslobadja
}

int DeleteByRang(Node **pRoot, int k) // gde je k == numLeft tog cvora
{
    int toDelete = 0, changeInLeft = 0, changeInRight = 0;
    
    // Rekurzivni poziv za levo i desno podstablo (ako postoje)
    if((*pRoot)->left != NULL)
        changeInLeft = DeleteByRang(&((*pRoot)->left), k);
    if((*pRoot)->right != NULL)
        changeInRight = DeleteByRang(&((*pRoot)->right), k);

    // Ispravka ranga (ako se desila promena u levom podstablu)
    if(changeInLeft)
        (*pRoot)->numLeft = NodeRang(*pRoot, (*pRoot)->value);

    // Brisanje (ako je to trazeni cvor)
    if(k == (*pRoot)->numLeft){
        toDelete = 1;
        Delete(pRoot, (*pRoot)->value);
    }   

    // Povratna informacija (ako se desila neka od mogucih promena)
    if(changeInLeft || changeInRight || toDelete)
        return 1;
    else
        return 0;
}

int main()
{
    int n;
    scanf("%d", &n);
    
    // Kreiranje stabla
    Node *root = FormTree(n);

    PrintTree(root);
    printf("\n");

    int k;
    scanf("%d", &k);
    
    // Brisanje
    DeleteByRang(&root, k);
    
    PrintTree(root);
    printf("\n");
}
