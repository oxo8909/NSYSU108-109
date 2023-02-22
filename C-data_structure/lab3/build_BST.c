/*done*/
/*practice 3*/
#include <stdio.h> 
#include <stdlib.h> 
  
typedef struct node { 
    int data; 
    struct node *left, *right; 
} Node;
// arr method
int arr[20] = {0};
int a = 0;
void arrToNull(){
	int i = 0;
	for(i; i < 20; ++i){
		arr[i] = 0;
	}
	a = 0;
} 
// end define arr

void inorder(Node* root){ 
	//write your code. 
	if(root){
		inorder(root->left);
//		printf("%d ", root->data);
		arr[a] = root->data;
		a++;
		inorder(root->right);
	}
} 

int count_non = 0;
int countnonleaf(Node* node){
	//write your code.  
	if(node){
		if(node->left || node->right) count_non++;
		countnonleaf(node->left);
		countnonleaf(node->right);
	}
	return count_non;
}
int count = 0;
int countleaf(Node* node){
	//write your code.
	if(node){
		if(!(node->left) && !(node->right)) count++;
		countleaf(node->left);
		countleaf(node->right);
	}
	return count;
}

int height(Node* node){
    //write your code.
    int leftHeight = 0;
    int rightHeight = 0;
    
    if(!node) return 0;
    else{
    	leftHeight = height(node->left);
    	rightHeight = height(node->right);
    	if(leftHeight > rightHeight){
    		return (leftHeight+1);
		}else{
			return (rightHeight+1);
		}
	}
}

// when is_BST, it's inorder being from small to big
int is_BST(Node* node){  
	//write your code.
	if(node){
		arrToNull();
		inorder(node);
		int b = 1;
		for(b; arr[b] != 0; ++b){
			if(arr[b-1] > arr[b]) return 0;
		}
		return 1;
	}
}
/*i do not know!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1*/
Node* insert(Node* node, int data){ 
    //write your code.
    Node* ptr = NULL;
	Node* current = NULL; 
	Node* previous = NULL;
    ptr = malloc(sizeof(Node));
    ptr->data = data;
    ptr->left = ptr->right = NULL;
    
    if(!node)
    	node = ptr;
    else {
    	current = node;
    	while(current){
    		previous = current;
    		if(ptr->data < current->data)
    		current = current->left;
    		else
    		current = current->right;
		}
		if(ptr->data < previous->data)
			previous->left = ptr;
		else
			previous->right = ptr;
	}
  	return node;
//    Node* new_node = malloc(sizeof(Node));
//	new_node->data = data;
//	new_node->left = new_node->right = NULL;
//	   	
//	
//	if(!node) return new_node;
//	
//	if(data < node->data){
//		node->left = insert(node->left, data);
//	}
//	else{
//		node->right = insert(node->right, data);
//	} 
//	
//	return node;
	
//    if(node->left && node->right){
//    	if(data < (node->left)->data){
//			insert(node->left, data);
//		}else{
//			insert(node->right, data);
//		}
//	}else{
//		Node* new_node = malloc(sizeof(Node));
//	    new_node->data = data;
//	   	new_node->left = new_node->right = NULL;
//		/*左*/
//		if(data < node->data) node->left = new_node;
//		/*右*/ 
//	    else node->right = new_node;
//	}
} 

int main() 
{ 
    int insert_data[] = {8,4,12,2,6,10,14,1,3,5,7,9,11,13,15};
	Node* root = NULL; 
	int i;
	// 先讓root有東西 
//	root->data = insert_data[0];
//	root->left = root->right = NULL;
    root = insert(root, insert_data[0]);
	int len = sizeof(insert_data)/sizeof(insert_data[0]); 
    for(i=1;i<len;i++)
    {
    	insert(root, insert_data[i]);
	}
	printf("inorder traversal: ");
	inorder(root);
	for(i=0; arr[i] != 0; ++i){
		printf("%d ", arr[i]);
	}
//    inorder(root);
    printf("\nis BST: %d\n",is_BST(root));
	printf("\nroot data: %d\n",root->data);
	printf("the number of leaves: %d\n",countleaf(root));
	printf("the number of non-leaves: %d\n",countnonleaf(root));
	printf("height: %d\n\n",height(root));
		
	root->data = 20;
	arrToNull();
	inorder(root);
	printf("將其修改為非二元搜尋樹: \n");
	printf("inorder traversal: ");
	for(i=0; arr[i] != 0; ++i){
		printf("%d ", arr[i]);
	} 
//    inorder(root);
    printf("\nis BST: %d\n",is_BST(root));
    
    return 0; 
}

/*

         8
       /   \
      4    12
    / \    / \
  2   6   10  14
 /\  /\  / \  / \
1 3 5 7 9 11 13 15

*/

