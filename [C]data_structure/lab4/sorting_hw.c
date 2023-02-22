#include <stdio.h>
#include <time.h>
#define SIZE 5 //陣列大小
#define	MAX 100 //亂數範圍

void genRandomIntArry(int arr[], int sizem, int max);
void printArray(int arr[], int size);
void mergeSort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);
void quickSort(int arr[], int left, int right);

int main(void){
	
    int arr[SIZE] = {0};
    genRandomIntArry(arr, SIZE, MAX);
    

	printf("before sorting\n");
	printArray(arr, SIZE);
	
	// revise this sorting function
	// hw2
//	mergeSort(arr, 0, SIZE-1);
	
	// hw3
	quickSort(arr, 0, SIZE-1);
	
	printf("after sorting\n");
	printArray(arr, SIZE);
	
	return 0;
}


void genRandomIntArry(int arr[], int size, int max){
	int i; //陣列索引
	srand((unsigned)time(NULL)); //產生亂數種子

	//賦予值給陣列
	for(i =0; i< size; i++)
	{
		arr[i] = rand() % max + 1; //指定0~MAX範圍的亂數
	}	
}

void printArray(int arr[], int size){
	int i;
	for (i = 0; i < size; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");	
}

// hw2
void mergeSort(int arr[], int left, int right){
	//please implement the assigned sorting algorithm here
	if(left < right){
		int mid = (left + right) / 2;
		mergeSort(arr, left, mid);
		mergeSort(arr, mid+1, right);
		merge(arr, left, mid, right);
	}
}

void merge(int arr[], int left, int mid, int right){
	// 分別存進左右array 
	// input arr[left] ~ arr[mid] to left
	int len1 = (mid - left + 1) + 1;// 加尾巴 
	int arrLeft[len1];
	int i;
	for(i=0; i<len1-1; ++i){
		arrLeft[i] = arr[left+i];
	}
	arrLeft[len1-1] = 9999;// 超大尾巴
	
	// input arr[mid+1] ~ arr[right] to right
	int len2 = (right - (mid + 1) + 1) + 1;
	int arrRight[len2];
	
	for(i=0; i<len2-1; ++i){
		arrRight[i] = arr[(mid+1)+i];
	}
	arrRight[len2-1] = 9999;// 超大尾巴 
	
	// 兩array的第一個數字比大小後放進原array 
	int indexLeft=0, indexRight=0;
	for(i=left; i<=right; i++){
		if(arrLeft[indexLeft] <= arrRight[indexRight]){
			arr[i] = arrLeft[indexLeft];
			indexLeft++;
		}
		else{
			arr[i] = arrRight[indexRight];
			indexRight++;
		}
	}
}

// hw3
void quickSort(int arr[], int left, int right){
	//please implement the assigned sorting algorithm here
	int pivot, i, j, temp;
	if(left < right){
		i = left;
		j = right + 1;
		pivot = arr[left];
		do{
			do i++; while(arr[i] < pivot);
			do j--; while(arr[j] > pivot);
			if(i < j){
				// swap arr[i] and arr[j]
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		} while(i < j);
		// swap arr[left] and arr[j]
		temp = arr[left];
		arr[left] = arr[j];
		arr[j] = temp;
		
		quickSort(arr, left, j-1);
		quickSort(arr, j+1, right);
	}
}

