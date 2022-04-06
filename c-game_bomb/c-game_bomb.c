// ����game = 0, ���\game = 1
/************ �d�]�ɶ�_�a�p ************/
// 9: bomb 10:���� 
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> //---------------------> system(cls)

// �C�����O�j�p 
#define ROW 7
#define COLUMN 4
// �]�A��ت� 
#define BIGROW (ROW + 2) 
#define BIGCOLUMN (COLUMN + 2)
// �a�p���X�� 
#define BOMB 5

typedef struct table{
	int element; // ��l�N���� 
	int ifopen; // 1: �}�L�F �� ���ӭn�}�٨S�} 0: �٨S�}  2:�]���O���~�} 
}Table;

// function
void makeTable(int counter, Table [][BIGCOLUMN], int [], int [], int [], int []); // �C�����O 
int randomNumber(int range); // �H���ܼ� 
void setElement(Table [][BIGCOLUMN], int []); // �]�m�C�@�檺�ƭȡA�L�ᤣ�A�� 
void input(int [], int [], int []); // input
void correctInput(int [], int [], int []); // check if input is in the range of the table
void aroundElement(int row, int column, Table [][BIGCOLUMN], int []); // �P��8�� 
void aroundOpen(int row, int column, Table [][BIGCOLUMN], int []); // �}�Ү���s�a����l 



// main
int main(int game){
	/************ �ƫe�B�z ************/
	system("cls");
	Table table[BIGROW][BIGCOLUMN];
	int eight[8] = {0};	

	// �Ntable����reset 0
	int i = 0, j = 0;
	for(i; i < BIGROW; ++i){
		// column
		for(j = 0; j < BIGCOLUMN; ++j){
			table[i][j].element = 0;
			table[i][j].ifopen = 0;
		}
	}	
	
	/************ �C���}�l ************/ 
	/***** player input *****/
	int dig[1] = {0}, rowInput[1] = {0}, columnInput[1] = {0}, breaker = 1;
	int counter = 0; // ���F�h�֦� 
	makeTable(counter, table, rowInput, columnInput, dig, eight);
	
	input(dig, rowInput, columnInput);
	
	for(counter = 1; breaker == 1; ){
		/***** react to input *****/
		switch(dig[0]){
			// dig: 1: �}�� 2: ���O�� 3: �Ѱ��O�� 
			case 1:
				// condition1: is bomb
				if(table[rowInput[0]][columnInput[0]].element == 9){
					makeTable(counter, table, rowInput, columnInput, dig, eight);
					system("cls");
					printf("<<GAME OVER>>\n");// ----------------------->����100 
					sleep(5);
					return 0;
					breaker = 0; // ----------------------------->�C������ 
				}
				// condition2: not bomb
				else if(table[rowInput[0]][columnInput[0]].element != 9){
					table[rowInput[0]][columnInput[0]].ifopen == 1;
					makeTable(counter, table, rowInput, columnInput, dig, eight);
					
					counter++;
					/***** �C������ *****/
					// ���F�a�p�H�~�����}�F 
					i = 1; j = 1;
					int complete = 0;
					for(i; i <= ROW; ++i){
						for(j = 0; j <= COLUMN; ++j){
							if(table[i][j].ifopen == 1 || table[i][j].element == 9){
								++complete;
							}
						}
					} 
					if(complete == ROW * COLUMN){
						system("cls");
						printf("<<COMPLETE>>\n"); // -------------------->�[�� 
						sleep(5);
						return 1;
						breaker = 0; // --------------------------->�C������ 
					}else{
						input(dig, rowInput, columnInput);
					}
				}
				break;
			
			// ���O�� 
			case 2:
				makeTable(counter, table, rowInput, columnInput, dig, eight); 
				input(dig, rowInput, columnInput);
				break;
				
			// �Ѱ��O�� 
			case 3:
				makeTable(counter, table, rowInput, columnInput, dig, eight);
				input(dig, rowInput, columnInput);
				break;
			default:
				break;
		} // end switch 
	} // end for
} // end main

/************* function�� ************/

// �C�����O
void makeTable(int counter, Table table[][BIGCOLUMN], int row[], int column[], int dig[], int eight[]){
	system("cls");
	// �C���}�l
	int row_bomb = 0, column_bomb = 0;
/**********************************�٨Sinput�L***************************************************/	
	if(counter == 0){
		// �гy�a�p 
		int b = 1;
		for(b; b <= BOMB; ++b){
			row_bomb = randomNumber(ROW); 
			column_bomb = randomNumber(COLUMN);
			// �w�g�O�a�p
			if(table[row_bomb][column_bomb].element == 9){
				b -= 1;
			}else{ // �٤��O 
				table[row_bomb][column_bomb].element = 9;	
			}
		}
		
		// �������C�����O�]�m�ƭ� (!!���|�A��!!) 
		setElement(table, eight);
		
		// �L���O 
		// row
		int i = 0, j = 0, k = 0, h = 1;
		// search every element
		for(i; i < BIGROW; ++i){
			// column
			for(j = 0; j < BIGCOLUMN; ++j){
				// �L��t�����ܼƦr 
				if(i == 0){
					if(k != 0){
						if(j == COLUMN + 1){ // �k�䨺����� 
							table[i][j].element = 10; // 10�N����� 
						}else{
							printf("%3d", k);
							table[i][j].element = 10;	
						}
					}
					else if(k == 0){
						printf("   ");
						table[i][j].element = 10;
					}
					++k;
				}
				else if(j == 0){
					if(i == ROW + 1){ // �U��������� 
						table[i][j].element = 10;
					}else{
						printf("%3d", h);
						table[i][j].element = 10;
					}
					++h;
				}
				else if(i == ROW + 1 || j == COLUMN + 1){ // �k��+�U������� 
					table[i][j].element = 10;
				}
				// �����L��t�����ܼƦr
				// �H�W�L�����u�O��� && �����(10)��C�����O��_�� 
				else if(i!= ROW + 1 && j != COLUMN + 1){
					printf("  *");	
				}
			}
			printf("\n");
		} // end for
	} // end if
/*********************************�Ĥ@��input��*********************************************/	
	else if(counter == 1){
		int i = 0, j = 0, k = 0, h = 1;
		if(dig[0] == 1){ // �}���~�n!! 
			aroundOpen(row[0], column[0], table, eight);
		}
		
		for(i; i < ROW + 1; ++i){
			for(j = 0; j < COLUMN + 1; ++j){
				if(i == 0){ // �n�L���䪺1234�خ� 
					if(k == 0){
						printf("   ");
					}
					else{
						printf("%3d", k);
					}
					++k;
				}
				else if(j == 0){ // �]�O�n�L�خ� 
					printf("%3d", h);
					++h;
				}
				// �L���خؤF 
				
				// ��F�ڿ諸��l�F 
				else if(i == row[0] && j == column[0]){
					// �}�� 
					if(dig[0] == 1){
						table[row[0]][column[0]].ifopen = 1; 
						printf("   ");
					}
					// �O�� 
					else if(dig[0] == 2){
						table[row[0]][column[0]].ifopen = 2; //�M�ݩ󰵰O����2 
						printf("  -");
					}
					//�Ѱ��O�� 
					else if(dig[0] == 3){
						table[row[0]][column[0]].ifopen = 0;// �ߤ@�|��ifopen�ܦ^0������ 
						printf("  *");
					}
				}
				// ���N�}�F�� 
				else if(table[i][j].ifopen == 1){
					if(table[i][j].element == 0){
						printf("   ");
					}else{
						printf("%3d", table[i][j].element);
					}
				}
				// not dig
				else if(table[i][j].ifopen == 2){
					printf("  -");
				}
				// �q�S�}�L�� 
				else{
					printf("  *");
				}
			}
			printf("\n");
		} // end for
	} // end else if
/********************************���᪺input************************************************/	
	// ���O�Ĥ@���}�F 
	else{
		int i = 0, j = 0, k = 0, h = 1;
		if(dig[0] == 1 && table[row[0]][column[0]].element == 0){ // �}��and���}���O0�~�n!! 
			aroundOpen(row[0], column[0], table, eight);
		}
		for(i; i < ROW + 1; ++i){
			for(j = 0; j < COLUMN + 1; ++j){
				if(i == 0){ // �~��L�خ� 
					if(k == 0){
						printf("   ");
					}
					else{
						printf("%3d", k);
					}
					++k;
				}
				else if(j == 0){
					printf("%3d", h);
					++h;
				} // �H�W�O�L�خ�
				 
				// ��F�ڿ諸��l�F 
				else if(i == row[0] && j == column[0]){
					// �}�� 
					if(dig[0] == 1){
						if(table[i][j].element == 0){
							table[row[0]][column[0]].ifopen = 1; 
							printf("   ");
						}else{
							table[row[0]][column[0]].ifopen = 1;
							printf("%3d", table[i][j].element);
						}
					}
					// �O�� 
					else if(dig[0] == 2){
						table[row[0]][column[0]].ifopen = 2;
						printf("  -");
					}
					//�Ѱ��O�� 
					else if(dig[0] == 3){
						table[row[0]][column[0]].ifopen = 0;// �ߤ@�|��ifopen�ܦ^0������ 
						printf("  *");
					}
				}
				// ���N�}�F�� 
				else if(table[i][j].ifopen == 1){
					if(table[i][j].element == 0){
						printf("   ");
					}else{
						printf("%3d", table[i][j].element);
					}
				}
				// not dig
				else if(table[i][j].ifopen == 2){
					printf("  -");
				}
				// �q�S�}�L�� 
				else if(table[i][j].element != 10){
					printf("  *");
				}
			}
			printf("\n");
		} // end for
	} // else
} // end function makeTable

// �H���ܼ� 1 ~ range
int randomNumber(int range){
	srand(time(NULL));
	return rand() % range + 1;
} // end function randomNumber

// �]�w�C��ƭȡA�q�n�N���ܤF!! 
void setElement(Table table[][BIGCOLUMN], int eight[]){
	int i = 1, j = 1, k = 0, nBomb = 0;
	
	// search every element
	for(i; i <= ROW; ++i){
		for(j = 1; j <= COLUMN; ++j){
			// �p�G���椣�Obomb 
			if(table[i][j].element != 9){
				aroundElement(i, j, table, eight); // ��������8�檺�ƭ� 
				// search every eight(eight �N�O�P��8���) 
				for(k = 0; k < 8; ++k){
					if(eight[k] == 9){
						++nBomb; // �Y�O���䦳�@��bomb�A�N++ 
					} // end if 
				} // end for
				if(nBomb == 0){ //����S��bomb 
					table[i][j].element = 0;
				}else{ // �X��bomb�A�ƭȴN�h�� 
					table[i][j].element = nBomb;
					nBomb = 0;	
				} // end if
			} // end outer if
		} // end for
	} // end search every element
} // end function setElement

// Input position
void input(int dig[], int row[], int column[]){
	// reset(debug)
	dig[0] = 1;
	row[0] = 1;
	column[0] = 1;  
	
	printf("1: �}�� 2: ���O�� 3: �Ѱ��O��\nEnter: ");
	scanf("%d", dig);
	correctInput(dig, row, column);
	
	printf("��J�y��");
	printf("\nrow: ");
	scanf("%d", row);
	correctInput(dig, row, column);
	
	printf("column: ");
	scanf("%d", column); 
	correctInput(dig, row, column);
} // end function input

// Check if input is in the range of the table
void correctInput(int dig[], int row[], int column[]){
		
	// condition1: dig is ^1 || ^2 || ^3
	if(dig[0] != 1 && dig[0] != 2 && dig[0] != 3){
		printf("<<�L�Ŀﶵ�A�Э��s��J>>\n\n");
		input(dig, row, column);
	}
	
	// condition2: row too large
	if(row[0] > ROW){
		printf("<<row �W�X�d��A�п�J�s�y��>>\n\n");
		input(dig, row, column);
	}
	
	// condition3: column too large
	if(column[0] > COLUMN){
		printf("<<column �W�X�d��A�п�J�s�y��>>\n\n");
		input(dig, row, column);
	}
} // end function correctInput

// �����Y��P��8�ƭ� 
void aroundElement(int row, int column, Table table[][BIGCOLUMN], int eight[]){
	eight[0] = table[row - 1][column - 1].element; // ���W 
	eight[1] = table[row - 1][column].element; // �W 
	eight[2] = table[row - 1][column + 1].element; // �k�W 
	eight[3] = table[row][column - 1].element; // �� 
	eight[4] = table[row][column + 1].element; // �k 
	eight[5] = table[row + 1][column - 1].element; // ���U 
	eight[6] = table[row + 1][column].element; // �U 
	eight[7] = table[row + 1][column + 1].element; // �k�U 
} // end function aroundElement

/*** �}�Ҫ��񪺮�l ***/
void aroundOpen(int row, int column, Table table[][BIGCOLUMN], int eight[]){
	aroundElement(row, column, table, eight);
	int k = 0;
	// search���䪺��l(eight)�A�q���W�}�l 
	for(k = 0; k <= 7; ++k){
		// �p�G���䪺��l���O��t(10) �B�p�G�O�O�����ܤ]���} 
		if((row > 0 && row < ROW + 1) && (column > 0 && column < COLUMN + 1) && table[row][column].ifopen != 2){
			if(eight[k] == 0){
				// �p�G�}���O0���� 
				// recursive 
					switch(k){
						// ���W 
						case 0:  
							if(table[row - 1][column - 1].ifopen == 1){
								break;
							}else{
								table[row - 1][column - 1].ifopen = 1; // �}�_�� 
								aroundOpen(row - 1, column - 1, table, eight); // �H���W���D���~��} 
								aroundElement(row, column, table, eight); // �]����~���s�s�FaroundOpen, eight�Q��L�F�A�ҥH���Ǥ@��eight 
								break;
							} 
							
						// �W 
						case 1:
							if(table[row - 1][column].ifopen == 1){
								break;
							}else{
								table[row - 1][column].ifopen = 1;
							    aroundOpen(row - 1, column, table, eight);
							    aroundElement(row, column, table, eight);
							    break;
							}
	
						// �k�W 
						case 2:
							if(table[row - 1][column + 1].ifopen == 1){
								break;
							}else{
								table[row - 1][column + 1].ifopen = 1;
							    aroundOpen(row - 1, column + 1, table, eight);
							    aroundElement(row, column, table, eight);
							    break;
							}
							
						// �� 
						case 3:
							if(table[row][column - 1].ifopen == 1){
								break;
							}else{
								table[row][column - 1].ifopen = 1;
							    aroundOpen(row, column - 1, table, eight);
							    aroundElement(row, column, table, eight);
							    break;
							}
							
						// �k 
						case 4:
							if(table[row][column + 1].ifopen == 1){
								break;
							}else{
								table[row][column + 1].ifopen = 1;
							    aroundOpen(row, column + 1, table, eight);
							    aroundElement(row, column, table, eight);
							    break;
							}
							
						// ���U 
						case 5:
							if(table[row + 1][column - 1].ifopen == 1){
								break;
							}else{
								table[row + 1][column - 1].ifopen = 1;
							    aroundOpen(row + 1, column - 1, table, eight);
							    aroundElement(row, column, table, eight);
							    break;
							}
							
						// �U 
						case 6:
							if(table[row + 1][column].ifopen == 1){
								break;
							}else{
								table[row + 1][column].ifopen = 1;
							    aroundOpen(row + 1, column, table, eight);
							    aroundElement(row, column, table, eight);
							    break;
							}
							
						// �k�U 
						case 7:
							if(table[row + 1][column + 1].ifopen == 1){
								break;
							}else{
								table[row + 1][column + 1].ifopen = 1;
							    aroundOpen(row + 1, column + 1, table, eight);
							    aroundElement(row, column, table, eight);
							    break;
							}
					} // end inner switch
				// end case 0
			}
			
			// is bomb
			else if(eight[k] == 9){
				// do nothing
			}
			
			// is �خ� 
			else if(eight[k] == 10){
				// do nothing
			}
			
			else{
				// ���䪺�O�Ʀr�N�@�˥��}�A���즹����
				switch(k){
					// ���W 
					case 0:  
						table[row - 1][column - 1].ifopen = 1; // �}�_�� 
						break;
					// �W 
					case 1:
						table[row - 1][column].ifopen = 1;
						break;
					// �k�W 
					case 2:
						table[row - 1][column + 1].ifopen = 1;
						break;
					// �� 
					case 3:
						table[row][column - 1].ifopen = 1;
						break;
					// �k 
					case 4:
						table[row][column + 1].ifopen = 1;
						break;
					// ���U 
					case 5:
						table[row + 1][column - 1].ifopen = 1;
						break;
					// �U 
					case 6:
						table[row + 1][column].ifopen = 1;
						break;
					// �k�U 
					case 7:
						table[row + 1][column + 1].ifopen = 1;
						break;
				} // end switch
			} // end else
		} // end if
	} // end for
} // end function aroundOpen
