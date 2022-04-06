#include <stdio.h>
#define ROW 4 //定義矩陣行大小 
#define COL 4 //定義矩陣列大小

int main(void) {
	int i,j, tmp;
	//宣告二維陣列 
	int matrix[ROW][COL] = {{ 1, 2, 3, 4},
							{ 5, 6, 7, 8},
							{ 9,10,11,12},
							{13,14,15,16}};
	int matrix_transposed[ROW][COL] = {0};
	
	printf("Original:\n");
	//列印出矩陣內容 
	for(i=0; i< ROW; i++) {
		for(j=0; j< COL; j++) {
			printf("%4d", matrix[i][j]);
		}
		printf("\n");
	}	
	
	printf("\nTranspose: \n");
	
	// transpose
	int i_t = 0, j_t = 0;
	for(i = 0; i < ROW; i++) {
		for(j = 0; j < COL; j++) {
			i_t = j;
			j_t = i;
			matrix_transposed[i_t][j_t] = matrix[i][j];
		}
	}
	// printf_transpose
	for(i=0; i< ROW; i++) {
		for(j=0; j< COL; j++) {
			printf("%4d", matrix_transposed[i][j]);
		}
		printf("\n");
	}
	
	return 0;							
} 
