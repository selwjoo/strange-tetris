#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h> 

clock_t startDropT, endT, startGroundT;
int x = 8, y = 1;
RECT blockSize;
int blockForm;
int blockRotation = 0;
int key;
int signal = 0;
int cnt = 0;
int level = 0;
time_t lastLevelUpTime = 0;

int block[12][5][5][5] = {
	{ // F모양 블럭
		{
			{0,0,0,0,0},
			{0,0,1,1,0},
			{0,1,1,0,0},
			{0,0,1,0,0},
			{0,0,0,0,0}
		},
		{
			{0,0,0,0,0},
			{0,0,1,0,0},
			{0,1,1,0,0},
			{0,0,1,1,0},
			{0,0,0,0,0}
		},
		{
			{0,0,0,0,0},
			{0,1,1,0,0},
			{0,0,1,1,0},
			{0,0,1,0,0},
			{0,0,0,0,0}
		},

		{
			{0,0,0,0,0},
			{0,0,1,0,0},
			{0,1,1,0,0},
			{0,0,1,1,0},
			{0,0,0,0,0}
		},

		{
			{0,0,0,0,0},
			{0,1,1,0,0},
			{0,0,1,1,0},
			{0,0,1,0,0},
			{0,0,0,0,0}
		}

	},
	{    // l모양 블럭
		{
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0}
		},
		{
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0}
		},
		{
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0}
		},

		{
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0}
		}

	},


	{   // L모양 블럭
		{
			{0,0,0,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,0,1,1,0}
		},
		{
			{0,0,0,0,0},
			{0,0,1,1,0},
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0}
		},
		{
			{0,0,0,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,1,1,0,0}
		},

		{
			{0,0,0,0,0},
			{0,0,1,1,0},
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0}
		},

		{
			{0,0,0,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,1,1,0,0}
		}


	},
	{   // N모양 블럭
		{
			{0,0,0,0,0},
			{0,0,0,1,0},
			{0,0,1,1,0},
			{0,0,1,0,0},
			{0,0,1,0,0}
		},
		{
			{0,0,0,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,0,1,1,0},
			{0,0,0,1,0}
		},
		{
			{0,0,0,0,0},
			{0,1,0,0,0},
			{0,1,1,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0}
		},

		{
			{0,0,0,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,0,1,1,0},
			{0,0,0,1,0}
		},

			{
			{0,0,0,0,0},
			{0,1,0,0,0},
			{0,1,1,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0}
		}

	},
	{   // P모양 블럭
		{
			{0,0,0,0,0},
			{0,1,1,0,0},
			{0,1,1,0,0},
			{0,1,0,0,0},
			{0,0,0,0,0}
		},
		{
			{0,0,0,0,0},
			{0,1,0,0,0},
			{0,1,1,0,0},
			{0,1,1,0,0},
			{0,0,0,0,0}
		},

		{
			{0,0,0,0,0},
			{0,0,1,1,0},
			{0,0,1,1,0},
			{0,0,0,1,0},
			{0,0,0,0,0}
		},

			{
			{0,0,0,0,0},
			{0,1,0,0,0},
			{0,1,1,0,0},
			{0,1,1,0,0},
			{0,0,0,0,0}
		},

		{
			{0,0,0,0,0},
			{0,0,1,1,0},
			{0,0,1,1,0},
			{0,0,0,1,0},
			{0,0,0,0,0}
		}

	},
	{   // T모양 블럭
		{
			{0,0,0,0,0},
			{0,1,1,1,0},
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,0,0,0,0}
		},
		{
			{0,0,0,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,1,1,1,0},
			{0,0,0,0,0}
		},
		{
			{0,0,0,0,0},
			{0,1,1,1,0},
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,0,0,0,0}
		},

		{
			{0,0,0,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,1,1,1,0},
			{0,0,0,0,0}
		},

		{
			{0,0,0,0,0},
			{0,1,1,1,0},
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0}
		}

	},

	{   // U모양 블럭
		{
			{0,0,0,0,0},
			{0,1,0,1,0},
			{0,1,1,1,0},
			{0,0,0,0,0},
			{0,0,0,0,0}
		},
		{
			{0,0,0,0,0},
			{0,0,0,0,0},
			{0,1,1,1,0},
			{0,1,0,1,0},
			{0,0,0,0,0}
		},
		{
			{0,0,0,0,0},
			{0,1,0,1,0},
			{0,1,1,1,0},
			{0,0,0,0,0},
			{0,0,0,0,0}
		},
		{
			{0,0,0,0,0},
			{0,0,0,0,0},
			{0,1,1,1,0},
			{0,1,0,1,0},
			{0,0,0,0,0}
		},

		{
			{0,0,0,0,0},
			{0,1,0,1,0},
			{0,1,1,1,0},
			{0,0,0,0,0},
			{0,0,0,0,0}
		}

	},

	{   // V모양 블럭
		{
			{0,0,0,0,0},
			{0,1,0,0,0},
			{0,1,0,0,0},
			{0,1,1,1,0},
			{0,0,0,0,0}
		},
		{
			{0,0,0,0,0},
			{0,1,1,1,0},
			{0,1,0,0,0},
			{0,1,0,0,0},
			{0,0,0,0,0}
		},
		{
			{0,0,0,0,0},
			{0,0,0,1,0},
			{0,0,0,1,0},
			{0,1,1,1,0},
			{0,0,0,0,0}
		},

		{
			{0,0,0,0,0},
			{0,1,1,1,0},
			{0,1,0,0,0},
			{0,1,0,0,0},
			{0,0,0,0,0}
		},

		{
			{0,0,0,0,0},
			{0,0,0,1,0},
			{0,0,0,1,0},
			{0,1,1,1,0},
			{0,0,0,0,0}
		}


	},

	{   // W모양 블럭
		{
			{0,0,0,0,0},
			{0,1,0,0,0},
			{0,1,1,0,0},
			{0,0,1,1,0},
			{0,0,0,0,0}
		},
		{
			{0,0,0,0,0},
			{0,0,1,1,0},
			{0,1,1,0,0},
			{0,1,0,0,0},
			{0,0,0,0,0}
		},
		{
			{0,0,0,0,0},
			{0,0,0,1,0},
			{0,0,1,1,0},
			{0,1,1,0,0},
			{0,0,0,0,0}
		},

		{
			{0,0,0,0,0},
			{0,0,1,1,0},
			{0,1,1,0,0},
			{0,1,0,0,0},
			{0,0,0,0,0}
		},
		{
			{0,0,0,0,0},
			{0,0,0,1,0},
			{0,0,1,1,0},
			{0,1,1,0,0},
			{0,0,0,0,0}
		}

	},

	{   // X모양 블럭
		{
			{0,0,0,0,0},
			{0,0,1,0,0},
			{0,1,1,1,0},
			{0,0,1,0,0},
			{0,0,0,0,0}
		},
		{
			{0,0,0,0,0},
			{0,0,1,0,0},
			{0,1,1,1,0},
			{0,0,1,0,0},
			{0,0,0,0,0}
		},
		{
			{0,0,0,0,0},
			{0,0,1,0,0},
			{0,1,1,1,0},
			{0,0,1,0,0},
			{0,0,0,0,0}
		},

		{
			{0,0,0,0,0},
			{0,0,1,0,0},
			{0,1,1,1,0},
			{0,0,1,0,0},
			{0,0,0,0,0}
		},

		{
			{0,0,0,0,0},
			{0,0,1,0,0},
			{0,1,1,1,0},
			{0,0,1,0,0},
			{0,0,0,0,0}
		}


	},

	{   // Y모양 블럭
		{
			{0,0,0,0,0},
			{0,0,1,0,0},
			{0,1,1,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0}
		},
		{
			{0,0,0,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,1,1,0,0},
			{0,0,1,0,0}
		},
		{
			{0,0,0,0,0},
			{0,0,1,0,0},
			{0,0,1,1,0},
			{0,0,1,0,0},
			{0,0,1,0,0}
		},

		{
			{0,0,0,0,0},
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,1,1,0,0},
			{0,0,1,0,0}
		},
		{
			{0,0,0,0,0},
			{0,0,1,0,0},
			{0,0,1,1,0},
			{0,0,1,0,0},
			{0,0,1,0,0}
		}

	},
	{   // Z모양 블럭
		{
			{0,0,0,0,0},
			{0,1,1,0,0},
			{0,0,1,0,0},
			{0,0,1,1,0},
			{0,0,0,0,0}
		},
		{
			{0,0,0,0,0},
			{0,0,1,1,0},
			{0,0,1,0,0},
			{0,1,1,0,0},
			{0,0,0,0,0}
		},
		{
			{0,0,0,0,0},
			{0,0,1,1,0},
			{0,0,1,0,0},
			{0,1,1,0,0},
			{0,0,0,0,0}
		},

		{
			{0,0,0,0,0},
			{0,0,1,1,0},
			{0,0,1,0,0},
			{0,1,1,0,0},
			{0,0,0,0,0}
		},
		{
			{0,0,0,0,0},
			{0,0,1,1,0},
			{0,0,1,0,0},
			{0,1,1,0,0},
			{0,0,0,0,0}
		}
	}
};

int space[17 + 1][11 + 2] = {  // 세로 15+1(아래벽)칸, 가로 10+2(양쪽 벽)칸  
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,3,3,3,3,3,3,3,3,3,3,3,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1}
};




void Init();
void gotoxy(int x, int y);
void CreateRandomForm();
bool CheckCrash(int x, int y);
void DropBlock();
void BlockToGround();
void RemoveLine();
void DrawMap();
void DrawBlock();
void DrawMenu();
void DrawfinishMenu();
void InputKey();
void Drawline();
void overline();
void mapMaker();




int main() {

	Init();
	startDropT = clock();
	while (true) {
		DrawMenu();
		if (signal == 1) {
			cnt += 1;
			break;
		}
	}
	

	if (signal == 1) {
		signal = 0;
		CreateRandomForm();
	
		
		while (TRUE) {

			if(cnt == 1) {
				int x = 3; //타이틀화면이 표시되는 x좌표 
				int y = 4; //타이틀화면이 표시되는 y좌표 

				gotoxy(x + 3 , y - 4); printf("시간 : %ds", clock()/1000);

			}
			mapMaker();
			DrawMap();
			DrawBlock();
			Drawline();
			DropBlock();
			BlockToGround();
			RemoveLine();
			InputKey();
			overline();
		}
	
	}

}

void mapMaker() {

	time_t currentTime = clock() / CLOCKS_PER_SEC;

	if (currentTime - lastLevelUpTime >= 30) {
		++level;
		lastLevelUpTime = currentTime;

		for (int i = 0; i < 18; i++) {
			for (int j = 0; j < 13; j++) {
				space[i][j] = 0;
			}
		}

		for (int i = 0; i < 18-level; i++) {
			for (int j = 0; j < 13-level; j++) {

				if (i == 1 && j >= 1+level && j <= 11-level) {
					space[i][j] = 3;
				}

				if ( (i == 17-level && j >= 1 + level && j <= 11 - level) || j == 0+level || j == 12-level) {
					space[i][j] = 1; 
				}

				
				
				
			}
		}
	}

}


void Init() {
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	srand(time(NULL));
}
void gotoxy(int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void CreateRandomForm() {
	blockForm = rand() % 12;
}

bool CheckCrash(int x, int y) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (block[blockForm][blockRotation][i][j] == 1) {
				int t = space[i + y][j + x / 2];
				if (t == 1 || t == 2) { // 벽일 때, 블럭일 때
					return true;
				}
			}
		}
	}
	return false;
}

void DropBlock() {
	endT = clock();
	if ((float)(endT - startDropT) >= 800) {
		if (CheckCrash(x, y + 1) == true) return;
		y++;
		startDropT = clock();
		startGroundT = clock();
		system("cls");
	}
}

void BlockToGround() {
	if (CheckCrash(x, y + 1) == true) {
		if ((float)(endT - startGroundT) > 1500) {
			// 현재 블록 저장
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					if (block[blockForm][blockRotation][i][j] == 1) {
						space[i + y][j + x / 2] = 2;
					}
				}
			}
			x = 8;
			y = 0;
			CreateRandomForm();
		}
	}
}

void RemoveLine() {
	for (int i = 17; i >= 0; i--) { // 벽라인 제외한 값
		int npt = 0;
		for (int j = 1; j < 11; j++) { // 
			if (space[i][j] == 2) {
				npt++;
			}
		}
		if (npt >= 10-level*2 ) { // 벽돌이 다 차있다면
			for (int j = 0; i - j >= 0; j++) {
				for (int x = 1; x < 11; x++) {
					if (i - j - 1 >= 0)
						space[i - j][x] = space[i - j - 1][x];
					else      // 천장이면 0저장
						space[i - j][x] = 0;
				}
			}
		}
	}
}

void DrawMap() {
	gotoxy(0, 0);
	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 13; j++) {
			if (space[i][j] == 1) {
				gotoxy(j * 2, i);
				printf("■");
			}
			else if (space[i][j] == 2) {
				gotoxy(j * 2, i);
				printf("▨");
			}
			else if (space[i][j] == 3) {
				gotoxy(j * 2, i);
				printf("ㅡ");
			}
		}
	}
}

void DrawMenu() {

	int x = 2; //타이틀화면이 표시되는 x좌표 
	int y = 4; //타이틀화면이 표시되는 y좌표 

	gotoxy(x, y + 15); printf("made by 복시우,정여진"); Sleep(100);
	gotoxy(x + 5, y + 2); printf("T E T R I S"); Sleep(100);
	gotoxy(x, y + 7); printf("Please Enter [enter Key] or ");
	gotoxy(x, y + 8); printf("[space key] to Start..");
	gotoxy(x, y + 10); printf("  ↑   : Shift");
	gotoxy(x, y + 11); printf("←  → : Left / Right");
	gotoxy(x, y + 12); printf("  ↓   : Soft Drop");
	gotoxy(x, y + 13); printf(" SPACE : Hard Drop");

	
		if (_kbhit()) {
			key = _getch();
			switch (key) {
			case 13: // enter
				signal += 1;
				system("cls");
				break;

			case 32: // space 
				signal += 1;
				system("cls");
				break;
			}
		}
	
	
}

void overline() {
	for (int j = 1; j < 11; j++) { // 
		if (space[1][j] == 2) {
			cnt += 1;
		}
	}

	while (cnt >= 2) {
		DrawfinishMenu();
	}
	
	
}

void DrawfinishMenu() {

	int x = 3; //타이틀화면이 표시되는 x좌표 
	int y = 4; //타이틀화면이 표시되는 y좌표 

	gotoxy(x, y + 0); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");  
	gotoxy(x, y + 1); printf("▤                              ▤");
	gotoxy(x, y + 2); printf("▤  +-----------------------+   ▤");
	gotoxy(x, y + 3); printf("▤  |  G A M E  O V E R..   |   ▤");
	gotoxy(x, y + 4); printf("▤  +-----------------------+   ▤");
	gotoxy(x, y + 5); printf("▤   YOUR TIME :  %d            ▤",endT);
	gotoxy(x, y + 6); printf("▤                              ▤");
	gotoxy(x, y + 7); printf("▤ Press enter key to restart.. ▤");
	gotoxy(x, y + 8); printf("▤                              ▤");
	gotoxy(x, y + 9); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");


	if (_kbhit()) {
		key = _getch();
		switch (key) {

		case 13: // enter
			signal = 0 ;
			system("cls");
			main();
			break;
		}
	}


}

void DrawBlock() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (block[blockForm][blockRotation][i][j] == 1) {
				gotoxy(x + j * 2, y + i);
				printf("▣");
			}
		}
	}
}

void Drawline() {
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	while (!CheckCrash(Pos.X, Pos.Y + 1)) {
		++Pos.Y;
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (block[blockForm][blockRotation][i][j] == 1) {
				gotoxy(Pos.X + j * 2, Pos.Y + i);
				printf("□");
			}
		}
	}
}



void InputKey() {
	if (_kbhit()) {
		key = _getch();
		switch (key) {
		case 72: // space
			blockRotation++;
			if (blockRotation >= 5) blockRotation = 0;
			startGroundT = clock();
			break;
		case 75: // left
			if (CheckCrash(x - 2, y) == false) {
				x -= 2;
				startGroundT = clock();
			}
			break;
		case 77: // right
			if (CheckCrash(x + 2, y) == false) {
				x += 2;
				startGroundT = clock();
			}
			break;
		case 80: // down
			if (CheckCrash(x, y + 1) == false)
				y++;
			break;

		case 32:
			while (CheckCrash(x, y + 1) == false) {
				y++;
			}


		}

		system("cls");
	}
}