#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
// OPSize => �w�q�B��l�`�j�p5
// OP => ��N�B��l(Arithmetic Operator) 
// OP_Priority => �ΨӦs��B��l���u������ 
#define OPSize 5
char OP[OPSize] = {'(', '+' , '-' , '*' , '/'};
int OP_Priority[OPSize] = {0, 1, 1, 2, 2};

// StackSize => �w�qStack�e�q�j�p
// stack => ���| �O�@�ӥ����ܼơA�ΨӸ˸���ơC 
// top => �ΨӧP�_Stack�ثe�˸������סA�w�] -1 (Empty) 
#define stackSize 50
char stack[stackSize];
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
char pop(){ 
	//write your code.
	int p = stack[top];
	stack[top] = ' ';
	--top;
	
	return p;
}
// IsEmpty �P�_�O�_���Ű}�C 
int IsEmpty(void){
	//write your code.
	if(top == -1) return 1;
	else return 0;
}
// IsFull �P�_�O�_�������}�C 
int IsFull(){
	//write your code.
	if((top + 1) > (stackSize - 1)) return 1;
	else return 0;
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
// getPriority ���o�B��l���u���� 
int getPriority(char c){
   int i;
   for(i=0; i<OPSize; i++){
      if(OP[i] == c){
         return OP_Priority[i];
	  } 
   } 
   return -1;
}

//  �P�_�Q�i�� 
int IsDigit(char c){
	if(c>='0' && c<='9'){
		return 1;
	}else{
		return 0;
	}
}

// convertPostfix => infix(����) ��� postfix(���) 
void convertPostfix(char infix[], char postfix[]){
	//write your code.
	int i = 0, j = 0;
	
	while(infix[i] != '\0'){
		// ��: �Ʀr -> �����s�i postfix 
		if(IsDigit(infix[i])){
			postfix[j++] = infix[i++];
		}
		// �L: '(' -> �����s�i stack 
		else if(infix[i] == '('){
			push(infix[i++]);
		}
		// ��: ')' -> ���� pop �X�ӡA�s�i postfix 
		else if(infix[i] == ')'){
			while(!IsEmpty()){
				if(getTopData() != '(') postfix[j++] = pop();
				else pop();
			}
			i++;
		}
		// �v: ��L 
		else{
			// stack is empty
			if(IsEmpty()){
				push(infix[i++]);
			}
			// �n��� 
			else{
				// stack �w�g�񤣤U 
				if(IsFull()) printf("Error.");
				
				else{
					// �n��i�h������j 
					if(getPriority(infix[i]) > getPriority(getTopData())){
						push(infix[i++]);
					}
					// �S������j
					else{
						while(getPriority(infix[i]) <= getPriority(getTopData())){
							postfix[j++] = pop();
						}
						push(infix[i++]);
					} 
				}
			}
		} // end of ��L 
	} // end of scanning infix
	
	// ���y�� infix ��� stack �����F��� pop �X�ө�i postfix 
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
                
        // C�y���� -'0' �O�NASCII �����ܥL�� int 
        int a=pop()-'0';
		int b=pop()-'0';
		int c=0;
		
        printf("�L�{�G%d %c %d = ", b, postfix[point], a);
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
    printf("result�G%d \n", result); 
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
	char infix[] = "(1+2)*(5+6)";
	char postfix[strlen(infix)];
	convertPostfix(infix, postfix);
	float result = calculate(postfix);
	printf("====================\n");
	printf("�B�⦡-�D��1�G%s\n", infix);
	printf("infix Size�G%d\n", strlen(infix));
	printf("���ǡG%s\n", infix);
	printf("��ǡG%s\n", postfix);
	printf("��Ǫ��p�⵲�G�G%.2f\n", result);
	printf("====================\n");
	
	// �B�⦡-�D��2 
	char infix2[] = "(4+9)*(9-3)+1";
	char postfix2[strlen(infix2)];
	convertPostfix(infix2, postfix2);
	float result2 = calculate(postfix2);
	printf("====================\n");
	printf("�B�⦡-�D��2�G%s\n", infix2);
	printf("infix Size�G%d\n", strlen(infix2));
	printf("���ǡG%s\n", infix2);
	printf("��ǡG%s\n", postfix2);
	printf("��Ǫ��p�⵲�G�G%.2f\n", result2);
	printf("====================\n");
}
// --------------------
// Main Function End
// --------------------

