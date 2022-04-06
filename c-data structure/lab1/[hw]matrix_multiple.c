#include <stdio.h>
#define ROW 4 //定義矩陣行大小 
#define COL 4 //定義矩陣列大小 


int main(void) {
	int i, j, k, sum;
	//宣告二維陣列 
	int m1[ROW][2] = {{ 1, 2},
					  { 3, 4},
					  { 5, 6},
					  { 7, 8}};
	int m2[2][COL] = {{ 9,10, 11,12},
					  {13,14,15,16}};
					  
	int matrix[ROW][COL] = {0};
	
	for(i=0; i< ROW; i++) {
		for(j=0; j< 2; j++) {
			printf("%4d", m1[i][j]);
		}
		printf("\t");
		if(i < 2){	
			for(j=0; j< COL; j++) {
				printf("%4d", m2[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n矩陣相乘結果：\n");

	// multiple
	for(i = 0; i < ROW; i++) {
		for(k = 0; k < ROW; k++){
			for(j = 0; j < 2; j++) {
				matrix[i][k] += m1[i][j] * m2[j][k];
			}
		}
	}
	
	// print_multiple
	for(i=0; i< ROW; i++) {
		for(j=0; j< COL; j++) {
			printf("%4d", matrix[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}
