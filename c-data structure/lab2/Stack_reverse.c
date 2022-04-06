#include <stdio.h>
#include <string.h>

// StackSize => �w�qStack�e�q�j�p
// stack => ���| �O�@�ӥ����ܼơA�ΨӸ˸���ơC 
// top => �ΨӧP�_Stack�ثe�˸������סA�w�] -1 (Empty) 
#define stackSize 50
char stack[stackSize];
char result[stackSize];
int top = -1;

// --------------------
// Stack Function 
// --------------------
// Push ��J 
void push(char item){
	//write your code.
	++top; 
	stack[top] = item;
}
// Pop �R�� 
int pop(){
	//write your code.
	stack[top] = ' ';
	--top;
}

// getTopData ���oStack�̳��ݸ�� 
char getTopData(){
	//write your code.
	return stack[top]; 
}
// --------------------
// Stack Function End
// --------------------
// --------------------
// Calculate Function
// --------------------
char* reverse(char str[]){
	//write your code. 
	// �k�s-> for�ĤG�D 
	int i = 0;
	for(i = 0; i < stackSize; ++i){
		result[i] = ' ';
	}
	
	// str into stack
	for(i = 0; str[i] != '\0'; ++i){
		push(str[i]);
	}
	
	// top of stack into result
	for(i = 0; top > -1; ++i){
		result[i] = getTopData();
		pop();
	}
	return result;
}
// --------------------
// Calculate Function End
// --------------------
// --------------------
// Main Function
// --------------------
int main(void){ 
	// �B�⦡-�D��1 
	char str[] = ".dlroW olleH";
	char* result = reverse(str);
	printf("====================\n");
	printf("�B�⦡-�D��1�G%s\n", str);
	printf("Reverse�G%s\n", result);
	printf("====================\n");
	
	// �B�⦡-�D��2 
	char str2[] = ".erutcurtS ataD";
	char* result2 = reverse(str2);
	printf("====================\n");
	printf("�B�⦡-�D��2�G%s\n", str2);
	printf("Reverse�G%s\n", result2);
	printf("====================\n");
	
	return 0;
}
// --------------------
// Main Function End
// --------------------
