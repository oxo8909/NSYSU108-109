#include <stdio.h>
#include <math.h>
#define SIZE 99 //陣列大小

void printArray(int array[]);
double sum(int array[]);
double mean(int array[]);
double stDev(int array[]);
int max(int array[]);
int min(int array[]);
int median(int array[]);
int mode(int array[]);

int main(void) {
	//宣告一個99個元素的整數陣列，數值範圍介於1~9之間
	int values[SIZE] = {6,7,8,9,8,7,8,9,8,9,
	                    7,8,9,5,9,8,7,8,7,8,
	                    6,7,8,9,3,9,8,7,8,7,
	                    7,8,9,8,9,8,9,7,8,9,
	                    6,7,8,7,8,7,9,8,9,2,
	                    7,8,9,8,9,8,9,7,5,3,
	                    5,6,7,2,5,3,9,4,6,4,
	                    7,8,9,6,8,7,8,9,7,8,
	                    7,4,4,2,5,3,8,7,5,6,
	                    4,5,6,1,6,5,7,8,7
	                   };
	printf("[values]\n");
	printArray(values);
	printf("\n***** Statistical Results *****\n");
	
	// print the answers
	printf("Sum = %d\n", (int)sum(values));
	printf("Mean = %lf\n", mean(values));
	printf("stDev = %lf\n", stDev(values));
	printf("Max = %d\n", max(values));
	printf("Min = %d\n", min(values));
	printf("Median = %d\n", median(values));
	printf("Mode = %d\n", mode(values));
	
	return 0;
}

//將陣列內容在螢幕顯示出來
void printArray(int array[]) {
	int i;
	for (i = 0; i < SIZE; ++i) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

// sum
double sum(int array[]){
	int i = 0;
	int sum = 0;
	for(i; i < SIZE; i++){
		sum += (double)array[i];
	}
	return sum;
}

// mean
double mean(int array[]){
	return (sum(array) / (double)SIZE);
}

// stDev
double stDev(int array[]){
	int i = 0;
	double u = 0, Sum = 0;
	u = mean(array);
	for(i; i < SIZE; i++){
		Sum += ((double)array[i] - u) * ((double)array[i] - u);
	}
	return sqrt(Sum / (double)SIZE);
}

// max
int max(int array[]){
	int i = 0, max = array[0];
	for(i; i < SIZE - 1; i++){
		if(array[i + 1] > max) max = array[i + 1];
	}
	return max;
}

// min
int min(int array[]){
	int i = 0, min = array[0];
	for(i; i < SIZE - 1; i++){
		if(array[i + 1] < min) min = array[i + 1];
	}
	return min;
}

// median
int median(int array[]){
	int  i = 0, j = 0, box = 0;
	for(j; j < SIZE; j++){
		for(i = 0; i < SIZE - 1; i++){
			if(array[i + 1] < array[i]){
				box = array[i + 1];
				array[i + 1] = array[i];
				array[i] = box; 
			}
		}
	}
	int m = (SIZE / 2) + 1;
	return array[m];
}

// mode
int mode(int array[]){
	int count = 0, i = 0, j = 0, count_max = 0;
	int max_int = max(array);
	int min_int = min(array);
	int mode = 0;
	for(i = min_int; i <= max_int; i++){
		for(j = 0; j < SIZE; j++){
			if(array[j] == i) count++;
		}
		if(count > count_max){
			count_max = count;
			mode = i;
		}
		count = 0;
	}
	return mode;
}

