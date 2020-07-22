#pragma once
#include <conio.h>
#include <cstdlib>
#include <Windows.h>
#include <time.h>
#include <iostream>

using namespace std;

#include "Ball.h"
#include "Block.h"
#include "Panel.h"

#define M 24
#define N 79

char map[M][N];

void ShowControl() {
	cout << "\n\n\n\n\tINFO:\t\n\tS - START THE GAME\t\n\tA - MOVE LEFT\tD - MOVE RIGHT\t\n\tP - PAUSE\t\n";
	cout << "\tQ - SHOW CONTROL\t\n\n\tONE BLOCK = 10 POINTS\t\n";
	cout << "\n\n\t-> PRESS ANY KEY TO CONTINUE.\t\n\n\n\n";
}

void DrawMap() {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
}

void SetCaret(char symbol, Panel & object) {
	for (int i = 0; i < object.width; i++) {
		map[object.x][object.y + i] = symbol;
	}
}

int Collision(Ball & b, Block & block) {
	if (block.existence) {
		if ((b.x == block.x + 1) && (b.y >= block.y) && (b.y <= block.y + block.width)) {
			return 1;
		}
		if ((b.x == block.x) && (b.y == block.y + block.width)) {
			return 2;
		}
		if ((b.x == block.x - 1) && (b.y >= block.y) && (b.y <= block.y + block.width)) {
			return 1;
		}
		if ((b.x == block.x) && (b.y == block.y)) {
			return 2;
		}
	}
	return 0;
}

void SetBlocks(Block **bl) {
	for (int i = 0; i < M / 4; i++) {
		int step = 1;
		for (int j = 0; j < N / 4; j++) {
			Block & b = bl[i][j];
			b.width = 3;
			b.x = i;
			b.y = (j)*b.width + step;
			if (b.existence) {
				for (int h = 0; h < b.width; h++) {
					map[b.x][b.y + h] = '+';
				}
			}
			else {
				for (int h = 0; h < b.width; h++) {
					map[b.x][b.y + h] = ' ';
				}
			}
			map[b.x][b.y + b.width] = ' ';
			step++;
		}
	}
}

int play() {
	Panel *panel;
	panel = new Panel;
	Ball *ball;
	ball = new Ball;
	Block **blocks;
	blocks = new Block *[M / 4];
	for (int i = 0; i < M / 4; i++) { 
		blocks[i] = new Block [N / 4]; 
	}
	int players_score = 0;

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			map[i][j] = ' ';
		}
	}

	panel->x = 23;
	panel->y = 25;
	panel->width = 10;
	SetCaret('=', *panel);

	ball->x = panel->x - 1;
	ball->y = panel->y + panel->width / 2;
	ball->d_x = -1;
	ball->d_y = 1;
	ball->activity = true;
	map[ball->x][ball->y] = 'o';

	for (int i = 0; i < M / 4; i++) {
		for (int j = 0; j < N / 4; j++) {
			blocks[i][j].existence = true;
		}
	}

	for (int i = 0; i < 1; i++) {
		system("cls");
		ShowControl();
		_getch();
		break;
	}

	SetBlocks(blocks);
	DrawMap();

	int end = 0;
	char s, st;
	do {
		st = _getch();
		cout << st;
	} while (st != 's');

	while (end == 0) {
		s = 'w';
		if (ball->x < 8) {
			for (int i = 0; i < M / 4; i++) {
				for (int j = 0; j < N / 4; j++) {
					Block & b = blocks[i][j];
					if (Collision(*ball, b) == 1) {
						ball->d_x *= -1;
						b.existence = false;
						players_score += 1;
					}
					else if (Collision(*ball, b) == 2) {
						ball->d_y *= -1;
						b.existence = true;
					}
					SetBlocks(blocks);
				}
			}
		}
		map[ball->x][ball->y] = ' ';
		if (ball->activity) {
			ball->move();
		}
		map[ball->x][ball->y] = 'o';
		if (ball->y < 1 || ball->y > N - 1) {
			ball->d_y *= -1;
		}
		if (ball->x < 1 || ball->x > M - 1) {
			ball->d_x *= -1;
		}
		if ((ball->x == panel->x - 1) && (ball->y >= panel->y) && (ball->y <= panel->y + panel->width)) {//
			ball->d_x *= -1;
			ball->d_y *= -1;
		}
		if (ball->x > M - 1) {
			break;
		}

		if (_kbhit()) {
			s = _getch();
		}
		switch (s) {
		case 'a':
			SetCaret(' ', *panel);
			panel->y -= 3;
			SetCaret('=', *panel);
			break;
		case 'd':
			SetCaret(' ', *panel);
			panel->y += 3;
			SetCaret('=', *panel);
			break;
		case 'p':
			system("cls");
			cout << "\n\n\n\n\tPAUSE...\t\n\n\n\t-> PRESS ANY KEY TO CONTINUE.\t";
			_getch();
			break;
		case 'q':
			system("cls");
			ShowControl();
			_getch();
			break;
		}

		Sleep(1);
		system("cls");
		DrawMap();
	}

	system("cls");
	cout << "\n\n\n\n\tYOU LOST!\t\n\tSCORE\t" << players_score*10 << "\t\n\n\n\n";

	delete panel;
	delete ball;
	for (int i = 0; i < M / 4; i++) {
		delete[] blocks[i];
	}

	return 0;
};