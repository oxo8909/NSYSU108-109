#include<stdio.h>

#define QueueSize 6
char Queue[QueueSize] = { };
int front = 0, rear = 0;
int flag = 0;

// --------------------
// Queue Function 
// --------------------
// Enqueue 放入 
void Enqueue(char item){
	//write your code. 
	Queue[flag] = item;
	rear = flag; // rear 是輸入的最後一碼 
	flag = (flag + 1) % QueueSize; // point 往前一格 
}

// Dequeue 刪除 
void Dequeue(){
	//write your code. 
	Queue[front] = ' '; // 歸零 
	front = (front + 1) % QueueSize; // front 有內容的第一碼 
}

// IsEmpty 判斷是否為空陣列 
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
		printf("%d：%c  ", i, Queue[i]);
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
	
	// 題目1 
	printf("====================\n");
	Enqueue('A');
	Enqueue('B');
	Enqueue('C');
	Enqueue('D');
	Enqueue('E');
	Enqueue('F');
	printf("Queue Statues：");
	showQueue();
	Dequeue();
	Dequeue();
	Enqueue('G');
	Enqueue('H');
	printf("Queue Statues：");
	showQueue();
	printf("====================\n");
}
// --------------------
// Main Function End
// --------------------
