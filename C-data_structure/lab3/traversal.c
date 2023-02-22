/*done*/
/*practice 1*/
#include <stdio.h>
#include <stdlib.h>

//define
typedef struct Node {
    struct Node *Lchild;
    int data;
    struct Node *Rchild;
} Node; 

//create node
Node* create(int data) {
	struct Node *new_node;
	new_node = (Node* )malloc(sizeof(new_node));
	new_node->Lchild = NULL;
	new_node->Rchild = NULL;
	new_node->data = data;
} 

//preorder
void preorder(Node *root) {
	/*write your code here*/
	if(root){
		// VLR
		printf("%d ", root->data);
		preorder(root->Lchild);
		preorder(root->Rchild);
	}
}

//inorder
void inorder(Node *root) {
	/*write your code here*/
	if(root){
		// LVR
		inorder(root->Lchild);
		printf("%d ", root->data);
		inorder(root->Rchild);
	}
}

//postorder
void postorder(Node *root) {
	/*write your code here*/
	if(root){
		// LRV
		postorder(root->Lchild);
		postorder(root->Rchild);
		printf("%d ", root->data);
	}
}
   
int main() {
	//create tree
	struct Node *root;
	root = create(7);
    root->Lchild=create(43);
    root->Rchild=create(9);
    root->Lchild->Lchild=create(5);
    root->Lchild->Rchild=create(21);
    root->Rchild->Lchild=create(0);
    root->Rchild->Rchild=create(4);
    root->Lchild->Lchild->Lchild=create(13);
    
    //print answer
    printf("preorder : ");
    preorder(root);
    
    printf("\ninorder : ");
    inorder(root);
    
    printf("\npostorder : ");
    postorder(root);
    
    return 0;
}
