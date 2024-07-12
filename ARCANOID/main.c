#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include <math.h>

#define width 65
#define height 25
#define M_PI 3.14159265358979323846

typedef struct {
	int x, y;
	int w;
} TRacket;

typedef struct {
	float x, y;
	int ix, iy;
	float alfa;
	float speed;
} TBall;

char mas[height][width + 1];
TRacket racket;
TBall ball;

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

void MoveBall(float x, float y) {
	ball.x = x;
	ball.y = y;
	ball.ix = (int)round(ball.x);
	ball.iy = (int)round(ball.y);
}

void InitBall() {
	MoveBall(2, 2);
	ball.alfa = -1;
	ball.speed = 0.5;
}

void PutBall() {
	mas[ball.iy][ball.ix] = '*';
}

void AutoMoveBall() {
	// ������ ����� ����������
	if (ball.alfa < 0) ball.alfa += M_PI * 2;
	if (ball.alfa > M_PI * 2) ball.alfa -= M_PI * 2;

	// ����� ������������ �������� �������� ������ ������
	TBall bl = ball;

	// ��������� ����������� �� ��� ���, ���� �� ����� ���������� ����� �������
	while (1) {
		MoveBall(ball.x + cos(ball.alfa) * ball.speed, ball.y + sin(ball.alfa) * ball.speed);

		// ��������� ���������� �� �� �� ������ ��� � ��������
		if (mas[ball.iy][ball.ix] == '#' || mas[ball.iy][ball.ix] == '@') {
			// �������� ����� ��������� ������ � ������, bl ������ ��������� ������
			if ((ball.ix != bl.ix) && (ball.iy != bl.iy)) {
				// ���� ������ ����� � ����� ��� ������ ����� ������ ������ � ������� ����
				if (mas[bl.iy][ball.ix] == mas[ball.iy][bl.ix]) {
					ball.alfa = bl.alfa + M_PI;
				}
				else {
					if (mas[bl.iy][ball.ix] == '#')
						ball.alfa = (2 * M_PI - bl.alfa) + M_PI;
					else
						ball.alfa = (2 * M_PI - bl.alfa);
				}
			}
			else if (ball.iy == bl.iy) {
				ball.alfa = (2 * M_PI - bl.alfa) + M_PI;
			}
			else {
				ball.alfa = (2 * M_PI - bl.alfa);
			}

			// ��������� ����� �������� ����
			bl = ball;
		}
		else {
			break;
		}
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
	BOOL run = FALSE;
	InitRacket();
	InitBall();
	do {
		setcur(0, 0);
		if (run) {
			AutoMoveBall();
		}
		if (ball.iy > height) {
			run = FALSE;
		}
		init();
		PutRacket();
		PutBall();
		show();
		if (GetKeyState('A') < 0) MoveRacket(racket.x - 1);
		if (GetKeyState('D') < 0) MoveRacket(racket.x + 1);
		if (GetKeyState('W') < 0) run = TRUE;
		if (!run) {
			MoveBall(racket.x + racket.w / 2, racket.y - 1);
		}
		Sleep(10);
	} 
	while (GetKeyState(VK_ESCAPE) >= 0);
	return 0;
}