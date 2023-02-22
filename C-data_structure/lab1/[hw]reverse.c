#include <stdio.h>
#define SIZE 10 //陣列大小
int arr[SIZE] = {0};
int re[SIZE] = {0};
int reverse(int arr[], int re[]);

int main(void)
{
	int i; //陣列索引 
	int tmp; //暫存
	int arr[SIZE] = {0,1,2,3,4,5,6,7,8,9};

	printf("orign: ");
	//將陣列內容在螢幕顯示出來
	for (i = 0; i < SIZE; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	printf("reverse: ");
	
	// reverse
	int re[SIZE] = {0};
	reverse(arr, re);
	for (i = 0; i < SIZE; ++i)
	{
		printf("%d ", re[i]);
	}


	return 0;
}

int reverse(int arr[], int re[]){
	int i = 0, j = SIZE - 1;
	for(i; i < SIZE; i++){
		re[i] = arr[j];
		j--;
	}
}
