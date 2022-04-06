/*done*/
/*practice 2*/
/*when processing "&&", supposed A && B, if A is false, it will not compute B*/
#include <stdio.h> 
#include <stdlib.h> 
#include<math.h>

typedef struct Node {
    struct Node *Lchild;
    int data;
    struct Node *Rchild;
} Node; 

//創建節點
Node* create(int data) {
	struct Node *new_node;
	new_node = (Node* )malloc(sizeof(new_node));
	new_node->Lchild = NULL;
	new_node->Rchild = NULL;
	new_node->data = data;
} 

int identical(Node *T, Node *T2) {
	/*write your code here*/
	return (/*(T=NULL^T2=NULL) = TRUE; (T=1^T2=1) = FALSE; others = FALSE*/(!T && !T2) || (/*T not NULL*/T && /*T2 not NULL*/T2 && /*preorder = VLR*/(T->data == T2->data) && identical(T->Lchild, T2->Lchild) && identical(T->Rchild, T2->Rchild)));
}

//search
int search(Node *root,int search_val) {
	/*write your code here*/
	return (/*root is not NULL*/root && ((root->data == search_val) || (search(root->Lchild, search_val)) || (search(root->Rchild, search_val))));
}


int main() {
	//tree 
	struct Node *root;
	root = create(7);
    root->Lchild=create(43);
    root->Rchild=create(9);
    root->Lchild->Lchild=create(5);
    root->Lchild->Rchild=create(21);
    root->Rchild->Rchild=create(4);
    root->Lchild->Lchild->Lchild=create(13);
	//tree 1
	struct Node *root1;
	root1 = create(7);
    root1->Lchild=create(43);
    root1->Rchild=create(9);
    root1->Lchild->Lchild=create(5);
    root1->Lchild->Rchild=create(21);
    root1->Rchild->Rchild=create(4);
    root1->Lchild->Lchild->Lchild=create(13);
	//tree 2
	struct Node *root2;
	root2 = create(7);
    root2->Lchild=create(2);
    root2->Rchild=create(9);
    root2->Lchild->Lchild=create(5);
    root2->Lchild->Rchild=create(21);
    root2->Rchild->Lchild=create(0);
    root2->Rchild->Rchild=create(4);
    
    printf("Does tree and tree1 identical ?  %d\n",identical(root,root1));
    printf("Does tree and tree2 identical ?  %d\n",identical(root,root2));
    
    printf("\nsearch : ");
	printf(" \nDoes 2 exist in tree?: ");
	printf(search(root,2) ? "true" : "false");
	printf(" \nDoes 2 exist tree2?: ");
	printf(search(root2,2) ? "true" : "false");
    
/*   
tree
       7   
     /   \   
    43   9   
   /   \   \   
   5   21   4
  /
 13 
  
*/

/*   
tree1
       7   
     /   \   
    43   9   
   /   \   \   
   5   21   4
  /
 13 
   
*/

/*   
tree2
        7   
     /     \   
    2       9   
   /   \   / \   
   5   21 0   4
   
*/
}
