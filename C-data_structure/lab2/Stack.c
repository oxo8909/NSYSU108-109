#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
// OPSize => 定義運算子總大小5
// OP => 算術運算子(Arithmetic Operator) 
// OP_Priority => 用來存放運算子的優先順序 
#define OPSize 5
char OP[OPSize] = {'(', '+' , '-' , '*' , '/'};
int OP_Priority[OPSize] = {0, 1, 1, 2, 2};

// StackSize => 定義Stack容量大小
// stack => 堆疊 是一個全域變數，用來裝載資料。 
// top => 用來判斷Stack目前裝載的高度，預設 -1 (Empty) 
#define stackSize 50
char stack[stackSize];
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
char pop(){ 
	//write your code.
	int p = stack[top];
	stack[top] = ' ';
	--top;
	
	return p;
}
// IsEmpty 判斷是否為空陣列 
int IsEmpty(void){
	//write your code.
	if(top == -1) return 1;
	else return 0;
}
// IsFull 判斷是否為滿的陣列 
int IsFull(){
	//write your code.
	if((top + 1) > (stackSize - 1)) return 1;
	else return 0;
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
// getPriority 取得運算子的優先序 
int getPriority(char c){
   int i;
   for(i=0; i<OPSize; i++){
      if(OP[i] == c){
         return OP_Priority[i];
	  } 
   } 
   return -1;
}

//  判斷十進位 
int IsDigit(char c){
	if(c>='0' && c<='9'){
		return 1;
	}else{
		return 0;
	}
}

// convertPostfix => infix(中序) 轉至 postfix(後序) 
void convertPostfix(char infix[], char postfix[]){
	//write your code.
	int i = 0, j = 0;
	
	while(infix[i] != '\0'){
		// 壹: 數字 -> 直接存進 postfix 
		if(IsDigit(infix[i])){
			postfix[j++] = infix[i++];
		}
		// 貳: '(' -> 直接存進 stack 
		else if(infix[i] == '('){
			push(infix[i++]);
		}
		// 參: ')' -> 全部 pop 出來，存進 postfix 
		else if(infix[i] == ')'){
			while(!IsEmpty()){
				if(getTopData() != '(') postfix[j++] = pop();
				else pop();
			}
			i++;
		}
		// 肆: 其他 
		else{
			// stack is empty
			if(IsEmpty()){
				push(infix[i++]);
			}
			// 要比較 
			else{
				// stack 已經放不下 
				if(IsFull()) printf("Error.");
				
				else{
					// 要放進去的比較大 
					if(getPriority(infix[i]) > getPriority(getTopData())){
						push(infix[i++]);
					}
					// 沒有比較大
					else{
						while(getPriority(infix[i]) <= getPriority(getTopData())){
							postfix[j++] = pop();
						}
						push(infix[i++]);
					} 
				}
			}
		} // end of 其他 
	} // end of scanning infix
	
	// 掃描完 infix 後把 stack 中的東西全 pop 出來放進 postfix 
	if(infix[i] == '\0'){
		while(!IsEmpty()){
			postfix[j++] = pop();
		}
	} 
}

int calculate(char postfix[]){
    int point=0;
    int result = 0;
    while(postfix[point]!='\0')
    {
        while(IsDigit(postfix[point])){
        	push(postfix[point++]);
		}
                
        // C語言中 -'0' 是將ASCII 對應至他的 int 
        int a=pop()-'0';
		int b=pop()-'0';
		int c=0;
		
        printf("過程：%d %c %d = ", b, postfix[point], a);
        switch(postfix[point])
        {
			case'+':
				c=b+a;
				break;
			case'-':
				c=b-a;
				break;
			case'*':
				c=b*a;
				break;
			case'/':
				c=b/a;
				break;
        }
        printf("%d \n", c);
        push(c+'0');
        point++;
        result = c;
    }
    pop() -'0';
    printf("result：%d \n", result); 
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
	char infix[] = "(1+2)*(5+6)";
	char postfix[strlen(infix)];
	convertPostfix(infix, postfix);
	float result = calculate(postfix);
	printf("====================\n");
	printf("運算式-題目1：%s\n", infix);
	printf("infix Size：%d\n", strlen(infix));
	printf("中序：%s\n", infix);
	printf("後序：%s\n", postfix);
	printf("後序的計算結果：%.2f\n", result);
	printf("====================\n");
	
	// 運算式-題目2 
	char infix2[] = "(4+9)*(9-3)+1";
	char postfix2[strlen(infix2)];
	convertPostfix(infix2, postfix2);
	float result2 = calculate(postfix2);
	printf("====================\n");
	printf("運算式-題目2：%s\n", infix2);
	printf("infix Size：%d\n", strlen(infix2));
	printf("中序：%s\n", infix2);
	printf("後序：%s\n", postfix2);
	printf("後序的計算結果：%.2f\n", result2);
	printf("====================\n");
}
// --------------------
// Main Function End
// --------------------

