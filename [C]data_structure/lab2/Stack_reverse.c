#include <stdio.h>
#include <string.h>

// StackSize => 定義Stack容量大小
// stack => 堆疊 是一個全域變數，用來裝載資料。 
// top => 用來判斷Stack目前裝載的高度，預設 -1 (Empty) 
#define stackSize 50
char stack[stackSize];
char result[stackSize];
int top = -1;

// --------------------
// Stack Function 
// --------------------
// Push 放入 
void push(char item){
	//write your code.
	++top; 
	stack[top] = item;
}
// Pop 刪除 
int pop(){
	//write your code.
	stack[top] = ' ';
	--top;
}

// getTopData 取得Stack最頂端資料 
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
	// 歸零-> for第二題 
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
	// 運算式-題目1 
	char str[] = ".dlroW olleH";
	char* result = reverse(str);
	printf("====================\n");
	printf("運算式-題目1：%s\n", str);
	printf("Reverse：%s\n", result);
	printf("====================\n");
	
	// 運算式-題目2 
	char str2[] = ".erutcurtS ataD";
	char* result2 = reverse(str2);
	printf("====================\n");
	printf("運算式-題目2：%s\n", str2);
	printf("Reverse：%s\n", result2);
	printf("====================\n");
	
	return 0;
}
// --------------------
// Main Function End
// --------------------
