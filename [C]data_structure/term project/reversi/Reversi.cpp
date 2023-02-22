#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <MMsystem.h>
#include <string.h>


#define SCREEN_HEIGHT 500 //�]�w�C���������� 
#define SCREEN_WIDTH 500 //�]�w�C�������e��
#define GRID_NUM 8 //�]�w�C����}�C���l�ƶq 
#define LEFT_MARGINE 30 //�]�w����� 
#define TOP_MARGINE 45 //�]�w�W��� 
#define INIT_SPEED  80 //�]�w��l�t�� 
#define PLAYONE_COLOR  BLACK //�]�w���a�@�C��
#define PLAYTWO_COLOR  WHITE //�]�w���a�G�C��
#define PLAYHARD 10;
#define PLAYTIME 15;
//�ŧi�Ѥl���� 
enum Chess {
	EMPTY, //�ť� 
	PLAY_ONE, //���a�@ 
	PLAY_TWO //���a�G 
};

enum Mode {
	PLAYER, //���a�Ҧ� player vs player
	AI_SECOND, //���a�@: player,  ���a�G: AI 
	AI_BOTH // AI vs AI 
};

//�ŧi�Ѥl��l 
struct Location{
	int row; 
	int col;
};

//�ŧi�������l��m���`�I���c 
struct Node {
	Location loc; //�ѽL��m 
	struct Node *next;	//���V�U�@�Ӹ`�I 
};

//�w�q���V�`�I���c�������ܼ� 
typedef struct Node *NodePointer;

int menu_AI();
void entername();
void menu();
void openWindow(); //open the game 
void closeGame(); //process the end of the game
void playGame(int field[][GRID_NUM]); //the logic of the game processing
void initChessboard(int field[][GRID_NUM]); //initialize the chessboard
Location* getChessDown(int field[][GRID_NUM], Location *focusPtr); //get the location of the chess
void setChess(int field[][GRID_NUM], Location chessLoc); //�]�w���l 
void drawChessboard(int field[][GRID_NUM]); //ø�s�C���ϰ� 
void printBoardState(int field[][GRID_NUM]); //�L�X�ѽL���A 
bool checkValidation(NodePointer list, Location loc); //�ˬd�Ӧ�m�O�_���X�k�����l��m 
NodePointer getValidatedLocs(int field[][GRID_NUM]); //��o�Ҧ��X�k�U�l���Ҧ��y�и`�I 
NodePointer addNode(NodePointer list, Location loc); //�s�W�X�k�U�l���y�и�T�`�I
void drawValidatedLocs(NodePointer list); //�аO�X�Ҧ��Ӫ��a�Ҧ��X�k���U�Ѧ�m 
void cleanValidatedLocs(NodePointer list); //�M�z�аO 
void doReverse(int field[][GRID_NUM], Location chessLoc); //�i��¥մ�½�� 
int reverse(int field[][GRID_NUM], Location chessLoc, bool checkOnly); //�p��Y�U�l�y�ЩҦ��i�H½�઺�Ѥl�ƶq�A check_only = true �u�i��p��Afalse �|�i��Ѥl��½�� 
void drawSquare(int row, int col, int color); //ø�s��� 
void drawFocus(int field[][GRID_NUM], Location focus); //ø�s�ؼФQ�r  
void cleanFocus(int field[][GRID_NUM], Location focus);//�M���Q�r 
void drawCircle(int row, int col, int color); //ø�s���I 
void showGameWinMsg(); //�C�������T��
void showInfo(); //��ܹC��������T 

Location* PLAYONE_AI(int field[][GRID_NUM], Location *focusPtr, NodePointer validated_locs);//��@�q�������޿� 

char key; //�ާ@���� 
int speed; //���ʳt�� 
int currentPlayer = PLAY_ONE; //�]�w���a 
int modeCount = 0; //����Ҧ����� 
int totalTime = 0; //�����C���ɶ� 
int playMode = PLAYER; // �]�w����Ҧ��A���a�Ҧ���AI�Ҧ� 
int play1Score = 0; //���a�@���� 
int play2Score = 0; //���a�G���� 
int stepCount = 0; //�^�X�p�ƾ� 
unsigned int AI_mode;
int bgmopen=0;
int play1time = PLAYTIME;
int play2time = PLAYTIME;

char player1name[50]="";
char player2name[50]="";
int namecount=0;
int name1count=0;
int name2count=0;

char score1Msg[10];
char score2Msg[10];

//------------------------------------------------------------------------for the hard mode
int expectnum[][8]= {
					{90, -60, 10, 10, 10, 10, -60, 90}, // 0
					{-60, -80, 5, 5, 5, 5, -80, -60}, // 1
					{10, 5,   1, 1, 1, 1, 5, 10}, // 2
					{10, 5,   1, 1, 1, 1, 5, 10},  // 3
					{10, 5,   1, 1, 1, 1, 5, 10}, //4
					{10, 5,   1, 1, 1, 1, 5, 10}, //5
					{-60, -80, 5, 5, 5, 5, -80, -60}, // 6
					{90, -60, 10, 10, 10, 10, -60, 90}};// 7



int main( )
{  	
	openWindow();
	while(TRUE){
	
		speed = INIT_SPEED;
	   	int field[GRID_NUM][GRID_NUM] = {0};

		playGame(field); //�i��C��
		if (key == 'q' || key == 'Q')
			closeGame(); //�p�G���a��J'q'���}�C��	
		else if (key == 's' || key == 'S')
			continue; //�p�G���a��J's' �~��C�� 		    
	}
}

//�}�Ҵ�������
void openWindow(){
	initwindow(SCREEN_WIDTH + LEFT_MARGINE * 3, SCREEN_HEIGHT + TOP_MARGINE * 3, "Backgammon");
}

//�B�z�C�������޿� 
void closeGame(){
	exit(0);
}

//�C���i���޿�
void playGame(int field[][GRID_NUM]){
	setbkcolor(BLACK);
	menu();
	entername();
   	setbkcolor(LIGHTGRAY);
	drawChessboard(field); //ø�s�C���ϰ� 
	
//	NodePointer validated_locs = NULL;
//	play1Score = 0, play2Score = 0;
//	stepCount = 0;

 	totalTime =0;// ------------------------------------------------restart the timer
 	NodePointer validated_locs = NULL;
 	play1Score = 0, play2Score = 0;
 	stepCount = 0;
 	play1time=PLAYTIME;
 	play2time=PLAYTIME;//-------------------------------------------end restarting timer
	
	initChessboard(field); //��l�ƴѽL���A 
   	printBoardState(field); //�L�X�ѽL���A�A�Ω�debug�ϥ� 
   	
   	validated_locs = getValidatedLocs(field); //�p��Ҧ��X�k�y��  
   	drawValidatedLocs(validated_locs); //�b�ѽL�Wø�s�o�^�X�X�k���y�� 
	   	
	Location focus = {0, 0};
	Location* chessLocPtr;
	key = 0;
	int endPoint = 0;
	
	while(true){
		delay(speed); //�M�w�C�^�X�U�ѳt�� 
		showInfo(); //��ܮɶ��M���Ƹ�T
		
		if(playMode == PLAYER){
			chessLocPtr = getChessDown(field, &focus);
		}else if(playMode == AI_SECOND){
			if(currentPlayer == PLAY_ONE)
				chessLocPtr = getChessDown(field, &focus);
			else
				chessLocPtr = PLAYONE_AI(field, &focus, validated_locs);			
		}
		else { // playMode == AI_BOTH
			getChessDown(field, &focus);
			chessLocPtr = PLAYONE_AI(field, &focus, validated_locs);
		}
		
		if(chessLocPtr == NULL){
			//�u����J�j�p�g��a, q �M s�A�t�Τ~�������ñN��J���G�ߨ�~�h���ݳB�z 
			if (key == 'q' || key == 'Q' || key == 's' || key == 'S'){
				int p;//---------------------------- refreshing player1name and player2name
				for(p=0;p<50;++p){
					namecount = 0;
					name1count = 0;
					name2count = 0;
					player1name[p]=NULL;
					player2name[p]=NULL;
				}
				return;
			}//--------------------------------------------------------------end refreshing
								
			else if (key == 'a' || key == 'A'){ 
				//�M�w�O�_���ܼҦ� �A�D�n�����a�Ҧ��M�q���ޱ���AI�Ҧ� 
				modeCount++;
				playMode = modeCount % 3;
				key = 0;
			}
			
			if (endPoint == 0)
				continue;
		}
		
		//���a�u��U�b�X�k��m 
		if(chessLocPtr != NULL && checkValidation(validated_locs, *chessLocPtr) == false)
			continue;
		

		cleanValidatedLocs(validated_locs); //�M�z�X�k��m�аO 
		if(chessLocPtr != NULL)
			setChess(field, *chessLocPtr); //�p�G���a���Uspace�A�N�b�ؼФQ�r�y��ø�s�Ѥl�A�ç��ܴѽL���A 
 
 		//�p�G���O�ɥ��I�A�i��Y�l�P�_�A��½��Ѥl 
		if(endPoint == 0)
			doReverse(field, *chessLocPtr);
		
		if(currentPlayer == PLAY_ONE){
			currentPlayer = PLAY_TWO;
		}else{
			currentPlayer = PLAY_ONE;
		}
		
		printBoardState(field);
		
		// ���o�U�@�^�X���X�k��m 
		validated_locs = getValidatedLocs(field);
		//�p�G�Ӧ^�X�L�k��o�X�k���U�l��m�A�ɥ��I+1 
		if(validated_locs == NULL) endPoint++;
		else endPoint = 0;
		
		//�s���^�X���L�k��o�X�k�y�СA�Ϊ̤w�g�S���i�H�U�l����m�A�C������ 
		if(endPoint == 2 || (play1Score + play2Score) == GRID_NUM * GRID_NUM){ //�P�_�O�_�ŦX�C����������A 
			showGameWinMsg(); //��ܹC�������T���A�õ��ݪ��a��J�ﶵ
			return;
		}
		
		//ø�s�X�k�y�маO 
		drawValidatedLocs(validated_locs);
		printf("end point: %d\n", endPoint);
							
	}		
}

// ��l�ƴѽL���A 
void initChessboard(int field[][GRID_NUM]){
	Location loc;
   	currentPlayer = PLAY_ONE;
   	loc.row = GRID_NUM/2 - 1, loc.col = GRID_NUM/2 - 1;
   	setChess(field, loc);
   	
   	currentPlayer = PLAY_TWO;
   	loc.row = GRID_NUM/2, loc.col = GRID_NUM/2 - 1;
   	setChess(field, loc);
   	
   	currentPlayer = PLAY_ONE;
   	loc.row = GRID_NUM/2, loc.col = GRID_NUM/2;
   	setChess(field, loc);
   	
   	currentPlayer = PLAY_TWO;
   	loc.row = GRID_NUM/2 - 1, loc.col = GRID_NUM/2;
   	setChess(field, loc);
   	currentPlayer = PLAY_ONE;	
}

//ø�s�C���ϰ�A�̾ڹC�����x�}�]�wø�s���� 
void drawChessboard(int field[][GRID_NUM]){
   	int row = 0, col = 0;
   	int startX = 0, startY = 0, endX = 0, endY = 0;
   	cleardevice(); //�M�z�ù��e�� 
   	int squareHeight = SCREEN_HEIGHT / GRID_NUM;
   	int squareWidth = SCREEN_WIDTH / GRID_NUM;
   	setlinestyle(SOLID_LINE, 0, 1); 
   	setcolor(DARKGRAY);
	for(row = 0; row <= GRID_NUM; row ++){
		startX = LEFT_MARGINE + 0 * squareWidth + 0;
		startY =  TOP_MARGINE + row * squareHeight;
		endX = startX + GRID_NUM * squareWidth;
		line(startX, startY, endX, startY);
	}
	
	for(col = 0; col <=  GRID_NUM; col++){
		startX = LEFT_MARGINE + col * squareWidth;
		startY =  TOP_MARGINE + 0 * squareHeight + 0;
		endY = startY + GRID_NUM * squareHeight;
		line(startX, startY, startX, endY);
	}
}

//�C�L�ѽL���A 
void printBoardState(int field[][GRID_NUM]){
	int i,j;
	
	for(i=0;i<GRID_NUM;i++){
		for(j=0;j<GRID_NUM;j++)
			printf("%d ", field[i][j]);
		printf("\n");	
	}
}

//���o���a���l��m
Location* getChessDown(int field[][GRID_NUM], Location *focusPtr){
		
	char keyPress;
	if(kbhit()) 
		keyPress = getch();
		
	if(keyPress == ' ' && field[focusPtr->row][focusPtr->col] == EMPTY){
		return focusPtr;
	}
		
	cleanFocus(field, *focusPtr);
	//decide focus moving direction	
	switch(keyPress){
		case KEY_RIGHT:
			if(focusPtr->col < GRID_NUM - 1)
				focusPtr->col = focusPtr->col + 1;
			break;			
		case KEY_LEFT:
			if(focusPtr->col > 0)
				focusPtr->col = focusPtr->col - 1;
			break;		
		case KEY_UP:
			if(focusPtr->row > 0)
				focusPtr->row = focusPtr->row - 1;
			break;				
		case KEY_DOWN:
			if(focusPtr->row < GRID_NUM - 1)
				focusPtr->row = focusPtr->row + 1;
			break;				
	}
	
	drawFocus(field, *focusPtr);
	//�u����J�j�p�g
	if (keyPress == 'q' || keyPress == 'Q' || keyPress == 's' || keyPress == 'S' || keyPress == 'a' || keyPress == 'A'){
		key = keyPress;
	}
	return NULL;
}

//�]�w���l
void setChess(int field[][GRID_NUM], Location chessLoc){
	
	if(currentPlayer == PLAY_ONE){
		drawSquare(chessLoc.row, chessLoc.col, PLAYONE_COLOR);
		play1Score++;
		if(field[chessLoc.row][chessLoc.col]==PLAY_TWO)
			play2Score--;
	}else{
		drawSquare(chessLoc.row, chessLoc.col, PLAYTWO_COLOR);
		play2Score++;
		if(field[chessLoc.row][chessLoc.col]==PLAY_ONE)
			play1Score--;		
	}
	field[chessLoc.row][chessLoc.col] = currentPlayer;
	stepCount++;
}

//�ˬd�Ӧ�m�O�_���X�k�����l��m 
bool checkValidation(NodePointer list, Location loc){
	
	while(list != NULL){
		if(list->loc.row == loc.row && list->loc.col == loc.col)
			return true;
		list = list -> next;	
	}
	return false;
}

//��o�Ҧ��X�k�U�l���Ҧ��y�и`�I 
NodePointer getValidatedLocs(int field[][GRID_NUM]){
	int row, col;
	NodePointer reversible_list = NULL;
	Location checkLoc;
	for(row=0; row < GRID_NUM; row++){
		for(col=0; col < GRID_NUM; col++){
			if(field[row][col] != EMPTY)
				continue;
			checkLoc.row = row, checkLoc.col = col;
			if(reverse(field, checkLoc, true) > 0){
				reversible_list = addNode(reversible_list, checkLoc);
			}		
		}
	}
	return reversible_list;
}

NodePointer addNode(NodePointer list, Location loc){
	NodePointer tail = NULL;
	NodePointer newNode = (NodePointer) malloc(sizeof(Node)); //��l�Ƥ@�ӷs�`�I 
	newNode -> loc = loc;
	newNode -> next = NULL;	
	if(list == NULL)
		return newNode;
	else{
		//�M���C������ 
		tail = list;
		while(tail -> next != NULL){
			tail = tail -> next;
		}
		tail -> next = newNode; //�N���ڸ`�I�s����s�`�I 
		return list;
	}
}

//�аO�X�Ҧ��Ӫ��a�Ҧ��X�k���U�Ѧ�m 
void drawValidatedLocs(NodePointer list){
	
	if (list==NULL){
		printf("validated location do not exist!!\n");
		return;
	}

	printf("validated location: ");
	while(list != NULL){
		printf("(%d, %d) ",  list -> loc.row, list -> loc.col);		
		if(currentPlayer == PLAY_ONE)
			drawCircle(list -> loc.row, list -> loc.col, PLAYONE_COLOR);
		else
			drawCircle(list -> loc.row, list -> loc.col, PLAYTWO_COLOR);
		
		list = list -> next;
	}
	printf("\n");
}

//�M�z�аO 
void cleanValidatedLocs(NodePointer list){
	while(list != NULL){
		drawCircle(list -> loc.row, list -> loc.col, LIGHTGRAY);
		list = list -> next;
	}
	printf("\n");
}

//�i��¥մ�½�� 
void doReverse(int field[][GRID_NUM], Location chessLoc){
	reverse(field, chessLoc, false);
}

int reverse(int field[][GRID_NUM], Location chessLoc, bool checkOnly){
 	int dirSize = 8;
 	int rowDir[] = {-1, -1, -1,  0, 0,  1, 1, 1};
 	int colDir[] = {-1,  0,  1, -1, 1, -1, 0, 1};
 	int i, rowNext, colNext;
 	int totalReversed = 0;
 	Location loc;
 
 	for(i = 0; i<dirSize; i++){
  		rowNext = chessLoc.row;
  		colNext = chessLoc.col;
  		int reverseCount = 0, count = 0;
  		while(true){
   			rowNext += rowDir[i];
   			colNext += colDir[i];  
   			if(field[rowNext][colNext] == EMPTY || rowNext < 0 || colNext < 0 || rowNext > GRID_NUM-1 || colNext > GRID_NUM-1){
    			break;
   			} 
   			
			else if(field[rowNext][colNext] != currentPlayer) count++;
   			
   			else if(field[rowNext][colNext] == currentPlayer){
    			reverseCount = count;
    			break;
   			} 
  		}
  
  		if(reverseCount > 0 && checkOnly == false){
   			int j;
   			rowNext = chessLoc.row;
   			colNext = chessLoc.col;
   			for(j = 0; j < reverseCount; j++){
    			rowNext += rowDir[i];
    			colNext += colDir[i];
    			loc.row = rowNext;
    			loc.col = colNext;
    			setChess(field, loc);
   			}
  		}
  
  		totalReversed += reverseCount; 
 	}
 	return totalReversed;
}

//ø�s�ؼФQ�r
void drawFocus(int field[][GRID_NUM], Location focus){
	int focusX = 0, focusY = 0;
	int squareHeight = SCREEN_HEIGHT / GRID_NUM;
   	int squareWidth = SCREEN_WIDTH / GRID_NUM;
   	focusX = LEFT_MARGINE + focus.col * squareWidth + squareWidth / 2;
   	focusY =  TOP_MARGINE + focus.row * squareHeight + squareHeight / 2;
   	setlinestyle(SOLID_LINE, 0, 1); 
   	setcolor(YELLOW);
   	line(focusX -5, focusY, focusX + 5, focusY);
   	line(focusX, focusY - 5, focusX, focusY + 5);
}

//�M���ؼФQ�r
void cleanFocus(int field[][GRID_NUM], Location focus){
	if(field[focus.row][focus.col] == PLAY_ONE)
		setcolor(PLAYONE_COLOR);
	else if(field[focus.row][focus.col] == PLAY_TWO)
		setcolor(PLAYTWO_COLOR);	
	else
		setcolor(LIGHTGRAY);
			
	int focusX = 0, focusY = 0;
	int squareHeight = SCREEN_HEIGHT / GRID_NUM;
   	int squareWidth = SCREEN_WIDTH / GRID_NUM;
   	focusX = LEFT_MARGINE + focus.col * squareWidth + squareWidth / 2;
   	focusY =  TOP_MARGINE + focus.row * squareHeight + squareHeight / 2;
   	setlinestyle(SOLID_LINE, 0, 1); 
   	
   	line(focusX -5, focusY, focusX + 5, focusY);
   	line(focusX, focusY - 5, focusX, focusY + 5);
}

//ø�s���
void drawSquare(int row, int col, int color){
 	int squareHeight = SCREEN_HEIGHT / GRID_NUM;
    int SquareWidth = SCREEN_WIDTH / GRID_NUM;
 	int left = 0, right = 0, bottom = 0, top = 0;
 	left = LEFT_MARGINE + col * SquareWidth + 3;
    top =  TOP_MARGINE + row * squareHeight + 3;
 	right = left + SquareWidth - 3;
 	bottom = top + squareHeight - 3;
 	int lr_center = (left + right)/2;
 	int td_center = (top + bottom)/2;

 	int r = 20;    
    setcolor(color);
 	setfillstyle(SOLID_FILL,color); 
 	circle(lr_center,td_center,r); 
 	floodfill(lr_center,td_center,color);
}

//ø�s���I 
void drawCircle(int row, int col, int color){
	int squareHeight = SCREEN_HEIGHT / GRID_NUM;
   	int SquareWidth = SCREEN_WIDTH / GRID_NUM;
	int left = 0, right = 0, bottom = 0, top = 0;
	left = LEFT_MARGINE + col * SquareWidth + 3;
   	top =  TOP_MARGINE + row * squareHeight + 3;
	right = left + SquareWidth - 3;
	bottom = top + squareHeight - 3;
	int lr_center = (left + right)/2;
	int td_center = (top + bottom)/2;

	int r = 10;   	
   	setcolor(color);
	//	setfillstyle(SOLID_FILL,color); //�]�wø�s���󪺬���ߩM�C�� 
	circle(lr_center,td_center,r);
}

//�C�������T��
void showGameWinMsg(){
   	cleardevice(); //�M�z�Ҧ��ù���ơA�p�G�Ʊ�u��ܰT���ɡA�������� 
   	if(play1time<=0||play2time<=0){
    	PlaySound("win.wav",NULL,SND_FILENAME| SND_ASYNC|SND_LOOP);
     	bgmopen=0;
    }else{
     	PlaySound("win.wav",NULL,SND_FILENAME| SND_ASYNC|SND_LOOP);
     	bgmopen=0;
    }
    
    
	int i = 0;
	char msg[20] = "";
	char msg1[20] = "";
	char scoree[10]="Score : ";
	if(play1time<=0){
  		strcat(msg, "  Player Two Win");
  		PlaySound("win.wav",NULL,SND_FILENAME| SND_ASYNC|SND_LOOP);
  		
     	bgmopen=0;
 	}else if(play2time<=0){
  		strcat(msg, "  Player One Win");
  		PlaySound("win.wav",NULL,SND_FILENAME| SND_ASYNC|SND_LOOP);
     	bgmopen=0;
 	}else{
 		if(play1Score == play2Score){
		strcat(msg1, "  End In A Draw");
		
	 	if(play1time<=0||play2time<=0){
     		PlaySound("opening.wav",NULL,SND_FILENAME| SND_ASYNC|SND_LOOP);
     		bgmopen=0;
    	}else{
     		PlaySound("opening.wav",NULL,SND_FILENAME| SND_ASYNC|SND_LOOP);
     		bgmopen=0;
    	}
    
		}else if(play1Score > play2Score){
			strcat(msg1, "  Player One Win");
			PlaySound("win.wav",NULL,SND_FILENAME| SND_ASYNC|SND_LOOP);
     		bgmopen=0;
		}else strcat(msg1, "  Player Two Win");
		
		if(playMode == AI_SECOND) {
			if(play1Score < play2Score){
				PlaySound("sad.wav",NULL,SND_FILENAME| SND_ASYNC|SND_LOOP);
     			bgmopen=0;
			}
		}
	}
	
	
			
	char msg2[40] = "   press [q] to quit or [s] to restart";
   	for(; ; i++){
	   	setcolor(i%14);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 5);
	   	outtextxy(0, SCREEN_HEIGHT / 2, msg1);
	   	
	   	setcolor(WHITE);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 2);
	   	outtextxy(20, SCREEN_HEIGHT / 2 + 50, msg2);
	   	
	   	delay(300);
	   	
	   	setcolor(BLACK);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 5);
	   	outtextxy(0, SCREEN_HEIGHT / 2, msg1);	   
		   	
	   	if(kbhit()) {
			key = getch();	
			if (key == 'q' || key == 'Q' || key == 's' || key == 'S') {
				int p;//-----------------------------refresh the player1name and player2name
				for(p=0;p<50;++p){
					namecount = 0;
					name1count = 0;
					name2count = 0;
					player1name[p]=NULL;
					player2name[p]=NULL;
				}//-----------------------------------------------------------end refreshing
				return; 				
			}
		}
		
		sprintf(score1Msg, "%3d", play1Score);
		sprintf(score2Msg, "%3d", play2Score);
		setcolor(BLACK); //�]�w��r�C�� 
   		settextstyle(COMPLEX_FONT, HORIZ_DIR , 1);
		 //�]�w�r���A�����Ϋ����M�r���j�p 
		 
		int left = 5, top = 20;
		left = LEFT_MARGINE * 4 + GRID_NUM * SCREEN_WIDTH / GRID_NUM / 2;
		top = 20;
		outtextxy(left -90, 20, scoree);
		setfillstyle(SOLID_FILL,PLAYONE_COLOR);
		bar(left, top, left + 20, top + 20);
		outtextxy(left + 25, 20, score1Msg);
	
		left = LEFT_MARGINE * 4 + GRID_NUM * SCREEN_WIDTH / GRID_NUM / 2 + 100;
		setfillstyle(SOLID_FILL,PLAYTWO_COLOR);
		bar(left, top, left + 20, top + 20);	      	
		outtextxy(left + 25, 20, score2Msg);
	}	
}
void entername(){
 	if(playMode == AI_BOTH){
  		return;
 	}
 	char msg2[40] = "Press space to confirm";
 	char msg3[40] ="Enter Player";int i;
 	char msg4[40] ="Enter Player2 name:";
 	char msg[20]="";
 	cleardevice();
 	if(playMode == PLAYER||playMode==AI_SECOND){
  		strcat(msg3, "1 name:");
 	}
 
	for(;;i++){
  		setcolor(i%13+1);
    	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 5);
    	outtextxy(0, SCREEN_HEIGHT / 2, msg);
  		setcolor(WHITE);
  		settextstyle(TRIPLEX_FONT, HORIZ_DIR , 2);
  		outtextxy(20, SCREEN_HEIGHT / 2 + 50, msg3);
  		setcolor(WHITE);
  		settextstyle(TRIPLEX_FONT, HORIZ_DIR , 2);
  		outtextxy(20, SCREEN_HEIGHT / 2 + 100, msg2);
  		delay(200);
  	
  		setcolor(BLACK);
    	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 5);
    	outtextxy(0, SCREEN_HEIGHT / 2, msg);
    
		// name
  		if(kbhit()) {
   			key = getch();
   			if (key == ' ') {
    			break;     
   			}else if((key >= 'A'&& key<='Z')||(key >= 'a'&& key<='z'||key>='0'&&key<='9')){
    			namecount=0;
    			while(1){
     				if(msg3[namecount]!=NULL){
     					namecount++;
      					continue;
     				}
     				break;
    			}
    			while(namecount>19){
     				msg3[namecount-1]=NULL;
     				namecount--;
    			}
    			if(playMode == AI_SECOND){
     				strcat(msg3,player1name);
    			}else if(playMode == PLAYER){
     				strcat(msg3,player1name);
    			}
    
    			namecount=0;
    			while(1){
     				if(msg3[namecount]!=NULL){
      					namecount++;
      					continue;
     				}
     				break;// ignoring enter player1 name.....blablabla
    			}
    
    			msg3[namecount]=key;//after ignoring, next input...
    			
     			player1name[name1count]=key;
     			name1count++;
     			printf("%s!\n",player1name);
    			
    
    
 	   		}else if(key=='\b'){// backspace
    			namecount=0;
   	 			while(1){
     				if(msg3[namecount]!=NULL){
      					namecount++;
      					continue;
     				}
     				break;
    			}
    			while(namecount>19){
     				msg3[namecount-1]=NULL;
     				namecount--;
    			}
    			
     			player1name[name1count-1]=NULL;
     			if(name1count>0){
      				name1count--;
     			}
     			strcat(msg3,player1name);
    			printf("%s!\n",player1name);
    			
    			strcat(msg3,"   ");
   			}
  		}
	}
	
 	for(;;i++){//---------------------------------------------------------enter player2name
  	//printf("NUMBER2");
  		if(playMode != PLAYER){
      		return;
    	}
  		setcolor(i%13+1);
     	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 5);
     	outtextxy(0, SCREEN_HEIGHT / 2, msg);
  		setcolor(WHITE);
  		settextstyle(TRIPLEX_FONT, HORIZ_DIR , 2);
  		outtextxy(20, SCREEN_HEIGHT / 2 + 75, msg4);
  		delay(200);
  		setcolor(BLACK);
     	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 5);
     	outtextxy(0, SCREEN_HEIGHT / 2, msg);
     
  		if(kbhit()) {
   			key = getch();
   			if (key == ' ') {
    			return;     
   			}else if((key >= 'A'&& key<='Z')||(key >= 'a'&& key<='z'||key>='0'&&key<='9')){
    			namecount=0;
    			while(1){
     				if(msg4[namecount]!=NULL){
      					namecount++;
      					continue;
     				}
     				break;
    			}
    			while(namecount>19){
     				msg4[namecount-1]=NULL;
     				namecount--;
    			}
    			strcat(msg4,player2name);
    			namecount=0;
    			while(1){
     				if(msg4[namecount]!=NULL){
      					namecount++;
      					continue;
     				}
     				break;
    			}
    
    			msg4[namecount]=key;
    
    			if(playMode == PLAYER){
     				player2name[name2count]=key;
     				name2count++;
    			}
    			printf("%s!\n",player2name);
    
   			}else if(key=='\b'){
    			namecount=0;
    			while(1){
     				if(msg4[namecount]!=NULL){
      					namecount++;
      					continue;
     				}
     				break;
    			}
    			while(namecount>19){
     				msg4[namecount-1]=NULL;
     				namecount--;
    			}
    			if(playMode == PLAYER){
     				player2name[name2count-1]=NULL;
     				if(name2count>0){
      					name2count--;
    	 			}
    			}
    			strcat(msg4,player2name);
    			printf("%s!\n",player2name);
    			strcat(msg4,"   "); 
   			}
  		}
 	}
}
//��ܹC��������T
void showInfo(){
	totalTime += speed;
	char timeMsg[45] = " Time:";
	char modeMsg[20] = "";
	char optMsg1[50] = "press [q] to quit, [s] to restart";
	//char play1RoundMsg[20] = "player1name";
	//char play2RoundMsg[20] = "player2name";	
	char stepCountMsg[10] = "STEP:";
	
	char time[10];
	char step[10];
	
	int left, top;
	sprintf(time, "%5d", totalTime/1000);
	strcat(timeMsg, time);
	strcat(timeMsg, " sec.");
	
	sprintf(score1Msg, "%3d", play1Score);
	sprintf(score2Msg, "%3d", play2Score);
	sprintf(step, "%3d", stepCount);
	strcat(stepCountMsg, step);
	
	setcolor(WHITE); //�]�w��r�C�� 
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1); //�]�w�r���A�����Ϋ����M�r���j�p 
   	outtextxy(0, 0, timeMsg); //�̾ڧ��п�X��r��ù�
   	if (playMode == PLAYER){
   		if(currentPlayer == PLAY_ONE){
   			setcolor(LIGHTGRAY);
   			outtextxy(30, 20, player2name);
   			setcolor(WHITE);
   			outtextxy(30, 20, player1name);
			setfillstyle(SOLID_FILL,PLAYONE_COLOR);  	  
		}
		else
		{
			setcolor(LIGHTGRAY);
   			outtextxy(30, 20, player1name);
   			setcolor(WHITE);
			outtextxy(30, 20, player2name); 
			setfillstyle(SOLID_FILL,PLAYTWO_COLOR);  
		}
	}
   	if (playMode == AI_SECOND){
   		if(currentPlayer == PLAY_ONE){
   			setcolor(LIGHTGRAY);
   			outtextxy(30, 20, "AI");
   			setcolor(WHITE);
   			outtextxy(30, 20, player1name);
			setfillstyle(SOLID_FILL,PLAYONE_COLOR);  	  
		}
		else
		{
			setcolor(LIGHTGRAY);
   			outtextxy(30, 20, player1name);
   			setcolor(WHITE);
			outtextxy(30, 20, "AI"); 
			setfillstyle(SOLID_FILL,PLAYTWO_COLOR);  
		}
	}
	
	
	
	left = 5, top = 20;
   	bar(left , top, left + 20, top + 20);		
	   		
   	if(playMode == PLAYER){
   		strcat(modeMsg, "Player Mode      ");
   				
	}else if(playMode == AI_SECOND){
   		strcat(modeMsg, "P, P2 AI");    		
	}else
		strcat(modeMsg, "P1, P2 AI both   ");

   	setcolor(BLACK);
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1);
   	outtextxy(SCREEN_WIDTH - LEFT_MARGINE * 4, 0, modeMsg);
	
	setcolor(WHITE); //�]�w��r�C��
	left = LEFT_MARGINE * 2 + GRID_NUM * SCREEN_WIDTH / GRID_NUM / 3;
	top = 20;	      	
	outtextxy(left + 25, 20, stepCountMsg);	
	
	left = LEFT_MARGINE * 4 + GRID_NUM * SCREEN_WIDTH / GRID_NUM / 2;
	top = 20;
	setfillstyle(SOLID_FILL,PLAYONE_COLOR);
	bar(left, top, left + 20, top + 20);
	outtextxy(left + 25, 20, score1Msg);
	
	left = LEFT_MARGINE * 4 + GRID_NUM * SCREEN_WIDTH / GRID_NUM / 2 + 100;
	setfillstyle(SOLID_FILL,PLAYTWO_COLOR);
	bar(left, top, left + 20, top + 20);	      	
	outtextxy(left + 25, 20, score2Msg);
   	
   	setcolor(BLACK);
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1);
   	outtextxy(0, TOP_MARGINE + (GRID_NUM) * SCREEN_HEIGHT / GRID_NUM, optMsg1);
}

void menu(){
    cleardevice();
    
    if(bgmopen!=1){
     	PlaySound("opening.wav",NULL,SND_FILENAME| SND_ASYNC|SND_LOOP);
     	bgmopen=1;
    }
     
    playMode = PLAYER;
    modeCount=0;
 	int i = 0;
 	char msg1[20] = "Reversi";
 	
 	char msg2[40] = "Choose mode:";
 	char msg21[40] = "Player vs Player";
 	char msg22[40] = "Player vs AI";
 	char msg23[40] = "Ai vs Ai";
    
	for(; ; i++){
     	setcolor(WHITE);
     	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 7);
     	outtextxy(120, SCREEN_HEIGHT / 2-100, msg1);
     
     	setcolor(WHITE);
     	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 2);
     	outtextxy(20, SCREEN_HEIGHT / 2 + 30, msg2);
     	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 4);
     
     	outtextxy(100, SCREEN_HEIGHT / 2 + 70, msg21);
     	outtextxy(100, SCREEN_HEIGHT / 2 + 110, msg22);
     	outtextxy(100, SCREEN_HEIGHT / 2 + 150, msg23);
     	setcolor(i%10);
     	if(modeCount==0){
    		outtextxy(100, SCREEN_HEIGHT / 2 + 70, msg21);
     	}else if(modeCount==1){
    		outtextxy(100, SCREEN_HEIGHT / 2 + 110, msg22);
     	} else{
      		outtextxy(100, SCREEN_HEIGHT / 2 + 150, msg23);
     	}
     
     	setcolor(WHITE);
     	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 2);
     	outtextxy(20, SCREEN_HEIGHT / 2 + 230, "Press space to choose mode       ");
     	outtextxy(20, SCREEN_HEIGHT / 2 + 250, "Press backspace to close");
     
     	delay(200);
     
     	setcolor(BLACK);
     	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 5);
     	outtextxy(0, SCREEN_HEIGHT / 2, msg1);
      
      
     	if(kbhit()) {
   			key = getch();
   			if (key == ' '||key =='\b') {
    			if(key=='\b'){
     				closeGame();
    			}
    			playMode = modeCount%3;
    
    			if(!menu_AI()){
     				continue;
    			}
    			return;     
   			}else{
    			switch(key){
    	 			case KEY_UP:
      					if(modeCount>=0&&modeCount<=2){
       						modeCount --;
       						if(modeCount ==-1){
        						modeCount =0;
       						}
      					}
      
      					printf("%d",modeCount);
      					break;
     				case KEY_DOWN: 
       					if(modeCount>=0&&modeCount<=2){
       						modeCount ++;
       						if(modeCount ==3){
       	 						modeCount =2;
       						}
      					}
       					printf("%d",modeCount);
       					break;
     			}
   			}
  		}
 	} 
}

int menu_AI(){
	if(modeCount==0){
		return 1;
	}
	char msg2[]="Difficulty:          ";
	char msg3[]="Press space to choose difficulty";
	char msg4[]="Press backspace to back      ";
	char msg5[]="Easy                           ";
	char msg6[]="                              ";
	char msg7[]="Hard                           ";
	char msg8[]="Easy";
	char msg9[]="Hard";
	
	int i;
	setcolor(WHITE);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 2);
	outtextxy(20, SCREEN_HEIGHT / 2 + 30, msg2);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 2);
	outtextxy(20, SCREEN_HEIGHT / 2 + 230, msg3);
	outtextxy(20, SCREEN_HEIGHT / 2 + 250, msg4);
	AI_mode=0;
	for(;;i++){
		setcolor(WHITE);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 4);
		outtextxy(100, SCREEN_HEIGHT / 2 + 70, msg5);
	   	outtextxy(100, SCREEN_HEIGHT / 2 + 110,msg6);
	   	outtextxy(100, SCREEN_HEIGHT / 2 + 150, msg7);
	   	outtextxy(100, SCREEN_HEIGHT / 2 + 190, msg6);
	   	setcolor(YELLOW);
	   	//delay(200);
	   	if(AI_mode%2==1){
			 outtextxy(100, SCREEN_HEIGHT / 2 + 70, msg8);
		   }else{
			 outtextxy(100, SCREEN_HEIGHT / 2 + 150, msg9);
		   }
	   delay(200);
	   if(kbhit()) {
			key = getch();
			if (key == ' '||key =='\b') {
				if(key == ' '){
					return 1;
				}else{
					return 0;
				}
								
			}else{
				switch(key){
					case KEY_UP:
						AI_mode++;
						//printf("%d",AI_mode%2);
						break;
					case KEY_DOWN:	
						 AI_mode--;
						 //printf("%d",AI_mode%2);
						 break;
					}
			}
		}
	}

	
	
}

Location* PLAYONE_AI(int field[][GRID_NUM],  Location *focusPtr, NodePointer validated_locs) {
  	Location tmp= {0, 0};
   	int maxx = 0; 
  	int max = 0;
  	int maxx_neg = 0;
   	int max_neg = -100;  
  
   	if(AI_mode%2==1) {
     	while(validated_locs != NULL) {
      		tmp.row = validated_locs->loc.row;
      		tmp.col = validated_locs->loc.col;
      
      		if(reverse(field, tmp, true) > maxx) {
         		maxx = reverse(field, tmp, true);
         		focusPtr->row = tmp.row; focusPtr->col = tmp.col;
       		}
  
      		validated_locs = validated_locs->next;
    	}
    
     	if(maxx == 0) {
       		return NULL;
     	}
    	
		return focusPtr;
 	}
 
  	//hard
   	while(validated_locs != NULL) {
      	tmp.row = validated_locs->loc.row;
      	tmp.col = validated_locs->loc.col;
  
     	// if possitive
     	if (expectnum[tmp.row][tmp.col] > max && reverse(field, tmp, true) > maxx) {
         	max = expectnum[tmp.row][tmp.col];
         	maxx = reverse(field, tmp, true);
         	focusPtr->row = tmp.row;
   			focusPtr->col = tmp.col; 
        
     	}else if(expectnum[tmp.row][tmp.col] < 0) {
         	if(expectnum[tmp.row][tmp.col] > max_neg && reverse(field, tmp, true) > maxx_neg) {
             	max_neg = expectnum[tmp.row][tmp.col];
          		maxx_neg = reverse(field, tmp, true);
       
          		if(max == 0) {
              		focusPtr->row = tmp.row;focusPtr->col = tmp.col;
          		}
         	}
     	}
   
     	validated_locs = validated_locs->next; 
   	}
    
	if(maxx == 0 && maxx_neg == 0) {
       return NULL;
    }
 
 	return focusPtr;
}
