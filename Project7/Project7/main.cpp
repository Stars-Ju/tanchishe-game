#define _CRT_SECURE_NO_WARNINGS	
#include <iostream>
#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>


//坐标
typedef struct Point
{
	int x;
	int y;
}MYPOINT;
//蛇
struct Snake
{
	MYPOINT xy[100];  //蛇最长100节
	int num;
	char position;
}snake;
//食物
struct Food
{
	MYPOINT fdxy;
	int flag;
	int grade;
}food;
//窗口
HWND hwnd = NULL;

//方向
enum position{up,down,left,right};

void initSnake() {

	snake.xy[2].x = 0;
	snake.xy[2].y = 0;

	snake.xy[1].x = 10;
	snake.xy[1].y = 0;

	snake.xy[0].x = 20;
	snake.xy[0].y = 0;

	snake.num = 3;
	snake.position = right;

}


void drawSnake() {

	for (int i = 0; i < snake.num; i++) {
		setlinecolor(RED);
		setfillcolor(BLUE);
		fillrectangle(snake.xy[i].x, snake.xy[i].y, snake.xy[i].x + 10, snake.xy[i].y + 10);
	}
}
void moveSnake() {
	for (int i = snake.num - 1; i > 0; i--) {
		snake.xy[i].x = snake.xy[i - 1].x;
		snake.xy[i].y = snake.xy[i - 1].y;
	}
	switch (snake.position)
	{
	case up:
		snake.xy[0].y -= 10; break;
	case down:
		snake.xy[0].y += 10; break;
	case left:
		snake.xy[0].x -= 10; break;
	case right:
		snake.xy[0].x += 10; break;
	default:
		break;
	}
}
void keyDown() {
	char key = _getch();

	if (key == 32) {
		while (_getch() != 32);
	}

	switch (key)
	{
	case 'w':
	case 'W':
	case 72:
		if (snake.position != down) {
			snake.position = up;
		}
		break;
	case 's':
	case 'S':
	case 80:
		if (snake.position != up) {
			snake.position = down;
		}
		break;
	case 'a':
	case 'A':
	case 75:
		if (snake.position != right) {
			snake.position = left;
		}
		break;
	case 'd':
	case 'D':
	case 77:
		if (snake.position != left) {
			snake.position = right;
		}
		break;
	}
}

void initFood() {
	srand((unsigned int)time(NULL));
	food.fdxy.x = rand() % 80 * 10;
	food.fdxy.y = rand() % 60 * 10;
	food.flag = 1;

	for (int i = 0; i < snake.num; i++) {
		if (food.fdxy.x == snake.xy[i].x && food.fdxy.y == snake.xy[i].y) {
			food.fdxy.x = rand() % 80 * 10;
			food.fdxy.y = rand() % 60 * 10;
		}
	}
}
void drawFood() {
	setlinecolor(BLACK);
	setfillcolor(GREEN);
	fillrectangle(food.fdxy.x, food.fdxy.y, food.fdxy.x + 10, food.fdxy.y + 10);
}
void eatFood() {
	if (snake.xy[0].x == food.fdxy.x && snake.xy[0].y == food.fdxy.y) {
		food.flag = 0;
		snake.num++;
		food.grade += 10;
	}
}
void showGrade() {
	char grade[100] = "";
	sprintf(grade, "分数：%d", food.grade);
	setbkmode(TRANSPARENT);
	settextcolor(LIGHTBLUE);
	outtextxy(650, 30, grade);
}
int snakeDie() {
	if (snake.xy[0].x < 0 || snake.xy[0].x>800 || snake.xy[0].y < 0 || snake.xy[0].y>600) {
		MessageBox(hwnd, "撞墙，游戏结束！", "撞墙警告",0);
		return 1;
	}
	for (int i = 1; i < snake.num; i++) {
		if (snake.xy[0].x == snake.xy[i].x && snake.xy[0].y == snake.xy[i].y) {
			MessageBox(hwnd, "自杀,游戏结束", "自杀警告", 0);
			return 1;
		}
	}
	return 0;
}


int main() {

	hwnd=initgraph(800, 600);
	setbkcolor(WHITE);
	cleardevice();
	initSnake();


	while (1) {
		cleardevice();
		drawSnake();
		moveSnake();

		drawFood();
		eatFood();
		showGrade();

		if (snakeDie()) {
			break;
		}

		if (food.flag == 0) {
			initFood();
		}


		if (_kbhit()) {
			keyDown();
		}
		Sleep(100);
	}

	_getch();
	closegraph();
	return 0;
}