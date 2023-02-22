#include <stdlib.h> 
#include <stdio.h>
#include <stdbool.h>

// �w�q�`�I������
struct node{
	int data;
	struct node *next;
};

// �ŧi����head�h���V�Ĥ@�Ӹ`�I 
struct node* head = NULL;

bool isEmpty();
void insert(int insert_data);
void printList();

// �P�_linked list�O�_���� 
bool isEmpty(){
	//write your code. 
	if(head == NULL) return 1;
	else return 0;
}

void insert(int insert_data){
	//write your code. 
	struct node* new_node = malloc(sizeof(struct node));
	printf("Insert data: %d\n", insert_data);
	new_node->data = insert_data;
	// beginning
	if(isEmpty()){
		new_node->next = NULL;
		head = new_node;
	}else{
		// scan the list first
		struct node *ptr = head;
		struct node *pre = head; // node before ptr, prepared for delete
		struct node *post = NULL; // node after ptr
		struct node *deleteBox = NULL;
		while(ptr != NULL){
			post = ptr->next;
			// �ۦP���R��: 
			// equal
			if(new_node->data == ptr->data){
				printf("%d is in the list\n", insert_data);
				deleteBox = ptr;
				if(ptr == head){// it is head
					head = ptr->next;
				}else{
					pre->next = post;
				}
				free(deleteBox); // release
				ptr = NULL; // break while
			}
			// ���P���Ƨ�: 
			// smallest
			else if(new_node->data < head->data){
				new_node->next = head;
				head = new_node;
				ptr = NULL; // break while
			}
			// largest
			else if(new_node->data > ptr->data && post == NULL){
				ptr->next = new_node;
				new_node->next = NULL;
				ptr = NULL; // break while
			}
			// larger
			else if(new_node->data > ptr->data && new_node->data < post->data){
				ptr->next = new_node;
				new_node->next = post;
				ptr = NULL; // break while
			}
			
			if(ptr != head) 
				pre = ptr;// �p�Gptr�O�Ĥ@�ӡA�N�S����e����pre���� 
			if(ptr != NULL) 
				ptr = ptr->next;
		}
	} 
}

// �Nlinked list�Ҧ����`�I�L�X�� 
void printList() {
   struct node *ptr = head;
   printf("[ ");
   //�q�Y�}�l�L  
   while(ptr != NULL){
      printf("(%d) ", ptr->data);
      ptr = ptr->next;
   }
   printf(" ]\n");
}

int main(){
	
	// �C����J���Ʀr 
	int input;
	
	// Ūtxt�ɡA�|�@��@��Ū�� 
	// fopen �V opens a text file. 
	FILE *fp_r = fopen("input.txt", "r");
	
	// feof �V detects end-of-file marker in a file. 
	while(!feof(fp_r)){
		// fscanf �Vreads formatted input from a file. 
		fscanf(fp_r, "%d ", &input);
		insert(input);
		printList();
	}

	return 0;
}
