#include <stdio.h>
#define SIZE 10 //�}�C�j�p
int arr[SIZE] = {0};
int re[SIZE] = {0};
int reverse(int arr[], int re[]);

int main(void)
{
	int i; //�}�C���� 
	int tmp; //�Ȧs
	int arr[SIZE] = {0,1,2,3,4,5,6,7,8,9};

	printf("orign: ");
	//�N�}�C���e�b�ù���ܥX��
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
