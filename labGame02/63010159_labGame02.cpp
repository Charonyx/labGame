#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
#include<conio.h>

// style
void setcursor(bool visible) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void setcolor(int fg, int bg) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

// control
void gotoxy(int x, int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y) {
	gotoxy(x, y);
	setcolor(2, 4);
	printf(" <-0-> ");
}
void draw_bullet(int x, int y) {
	gotoxy(x, y);
	setcolor(5, 0);
	printf("0");
}
void erase_bullet(int x, int y) {
	gotoxy(x, y);
	setcolor(0, 0);
	printf("   ");
}
void erase_ship(int x, int y) {
	gotoxy(x, y);
	setcolor(0, 0);
	printf("       ");
}
int main()
{
	char ch = '.';
	int x = 38, y = 20, bx[5] = { 0 }, by[5] = { 0 };
	int path = 0, sleep = 20;
	int j = -1, max = 0;
	int bull[5] = { 0 };
	setcursor(0);
	draw_ship(x, y);

	do {
		if (_kbhit())
		{
			ch = _getch();
			if (ch == ' ' && max < 5)
			{
				++j;
				bull[j % 5] = 1;
				bx[j % 5] = x + 3;
				by[j % 5] = y - 1;
				++max;
			}
		}

		if (ch == 'a') { path = 1; }
		if (ch == 'd') { path = 2; }
		if (ch == 's') { path = 0; }

		int i = 0;
		while (i < 5) {
			if (bull[i] == 1 && by[i] > 0)
			{
				erase_bullet(bx[i], by[i]);
				draw_bullet(bx[i], --by[i]);
				if (by[i] == 0)
				{
					Sleep(sleep);
					erase_bullet(bx[i], by[i]);
					--max;
					by[i] = 0;
				}
			}
			++i;
		}

		if (x > 0 && x < 75)
		{
			if (path == 1)
			{
				erase_ship(x, y);
				draw_ship(--x, y);
				Sleep(sleep);
			}
			else if (path == 2)
			{
				erase_ship(x, y);
				draw_ship(++x, y);
				Sleep(sleep);
			}
		}
		if (ch == 'a' && x == 75)
		{
			erase_ship(x, y);
			draw_ship(--x, y);
			Sleep(sleep);
		}
		if (ch == 'd' && x == 0)
		{
			erase_ship(x, y);
			draw_ship(++x, y);
			Sleep(sleep);
		}
		fflush(stdin);
		Sleep(sleep);

	} while (ch != 'x');
	setcolor(7, 0);

	return 0;
}