#include <stdio.h>
#define SIZE 10 //�w�q �}�C �j�p 
#define ROW 4 //�w�q �x�}�� �j�p 
#define COL 5 //�w�q �x�}�C �j�p 
#define DEPTH 2 //�w�q �x�}�`�� �j�p 

int main(void)
{
	int i,j,k;
	
	int matrix_3d[ROW][COL][DEPTH] = {{{ 1, 2}, { 3, 4}, { 5, 6}, { 7, 8}, { 9,10}},
								      {{11,12}, {13,14}, {15,16}, {17,18}, {19,20}},
							          {{21,22}, {23,24}, {25,26}, {27,28}, {29,30}},
							          {{31,32}, {33,34}, {35,36}, {37,38}, {39,40}}};	
	
	for(i=0; i< ROW; i++) {
		for(j=0; j< COL; j++) {
			printf(" {");
			for(k=0;k<DEPTH;k++){
				printf("%3d", matrix_3d[i][j][k]);
			}
			printf("}");
		}
		printf("\n");
	}
	
	// �p��O�����} 
	int base = (int)&matrix_3d[0][0][0];
	int unit = (int)&matrix_3d[0][0][1] - (int)&matrix_3d[0][0][0];
	printf("\n%d + (((3 - 0) * %d + (3 - 0)) * %d + (1 - 0)) * %d = ", base, COL, DEPTH, unit);
	int address = base +  (((3 - 0) * COL + (3 - 0)) * DEPTH + (1 - 0)) * unit;
	printf("%d\n", address);
	
	// ��ڰO�����} 
	printf("m(3, 3, 1) �O�����}? %d", (int)&matrix_3d[3][3][1]);
	
	return 0;
}
