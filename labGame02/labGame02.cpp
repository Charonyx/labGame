#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<windows.h>

// style
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

// control
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void draw_ship(int x, int y)
{
	gotoxy(x, y);
	printf(" <-0-> ");
}

void erase_ship(int x, int y)
{
	system("cls");
//	setcolor(0, 0);
}


int main()
{
	char ch = ' ';
	int x = 38, y = 20;
	setcursor(0);
	setcolor(2, 4);
	draw_ship(x, y);

	do {
		if (_kbhit())
		{
			ch = _getch();
			if (ch == 'a' && x >= 1)
			{
				draw_ship(--x, y);
			}
			if (ch == 'd' && x <= 80)
			{
				draw_ship(++x, y);
			}
			if (ch == 's' && y <= 23)
			{
				erase_ship(x, y);
				draw_ship(x, ++y);
			}
			if (ch == 'w' && y >= 1)
			{
				erase_ship(x, y);
				draw_ship(x, --y);
			}
			fflush(stdin);
		}
		Sleep(10);
	} while (ch != 'x');


	return 0;
}