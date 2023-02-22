/*done*/
/*practice 4*/
#include <stdio.h> 
#include <stdlib.h> 
 
typedef struct node { 
    int data; 
    struct node *left, *right; 
} Node;

void postorder(Node* root){ 
	//write your code.
	if(root){
		postorder(root->left);
		postorder(root->right);
		printf("%d ", root->data);
	} 
} 

int preindex = 0;//用來記錄preorder[]的index 
Node* build_binary_tree(int inorder[], int preorder[], int instart, int inend, int len) 
{ 		
	//write your code.
	if(preindex == len || instart > inend) return NULL;
	Node* root = malloc(sizeof(Node));
	root->data = preorder[preindex];
	int i;
	for(i=instart; i <= inend; i++){
		if(inorder[i] == preorder[preindex]){
			preindex++;
			root->left = build_binary_tree(inorder, preorder, instart, i-1, len);
			root->right = build_binary_tree(inorder, preorder, i+1, inend, len);
			return root;
		}
	}
//	if(preindex >= len) return NULL;
//	if(preindex > inend){
//		Node* leaf = malloc(sizeof(Node));
//		leaf->data = preorder[preindex];
//		leaf->left = leaf->right = NULL;
//		return leaf;
//	}
//	Node* root = malloc(sizeof(Node));
//	root->data = preorder[preindex];
//	int i = 0;
//	for(i = instart; i <= inend; ++i){
//		if(preorder[preindex] == inorder[i]){
//			preindex++;
//			root->left = build_binary_tree(inorder, preorder, instart, i-1, len);
//			preindex++;
//			root->right = build_binary_tree(inorder, preorder, i+1, inend, len);
//		}
//	}
//	return root;
}

int main()
{
	int tree1inorder[] = {1,2,3,4,5,6,7};
	int tree1preorder[] = {4,2,1,3,6,5,7};
	int len1 = sizeof(tree1inorder)/sizeof(tree1inorder[0]);
	Node *root1 =  build_binary_tree(tree1inorder, tree1preorder, 0, len1-1, len1);
	printf("tree1 preorder traversal: 4, 2, 1, 3, 6, 5, 7 \n");
	printf("tree1 inorder traversal: 1, 2, 3, 4, 5, 6, 7 \n");
	printf("tree1 postorder traversal: ");
    postorder(root1);
    preindex = 0;
    
    int tree2inorder[] = {5,9,3,8,4,7,6};
	int tree2preorder[] = {8,9,5,3,7,4,6};
	int len2 = sizeof(tree2inorder)/sizeof(tree2inorder[0]);
	Node *root2 =  build_binary_tree(tree2inorder, tree2preorder, 0, len2-1, len2);
	printf("\n\ntree2 preorder traversal: 8, 9, 5, 3, 7, 4, 6 \n");
	printf("tree2 inorder traversal: 5, 9, 3, 8, 4, 7, 6 \n");
	printf("tree2 postorder traversal: ");
    postorder(root2);
    preindex = 0;
    
    return 0;
}

/*tree1

      4
    /  \
   2    6
 / \   / \
1  3  5   7

*/
/*tree2
      8
    /  \
   9    7
 / \   / \
5  3  4   6

*/
