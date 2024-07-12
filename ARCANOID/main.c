#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>

#define width 65
#define height 25

typedef struct {
	int x, y;
	int w;
} TRacket;

char mas[height][width + 1];
TRacket racket;

// �������������� ������� �� �������� �����
void InitRacket() {
	racket.w = 7;
	racket.x = (width - racket.w) / 2;
	racket.y = height - 1;

}

// ������������ �������
void PutRacket() {
	for (int i = racket.x; i < racket.x + racket.w; i++)
	{
		mas[racket.y][i] = '@';
	}
}

void MoveRacket(int x) {
	racket.x = x;
	// �������� ���� ������� �� �����
	if (racket.x < 1) {
		racket.x = 1;
	}
	if (racket.x + racket.w >= width) {
		racket.x = width - 1 - racket.w;
	}
}

void init() {
	// 0-�� ������ ��������� ���������
	for (int i = 0; i < width; i++) {
		mas[0][i] = '#';
	}
	mas[0][width] = '\0';
	// ����������� 0-�� ������ � 1-��
	strncpy(mas[1], mas[0], width+1);
	// 1-�� ������ ��������� ��������� ����� ���������� � ��������� �������
	for (int i = 1; i < width-1; i++) {
		mas[1][i] = ' ';
	}
	// 1-�� ������ ����������� �� ��� ���������
	for (int i = 2; i < height; i++) {
		strncpy(mas[i], mas[1], width+1);
	}
}

void show() {
	for (int i = 0; i < height; i++) {
		printf("%s", mas[i]);
		// ������ �������� ������ ������ �� ���� ������� ����� ���������
		if (i < height - 1) {
			printf("\n");
		}
	}
	
}

void setcur(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

int main() {
	// ���������� ���� ����� ��������� ������� ������
	InitRacket();
	do {
		setcur(0, 0);
		init();
		PutRacket();
		show();
		if (GetKeyState('A') < 0) MoveRacket(racket.x - 1);
		if (GetKeyState('D') < 0) MoveRacket(racket.x + 1);
		Sleep(10);
	} 
	while (GetKeyState(VK_ESCAPE) >= 0);
	return 0;
}