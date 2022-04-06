#include<stdio.h>

#define QueueSize 6
char Queue[QueueSize] = { };
int front = 0, rear = 0;
int flag = 0;

// --------------------
// Queue Function 
// --------------------
// Enqueue ��J 
void Enqueue(char item){
	//write your code. 
	Queue[flag] = item;
	rear = flag; // rear �O��J���̫�@�X 
	flag = (flag + 1) % QueueSize; // point ���e�@�� 
}

// Dequeue �R�� 
void Dequeue(){
	//write your code. 
	Queue[front] = ' '; // �k�s 
	front = (front + 1) % QueueSize; // front �����e���Ĥ@�X 
}

// IsEmpty �P�_�O�_���Ű}�C 
int isEmpty(){
	//write your code.
	int i = 0;
	int empty = 0;
	for(i; i < QueueSize; ++i){
		if(Queue[i] == ' ') empty++;
	}
	if(empty == 6) return 1;
	else return 0;
}

void showQueue(){
	int i;
	if (isEmpty()){
		printf("Circular Queue is empty!\n");
		return;
	}
	
	for (i = 0; i < QueueSize; i++){
		printf("%d�G%c  ", i, Queue[i]);
	}
	printf("\n");
}
// --------------------
// Queue Function End
// --------------------
// --------------------
// Main Function
// --------------------
int main(void){
	
	// �D��1 
	printf("====================\n");
	Enqueue('A');
	Enqueue('B');
	Enqueue('C');
	Enqueue('D');
	Enqueue('E');
	Enqueue('F');
	printf("Queue Statues�G");
	showQueue();
	Dequeue();
	Dequeue();
	Enqueue('G');
	Enqueue('H');
	printf("Queue Statues�G");
	showQueue();
	printf("====================\n");
}
// --------------------
// Main Function End
// --------------------
